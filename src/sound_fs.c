#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "sound_fs.h"
#include "trace.h"

static struct sound_fs_operations sound_fs_opts = { NULL };

static int do_getattr( const char *path, struct stat *st );
static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi );
static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi );
static int do_write( const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info * fi );
static int do_truncate( const char * path, off_t offset );

int set_sound_fs_operations(struct sound_fs_operations* operations) {
    if ( operations == NULL ) {
        return -EINVAL;
    }
    memcpy( &sound_fs_opts, operations, sizeof(struct sound_fs_operations) );
    return 0;
}

static struct fuse_operations fuse_opts = {
	.getattr = do_getattr,
	.readdir = do_readdir,
    .read = do_read,
    .write = do_write,
    .truncate = do_truncate
};


struct fuse_operations* get_fuse_operations() {
	return &fuse_opts;
}

static int do_getattr( const char *path, struct stat *st ) {
	st->st_uid = getuid();
	st->st_gid = getgid();
	st->st_atime = time( NULL );
	st->st_mtime = time( NULL );

	if ( strcmp( path, "/" ) == 0 )
	{
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2;
	}
	else
	{
		st->st_mode = S_IFREG | 0644;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
		
	return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
	(void) offset;
	(void) fi;
	filler( buffer, ".", NULL, 0 ); 
	filler( buffer, "..", NULL, 0 );
	
	if ( strcmp( path, "/" ) == 0 ) 
	{
		filler( buffer, "volume", NULL, 0 );
	}
	
	return 0;
}


static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
{
    (void) fi;
    char text_value[4] = { 0 };

    DEBUG_LOG("path %s\n", path);
    if ( strcmp( path, "/volume" ) != 0 ) {
        return -ENOENT;
    }

    if ( ! sound_fs_opts.get_volume ) {
        DEBUG_LOG("get_volume not implemented\n");
        return -ENOSYS; 
    }
            
    int volume = sound_fs_opts.get_volume();
    if ( volume < 0 ) {
        DEBUG_LOG("get_volume error (%d)\n", volume);
        return volume;
    }
                
    snprintf( text_value, sizeof(text_value), "%d", volume );
    DEBUG_LOG("get_volume returns %d\n", volume);
    size_t text_len = strlen(text_value);
    memcpy( buffer, text_value + offset, ( text_len - offset < size ) ? text_len - offset : size);
    return text_len - offset;
}

static int do_write ( const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info * fi )
{
    (void) fi;
    (void) offset;
    (void) size;
    char text_value[4];

    if ( size > sizeof(text_value) ) {
        return -EINVAL;
    }

    DEBUG_LOG("path %s\n", path);
    if ( strcmp( path, "/volume" ) != 0 ) {
        return -ENOENT;
    }

    if ( ! sound_fs_opts.set_volume ) {
        DEBUG_LOG("set_volume not implemented\n");
        return -ENOSYS; 
    }

    memcpy( text_value, buffer, ( sizeof(text_value) < size ) ? sizeof(text_value) : size);
    unsigned char volume =  strtoul (text_value, NULL, 0);

    if ( sound_fs_opts.set_volume(volume) ) {
        DEBUG_LOG("get_volume error (%d)\n", errno);
        return -errno;
    }
    return size;
}

static int do_truncate ( const char * path, off_t offset )
{
    (void) path;
    (void) offset;
    return 0;
}
