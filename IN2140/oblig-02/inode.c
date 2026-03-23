#include "inode.h"
#include "block_allocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int global_id_counter = 0;

struct inode* create_file( struct inode* parent, const char* name, char readonly, int size_in_bytes )
{
    // må  sjekke for like navn i parent dir
    if (find_inode_by_name(parent, name) != NULL) {
        return NULL;
    }

    // Tar inn en extent size der 0 <= extent size < 4 
    // må allokere riktig antall blokker med allocate_block i block_allocation.c 
    // hvis det ikke er nok plass vil kallet mislykkes -> frigjør ressurser og return null 

    int needed_blocks = (size_in_bytes + 4095) / 4096;
    int remaining_blocks = needed_blocks; // for å telle hvor mange ganger vi må allokere blokker
    int num_extents = 0;
    struct Extent* extents = NULL;

    while (remaining_blocks > 0)
    {
        int blocks = (remaining_blocks > 4) ? 4 : remaining_blocks;
        int32_t blockno;

        while (blocks > 0)
        {
            blockno = allocate_blocks(blocks);
            if (blockno != -1) break;
            blocks--;
        }
    
        if (blockno == -1)
        {
            free(extents);
            return NULL;
        }

        
        extents = realloc(extents, (num_extents + 1) * sizeof(struct Extent));

        extents[num_extents].blockno = blockno;
        extents[num_extents].extent = blocks;
        num_extents++;
        remaining_blocks -= blocks;
    }

    struct inode* n_node = malloc(sizeof(struct inode));
    n_node->id = global_id_counter;
    global_id_counter++;
    n_node->name = malloc(strlen(name) + 1);
    strcpy(n_node->name, name);
    n_node->is_directory = 0;
    n_node->is_readonly = readonly;
    n_node->filesize = size_in_bytes;
    n_node->num_entries = num_extents;
    n_node->entries = (uintptr_t*)extents;

    if (parent != NULL)
    {
        parent->entries = realloc(parent->entries, (parent->num_entries + 1) * sizeof(uintptr_t));
        parent->entries[parent->num_entries] = (uintptr_t)n_node;
        parent->num_entries++;
    }

    return n_node;
}

struct inode* create_dir( struct inode* parent, const char* name )
{
    // sjekker om dir allerede finnes i parent 
    if (parent != NULL) {
        if (find_inode_by_name(parent, name) != NULL) {
            return NULL;
        } 
    }

    struct inode* child = malloc(sizeof(struct inode));
    child->id = global_id_counter;
    global_id_counter++;
    child->name = malloc(strlen(name) + 1);
    strcpy(child->name, name); // vi leser ikke en fil direkte så navn må kopieres over 
    child->is_directory = 1;
    child->is_readonly = 0;
    child->filesize = 0;
    child->num_entries = 0;
    child->entries = 0;

    if (parent != NULL)
    {
        parent->entries = realloc(parent->entries, (parent->num_entries + 1) * sizeof(uintptr_t));
        parent->entries[parent->num_entries] = (uintptr_t)child;
        parent->num_entries++;
    }

    return child;
}

struct inode* find_inode_by_name( struct inode* parent, const char* name )
{
    if (parent == NULL || parent->is_directory == 0 || parent->num_entries == 0) {
        return NULL;
    }

    for (uint32_t i = 0; i < parent->num_entries; i++)
    {
        struct inode* entry = (struct inode*)parent->entries[i];
        if (strcmp(entry->name, name) == 0)
        {
            return entry;
        }
    }
    
    return NULL;
}

int delete_file( struct inode* parent, struct inode* node )
{
    if (node->is_directory != 0 || parent->is_directory != 1 || find_inode_by_name(parent, node->name) == NULL) {
        return -1;
    }

    //Må shifte alle elementer til venstre, sånn at noden vi skal slette er den siste i listen
    int i = 0;
    while ((struct inode*)parent->entries[i] != node) i++;

    for (int j = i; j < parent->num_entries - 1; j++)
    {
        parent->entries[j] = parent->entries[j+1];
    }

    parent->num_entries--;

    if (parent->num_entries == 0) {
        free(parent->entries);
        parent->entries = NULL;
    } else {
        parent->entries = realloc(parent->entries, parent->num_entries * sizeof(uintptr_t));

    }

    struct Extent* extents = (struct Extent*)node->entries;
    for (int i = 0; i < node->num_entries; i++) {
        for (int j = 0; j < extents[i].extent; j++) {
            free_block(extents[i].blockno + j); // i.e. block 2, ext 3 = blocks 2, 3, 4
        }
    }

    free(node->name);
    free(node->entries);
    free(node);

    return 0;
}

