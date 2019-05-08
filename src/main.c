#include <stdlib.h>
#include "MAX9744.h"
#include "sound_fs.h"


void clean_up_ressource(void) { 
	MAX9744_release();
}

int main(int argc, char *argv[]) {

	if ( MAX9744_init("/dev/i2c-1", 0x4b) ) {
		exit(1);
	}
	if ( atexit(clean_up_ressource) ) {
		exit(1);
	}

	struct sound_fs_operations sound_ops = {
		.get_volume = MAX9744_get_volume,
		.set_volume = MAX9744_set_volume
	};
    set_sound_fs_operations(&sound_ops);

    return fuse_main( argc, argv, get_fuse_operations(), NULL );
}





