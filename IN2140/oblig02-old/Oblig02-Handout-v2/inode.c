#include "inode.h"
#include "block_allocation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

struct inode* create_file( struct inode* parent, const char* name, char readonly, int size_in_bytes )
{
    // må  sjekke for like navn i parent dir
    
    if (find_inode_by_name(parent, name) != -1) {
        return NULL;
    }

    // må allokere riktig antall blokker med allocate_block i block_allocation.c 
    //          hvis det ikke er nok plass vil kallet mislykkes -> frigjør ressurser og return null 
    int blocks = allocate_block((int)ceil(size_in_bytes/4));

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

struct inode* load_inodes( const char* master_file_table )
{
    struct inode root; 
    root.id = 0;
    root.name = '/';
    root.is_directory = 1; 

    printf("loading cells\n");

    for (int i = 0; i < 100; i++) {
        printf("%c", master_file_table[i]);
    }
    
    printf("\n");
    //printf(master_file_table[0]);

    return NULL;
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