int delete_dir( struct inode* parent, struct inode* node )
{
    if (node->is_directory != 1 || 
        parent->is_directory != 1 || 
        find_inode_by_name(parent, node->name) == NULL ||
        node->num_entries != 0)
    {
        return -1;
    }

    int i = 0;
    while ((struct inode*)parent->entries[i] != node) i++;

    for (int j = i; j < parent->num_entries - 1; j++)
    {
        parent->entries[j] = parent->entries[j+1];
    }

    parent->num_entries--;

    if (parent->num_entries == 0) {
        free(parent->entries);
        parent->entries = NULL;
    } else {
        parent->entries = realloc(parent->entries, parent->num_entries * sizeof(uintptr_t));
    }
    
    fs_shutdown(node);

    return 0;
}

void write_helper(FILE* file, struct inode* node) {
    fwrite(&node->id, sizeof(uint32_t), 1, file);

    uint32_t name_len = strlen(node->name) + 1;

    fwrite(&name_len, sizeof(uint32_t), 1, file);
    fwrite(node->name, 1, name_len, file); // write bits of name for name_len 

    fwrite(&node->is_directory, sizeof(char), 1, file);
    fwrite(&node->is_readonly, sizeof(char), 1, file);

    if (node->is_directory)
    {
        fwrite(&node->num_entries, sizeof(uint32_t), 1, file);

        for (uint32_t i = 0; i < node->num_entries; i++)
        {
            struct inode* child = (struct inode*)node->entries[i];
            fwrite(&child->id, sizeof(uint32_t), 1, file);
        } 
        // en annen loop for å fortsette rekursivt
        // tror det kan bli problematisk å ha rekursjon samtidig som writing 
        for (uint32_t i = 0; i < node->num_entries; i++) {
            write_helper(file, (struct inode*)node->entries[i]);
        }
    } else
    {
        fwrite(&node->filesize, sizeof(uint32_t), 1, file);
        fwrite(&node->num_entries, sizeof(uint32_t), 1, file);
        struct Extent* extents = (struct Extent*)node->entries;
        for (uint32_t i = 0; i < node->num_entries; i++) {
            fwrite(&extents[i].blockno, sizeof(uint32_t), 1, file);
            fwrite(&extents[i].extent, sizeof(uint32_t), 1, file);
        }
    }
}


void save_inodes( const char* master_file_table, struct inode* root )
{
    FILE *file;
    file = fopen(master_file_table, "wb");

    write_helper(file, root);

    fclose(file);

    return;
}

struct inode* read_inodes(FILE* file) {
    struct inode* node = malloc(sizeof(struct inode));

    // ID
    if (fread(&node->id, sizeof(uint32_t), 1, file) != 1) {
        free(node);
        return NULL; 
    }

    // NAME_LEN
    uint32_t name_len;
    fread(&name_len, sizeof(uint32_t), 1, file);

    // NAME
    node->name = malloc(name_len + 1); 
    fread(node->name, 1, name_len, file);
    node->name[name_len] = '\0';

    printf("Name %s\n", node->name);


    // IS DIR
    fread(&node->is_directory, sizeof(char), 1, file);

    // IS RDONLY
    fread(&node->is_readonly, sizeof(char), 1, file);

    printf("is dir: %d, is readonly: %d\n", node->is_directory, node->is_readonly);


