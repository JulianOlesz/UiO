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
    //          hvis det ikke er nok plass vil kallet mislykkes -> frigjør ressurser og return null 
    printf("Size in bytes: %d\n", size_in_bytes);

    int needed_blocks = (size_in_bytes + 4095) / 4096;
    int remaining_blocks = needed_blocks; // for å telle hvor mange ganger vi må allokere blokker
    int num_extents = 0;

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
            return NULL;
        }

        

        struct Extent* extents = malloc((num_extents + 1) * sizeof(struct Extent));
        extents[num_extents].blockno = blockno;
        extents[num_extents].extent = blocks;
        num_extents++;
        remaining_blocks -= blocks;
    }

    
    

    printf("Trying allocate %d blocks", needed_blocks);

    struct Extent* extents = malloc(sizeof(struct Extent));

    
    

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
        printf("Increasing entry count: %d\n", parent->num_entries);
    }

    return n_node;
}

struct inode* create_dir( struct inode* parent, const char* name )
{
    // sjekker om dir allerede finnes i parent 
    if (parent != NULL) {
        struct inode* existing = find_inode_by_name(parent, name);
        printf("find_inode_by_name(%s, %s) = %p\n", parent->name, name, existing);
        if (existing != NULL) {
            printf("DIR ALREADY EXISTS: %s\n", name);
            return NULL;
        } 

        if (find_inode_by_name(parent, name) != NULL) {
            return NULL;
        } 
    }

    printf("Making child\n");

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

    printf("Made child\n");

    if (parent != NULL)
    {
        parent->entries = realloc(parent->entries, (parent->num_entries + 1) * sizeof(uintptr_t));
        parent->entries[parent->num_entries] = (uintptr_t)child;
        parent->num_entries++;
        printf("Increasing entry count: %d\n", parent->num_entries);
    }

    return child;
}

struct inode* find_inode_by_name( struct inode* parent, const char* name )
{
    if (parent == NULL || parent->is_directory == 0 || parent->num_entries == 0) {
        printf("%s is not a directory or has no entries\n", parent->name);
        return NULL;
    }

    printf("looking for node: %s - in: %s\n", name, parent->name);

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
    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
    return -1;
}

int delete_dir( struct inode* parent, struct inode* node )
{
    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
    return -1;
}

void save_inodes( const char* master_file_table, struct inode* root )
{
    printf("Saving inodes to mft: %s\n", master_file_table);

    printf("name: %s\n", root->name);
    //printf("inode %hhu", root->name);

    //fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
    return;
}

void load_helper (uint32_t id, FILE *file) {
    printf("\nload helper\n\n");
    printf("id: %u\n", id);

    uint32_t name_len;
    char *name;
    char       is_directory;
	char       is_readonly;
    uint32_t filesize;
    uint32_t num_entries;
    uintptr_t* entries;

    fread(&name_len, sizeof(uint32_t), 1, file);
    printf("name_len: %u\n", name_len);

    name = malloc(name_len + 1); //!
    fread(name, 1, name_len, file);
    name[name_len] = '\0';
    printf("name: %s\n", name);

    fread(&is_directory, sizeof(char), 1, file);
    printf("is directory: %d\n", is_directory);

    fread(&is_readonly, sizeof(char), 1, file);
    printf("is readonly: %d\n", is_readonly);

    if (is_directory == 1)
    {
        printf("IS DIR\n");
        fread(&num_entries, sizeof(uint32_t), 1, file);
        printf("num_entries: %u\n", num_entries);
        if (num_entries == 0)
        {
            printf("no entries left");
            return;
        } else 
        {

            for (int i = 0; i < num_entries; i++)
            {
                load_helper(entries[i], file);
            }
        }
    } else {
        printf("IS FILE\n");
        fread(&filesize, sizeof(uint32_t), 1, file);
        printf("filesize: %u\n", filesize);

        uint32_t temp;

        entries = malloc(num_entries * sizeof(uintptr_t));

        for (uint32_t i = 0; i < num_entries; i++)
        {
            fread(&temp, sizeof(uint32_t), 1, file);
            entries[i] = temp;
        }

       
        printf("entry: %lu\n", entries[0]);
        
        return;
    }
}

