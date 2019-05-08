#ifndef MAX9744_H
#define MAX9744_H

int MAX9744_init (const char* i2c_dev, int _i2c_address);

int MAX9744_get_volume(void);

int MAX9744_set_volume(unsigned char value);

int MAX9744_release(void);

#endif // MAX9744_H