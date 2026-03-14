#include "inode.h"
#include "block_allocation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct inode* create_file( struct inode* parent, const char* name, char readonly, int size_in_bytes )
{
    // må  sjekke for like navn i parent dir
    
    if (find_inode_by_name(parent, name) != -1) {
        return NULL;
    }

    // må allokere riktig antall blokker med allocate_block i block_allocation.c 
    //          hvis det ikke er nok plass vil kallet mislykkes -> frigjør ressurser og return null 
    int blocks = allocate_blocks( (int)ceil(size_in_bytes/4) );

    if (blocks == -1) {
        return NULL;
    }

    struct inode n_node;
    n_node.id = 1;
    n_node.name = name;
    n_node.is_directory = 0;
    n_node.is_readonly = readonly;
    n_node.filesize = size_in_bytes;
    n_node.num_entries = blocks;

    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
    return NULL;
}

struct inode* create_dir( struct inode* parent, const char* name )
{
    // sjekker om dir allerede finnes i parent 
    if (find_inode_by_name(parent, name) != -1) {
        return NULL;
    }

    struct inode n_node;
    n_node.id = 2;
    n_node.name = name;
    n_node.is_directory = 1;

    // entries bestemmes senere? 

    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
    return NULL;
}

struct inode* find_inode_by_name( struct inode* parent, const char* name )
{
    if (parent->is_directory == 0) {
        return -1;
    }

    //printf(parent->entries[0]);

    /*
    for (int i = 0; i < parent->num_entries; i++) {
        if (parent->entries[i] == name){

        }
    }
    */
    
    
    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
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
    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
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
                printf("no entries left");
                return;
            } else 
            {
                uint64_t temp;

                node->entries = malloc(node->num_entries * sizeof(uintptr_t));

                for (uint32_t i = 0; i < node->num_entries; i++)
                {   
                    fread(&temp, sizeof(uint64_t), 1, file);
                    node->entries[i] = temp;
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

void print_inode(struct inode* node) {
    printf("=== inode ===\n");
    printf("id:           %u\n", node->id);
    printf("name:         %s\n", node->name);
    printf("is_directory: %d\n", node->is_directory);
    printf("is_readonly:  %d\n", node->is_readonly);
    if (node->is_directory) {
        printf("num_entries:  %u\n", node->num_entries);
        for (uint32_t i = 0; i < node->num_entries; i++) {
            struct inode* child = (struct inode*)node->entries[i];
            printf("  child %d: %s\n", i, child->name);
        }
    } else {
        printf("filesize:     %u\n", node->filesize);
        printf("num_entries:  %u\n", node->num_entries);
        for (uint32_t i = 0; i < node->num_entries; i += 2) {
            printf("  block %u, extent %u\n", 
                (uint32_t)node->entries[i], 
                (uint32_t)node->entries[i+1]);
        }
    }
    printf("=============\n");
}

struct inode* load_inodes( const char* master_file_table )
{
    printf("loading from: %s\n", master_file_table);

    FILE *file = fopen(master_file_table, "rb");

    struct inode* root = NULL;
    struct inode* node;
    
    while ((node = read_inodes(file)) != NULL)
    {
        if (root == NULL)
        {
            root = node;
            printf("root- %s\n", root->name);
        }
    }
    
    fclose(file);

    printf("\nfile end.\n");

    print_inode(root);

    return root;
}

void fs_shutdown( struct inode* inode )
{
    fprintf( stderr, "%s is not implemented\n", __FUNCTION__ );
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

