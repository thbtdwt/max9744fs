# max9744fs

This 'fuse' daemon named 'max9744d' is used to control the volume of a max9744 device.
 
In details:
```
 -----------
|           |              ---------
| raspberry | <---i2c---> | max9744 |
|           |              ---------
 -----------
```

A systemd service creates /var/max9744/ directory and the daemon mounts a fuse fs containning only one file named 'volume'. 

## Build and installation 
```shell
cmake .
make 
sudo make install
````

## Usage

The volume value must be 0 to 63.

### Example
Set the volume:
```bash
echo 30 > /var/max9744/volume
```
Get the volume:
```bash
cat /var/max9744/volume
```