struct inode* read_inodes(FILE* file) {
    struct inode* node = malloc(sizeof(struct inode));

    // ID
    if (fread(&node->id, sizeof(uint32_t), 1, file) != 1) {
        free(node);
        return NULL; 
    }
    printf("\n ID: %u\n", node->id);

    // NAME_LEN
    uint32_t name_len;
    fread(&name_len, sizeof(uint32_t), 1, file);
    printf("name_len: %u\n", name_len);

    // NAME
    node->name = malloc(name_len); 
    fread(node->name, 1, name_len, file);
    node->name[name_len] = '\0';
    printf("name: %s\n", node->name);

    // IS DIR
    fread(&node->is_directory, sizeof(char), 1, file);
    printf("is directory: %d\n", node->is_directory);

    // IS RDONLY
    fread(&node->is_readonly, sizeof(char), 1, file);
    printf("is readonly: %d\n", node->is_readonly);

    if (node->is_directory == 1)
        {
            printf("this is a directory\n");

            node->filesize = 0;

            fread(&node->num_entries, sizeof(uint32_t), 1, file);
            printf("num_entries: %u\n", node->num_entries);

            if (node->num_entries == 0)
            {
                node->entries = NULL;
                printf("no entries left");
                return node;
            } else 
            {
                node->entries = malloc(node->num_entries * sizeof(uintptr_t));

                for (uint32_t i = 0; i < node->num_entries; i++)
                {   
                    fread(&node->entries[i], sizeof(uint64_t), 1, file);
                    printf("entry %d: %ld\n", i, node->entries[i]);
                }

                node->entries = node->entries;
            }
        } else {
            printf("this is a file\n");

            uint32_t filesize;
            fread(&node->filesize, sizeof(uint32_t), 1, file);
            printf("filesize: %u\n", node->filesize);

            fread(&node->num_entries, sizeof(uint32_t), 1, file);
            printf("num_entries: %u\n", node->num_entries);
        
            
            node->entries = malloc(node->num_entries * sizeof(struct Extent));
            struct Extent* extent = (struct Extent*)node->entries; // caster til extent type 

            for (int i = 0; i < node->num_entries; i++)
            {
                fread(&extent[i].blockno, sizeof(uint32_t), 1, file);
                fread(&extent[i].extent, sizeof(uint32_t), 1, file);
                printf("entry %d - blockno: %u, extent: %u\n", i, extent[i].blockno, extent[i].extent);
            }

            /*
            uint32_t byteskip;
            fread(&byteskip, sizeof(uint32_t), 1, file);
            */
            
        }
    return node;
}

struct inode* load_inodes( const char* master_file_table )
{
    printf("loading from: %s\n", master_file_table);

    FILE *file = fopen(master_file_table, "rb");

    struct inode* root = NULL;
    struct inode* node;

    struct inode** node_list = NULL;
    uint32_t node_count = 0;
    
    while ((node = read_inodes(file)) != NULL)
    { 
        struct inode** temp = realloc(node_list, (node_count + 1)*sizeof(struct inode*));
        if (temp == NULL){free(node_list);}
        node_list = temp;

        node_list[node_count++] = node;

        if (root == NULL)
        {
            root = node;
            printf("root- %s\n", root->name);
        }
        
    }

    for (int i = 0; i < node_count; i++)
    {
        struct inode* parent = node_list[i];
        if (parent->is_directory)
        {
            for (int j = 0; j < parent->num_entries; j++) {
                for (int k = 0; k < node_count; k++)
                {
                    if (node_list[k]->id == parent->entries[j])
                    {
                        printf("Setting parent %s \t for node: %s\n", parent->name, node_list[k]->name);
                        parent->entries[j] = node_list[k];
                        break;
                    }
                }
            }
        }
    }

    free(node_list);
    
    //find_inode_by_name(root, "kernel");

    fclose(file);

    printf("\nfile end.\n");

    return root;
}

void fs_shutdown( struct inode* inode )
{
    if (inode->is_directory == 1 && inode->num_entries != 0)
    {
        for (int i = 0; i < inode->num_entries; i++)
        {
            fs_shutdown(inode->entries[i]);
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

