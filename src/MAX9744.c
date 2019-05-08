#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include "MAX9744.h"
#include "trace.h"

#define print_and_return_errno() \
do { \
        fprintf(stderr,"%s: error: '%m' (%d)\n", __FUNCTION__, errno); \
        return -errno; \
} while(0)

#define check_state() \
do { \
        if ( i2c_file <= 0 || i2c_address <= 0 ) { \
        fprintf(stderr,"%s: error: MAX9744 not initialized\n", __FUNCTION__); \
        return -EIO; } \
} while(0)

static int i2c_file = 0;
static int i2c_address = 0;

int MAX9744_init (const char* i2c_dev, int _i2c_address) {

    if ( i2c_dev == NULL || _i2c_address == 0 ) {
        return -EINVAL;
    }

    i2c_address = _i2c_address;

    i2c_file = open(i2c_dev, O_RDWR);
    if (i2c_file < 0) {
        print_and_return_errno();
    }
    DEBUG_LOG("i2c_dev %s opened file=%d\n", i2c_dev, i2c_file);
    return 0;
}

static int MAX9744_get_bus() {

    check_state();
    if (ioctl(i2c_file, I2C_SLAVE, i2c_address) < 0) {
        print_and_return_errno();
    }
    return 0;
}


int MAX9744_get_volume(void) {
    DEBUG_LOG("entrer\n");
    if ( MAX9744_get_bus() ){
        return -EIO;
    }

    int value = i2c_smbus_read_byte(i2c_file);
    return value;
}

int MAX9744_set_volume(unsigned char value) {

    DEBUG_LOG("entrer\n");
    if ( MAX9744_get_bus() ){
        return -EIO;
    }

    if ( value > 63) {
        DEBUG_LOG("value(%d) > 63\n", value);
        errno = EINVAL;
        return -EINVAL;
    }

    return i2c_smbus_write_byte(i2c_file, value);
}

int MAX9744_release(void) {

    if ( i2c_file > 0) {
        DEBUG_LOG("close file %d\n", i2c_file);
        return close(i2c_file);
    }
    return 0;
}