    if (node->is_directory == 1)
        {
            node->filesize = 0;
            
            fread(&node->num_entries, sizeof(uint32_t), 1, file);

            //printf("Entries: %d\n", node->num_entries);

            if (node->num_entries == 0)
            {
                node->entries = NULL;
                return node;
            } else {
                node->entries = malloc(node->num_entries * sizeof(uintptr_t));
                for (uint32_t i = 0; i < node->num_entries; i++)
                {   
                    uint64_t id;
                    fread(&id, sizeof(uint64_t), 1, file);
                    node->entries[i] = (uintptr_t)id;
                    //printf("node entry %d\n", id);
                }
            }
        } else {
            uint32_t filesize;
            fread(&node->filesize, sizeof(uint32_t), 1, file);

            fread(&node->num_entries, sizeof(uint32_t), 1, file);
        
            node->entries = malloc(node->num_entries * sizeof(struct Extent));

            struct Extent* extent = (struct Extent*)node->entries; // caster til extent type 

            for (int i = 0; i < node->num_entries; i++)
            {
                fread(&extent[i].blockno, sizeof(uint32_t), 1, file);
                fread(&extent[i].extent, sizeof(uint32_t), 1, file);
            }
        }
    return node;
}

struct inode* load_inodes( const char* master_file_table )
{
    FILE *file = fopen(master_file_table, "rb");

    struct inode* root = NULL;
    struct inode* node;
    struct inode** node_list = NULL;
    uint32_t node_count = 0;
    
    while ((node = read_inodes(file)) != NULL)
    { 
        struct inode** temp = realloc(node_list, (node_count + 1)*sizeof(struct inode*));
        if (temp == NULL) free(node_list);
        node_list = temp;

        node_list[node_count++] = node;

        if (root == NULL) root = node;
    }

    for (int i = 0; i < node_count; i++)
    {
        struct inode* parent = node_list[i];
        if (parent->is_directory){
            for (int j = 0; j < parent->num_entries; j++) {
                for (int k = 0; k < node_count; k++) {
                    if (node_list[k]->id == (uint32_t)parent->entries[j]) {
                        parent->entries[j] = (uintptr_t)node_list[k];
                    }
                }
            }
        }
    }

    free(node_list);
    fclose(file);
    return root;
}

void fs_shutdown( struct inode* inode )
{
    if (inode->is_directory == 1 && inode->num_entries != 0)
    {
        for (int i = 0; i < inode->num_entries; i++)
        {
            fs_shutdown((struct inode*)inode->entries[i]);
        }
    }
    
    //må bruke free for name og entries fordi de ble laget med malloc 
    free(inode->name);
    free(inode->entries);
    free(inode);
    return;
}

/* This static variable is used to change the indentation while debug_fs
 * is walking through the tree of inodes and prints information.
 */
static int indent = 0;

static void debug_fs_print_table( const char* table );
static void debug_fs_tree_walk( struct inode* node, char* table );

void debug_fs( struct inode* node )
{
    char* table = calloc( NUM_BLOCKS, 1 );
    debug_fs_tree_walk( node, table );
    debug_fs_print_table( table );
    free( table );
}

static void debug_fs_tree_walk( struct inode* node, char* table )
{
    if( node == NULL ) return;
    for( int i=0; i<indent; i++ )
        printf("  ");
    if( node->is_directory )
    {
        printf("%s (id %d)\n", node->name, node->id );
        indent++;
        for( int i=0; i<node->num_entries; i++ )
        {
            struct inode* child = (struct inode*)node->entries[i];
            debug_fs_tree_walk( child, table );
        }
        indent--;
    }
    else
    {
        printf("%s (id %d size %d)\n", node->name, node->id, node->filesize );

        /* The following is an ugly solution. We expect you to discover a
         * better way of handling extents in the node->entries array, and did
         * it like this because we don't want to give away a good solution here.
         */
        uint32_t* extents = (uint32_t*)node->entries;

        for( int i=0; i<node->num_entries; i++ )
        {
            for( int j=0; j<extents[2*i+1]; j++ )
            {
                table[ extents[2*i]+j ] = 1;
            }
        }
    }
}

static void debug_fs_print_table( const char* table )
{
    printf("Blocks recorded in master file table:");
    for( int i=0; i<NUM_BLOCKS; i++ )
    {
        if( i % 20 == 0 ) printf("\n%03d: ", i);
        printf("%d", table[i] );
    }
    printf("\n\n");
}