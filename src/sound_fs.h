#ifndef SOUND_FS_H
#define SOUND_FS_H

#define FUSE_USE_VERSION 30
#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>

struct sound_fs_operations {
	int (*get_volume)(void);
	int (*set_volume)(unsigned char);
};
int set_sound_fs_operations(struct sound_fs_operations* operations);

struct fuse_operations* get_fuse_operations();



#endif // SOUND_FS_H