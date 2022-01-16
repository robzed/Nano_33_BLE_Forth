# A Forth for Arduino Nano 33 BLE.

Based on pForth, with some minor modifications and an API to Nano 33 BLE specific extensions. 

**NOTE: THIS PROJECT IS IN DEVLEOPMENT**

That means:
 - It isn't fully functional yet! 
 - While it runs, testing is in progress.
 - No binary is supplied - you'll need to build it (but a pre-built dictioary is supplied)

Next steps:
 - Testing new Arduino Nano 33 BLE specific commands
 - Add documentation
 



# Current Arduino Nano 33 BLE Support

All these are programmable from Forth.

 * Bluetooth Low energy (BLE) support.
 * Neopixel LED support.
 * Basic Arduino functions
    - e.g. millis, delay (called ms)
 * Internal flash writing to blocks on target for Forth extension / programs.
 * Support IMU 9-axis motion detector




# Accessing the terminal

pForth uses ANSI escape sequences. These haven't been changed from the original.

This is the command line that I use to access pForth on the Nano 33 BLE:
    picocom --baud 115200 --imap lfcrlf /dev/cu.usbmodem1421201


# Device Specific Words (Functions) Provided

These are in additional to standard pForth words

## General Functions


### ARDUINO-IFVER

Return: Return the version of the extensions


### HEAP_STATS

Return: Returns a pointer the mbed heap stats.



## Arduino Functions

See https://www.arduino.cc/reference/en/

 * 'ms' - called delay() in Arduino land. ms is the forth standard word.
 * 'millis'
 * 'micros'
 * 'delayMicroseconds'

These mirror the Arduino functions in terms of parameter/return.


## File System Interface

256K of internal Flash is set up as a filesystem - using mbed and LittleFS. This allows extra user Forth words to create
programs and applications that can be developed without reflashing the device.

See https://github.com/khoih-prog/FS_Nano33BLE for details on the Framework used.

We haven't considered FAT for the on-board flash - power loss robustness is poor, and it doesn't contain flash wear levelling.


### opendir

Open Directory for listing

Param:  Path/Name Zero-terminated C string
Return: Directory Object or 0 if heap allocation failure


### readdir

Read next directory entry along

Param:  Directory Object
Param:  Address - the directory entry to fill out (caller allocated)
Return: 1 on reading a filename, 0 at end of directory, negative error on failure 


### closedir

Call when finished with directory, frees up memory from heap.

Param:  Directory Object
Return: 0 on success, negative error code on failure 


### #dir

Get the sizeof the directory (number of entries)

Param:  Directory Object
Return: Number of files in the directory


### XDIRENTRY

Get various parameters about dir entry structure

Param:  selector, see below
Return: Value in bytes

#### Selector values

0 = Size of whole directory entry structure
1 = Offset of name in structure
2 = Max number of bytes in name possible (excluding zero terminator)
3 = Offset of type in structure
4 = Size of name field
5 = Size of type field


### fsremove

Remove a file from the filesystem

Param:  Path/Name Zero-terminated C string
Return: 0 on success, non-zero on error


### fsrename(ucell_t old_c_name_ptr, ucell_t new_c_name_ptr);

Rename a file

Param:  Old Path/Name Zero-terminated C string
Param:  New Path/Name Zero-terminated C string
Return: 0 on success, non-zero on error


## IMU Motion Sensor Interface


## BLE Interface


## NeoPixel Interface


## Raw Flash Interface

NOTICE: Using this interface without disabling the filesystem (or changing the addresses of either the 
raw flash or filesystem) will result in data loss!






# Adding User Functionality

There are three ways. 

## 1. The simplest - Forth Blocks on the Target

You can, at runtime, extend the Forth to have custom functions using the blocks facilities. This requires
no extra build steps on the host - and can be entirely extended on the Forth side.
 
You can copy blocks into a text file on the host (using LIST) for backup, and alternative download blocks using 
a termional programs paste facility. You can also EDIT the forth blocks directly on the target. 

REMEMBER to backup the Forth blocks from the target!!! If the target breaks, you don't want to lose your 
application!

## 2. Forth extensions

User functionality can be added in the base Forth dictionary - then you will need to rebuild the core 
dictionary. This will require you to build a Windows/Linux/Mac build from the source code provided using
the make files, as described on the pForth web site. You will then require to rebuild the project using
Sloeber or VS Code as described below.

## 3. C extensions

Obviously you can extend the C core with custom C code, but that is not expected. This requires you build the 
project in an Arduino environmnet such as Sloeber (an Eclipse IDE, projects provided) or Visual Studio Code 
with the correct plug-ins. The standard Arduino IDE will no do because of the folder structure and compiler
commands required.




# Important Note about errors

Some functions return errors. 

However, BLE and Neopixel memory allocation failures will cause a C++ exception, which not if caught, 
and will cause an reset. Consideration was given to returning a zero using new (std::nothrow) to 
avoid exceptions, but it didn't look like a massive improvement - since then the Forth code
because more complex for an error that probably won't happen. So it was left. This strategy probably 
needs to be revewied. 

However, the File System Interface Directory entry doesn't throw errors, and instead returns a 0.



# Notes about files

## Important NOTES about data Loss

If you lose power when writing, then most recent changes will be lost.

Additionally, the device might fail. Perhaps this is a chance event, a flash failure, a static discharge
to the device (by hands, electrical spike or other source) or an overvoltage could cause the device to die
and be unrecoverable.

For both reasons it is critical you backup the data on your device - for example by listing 
all files and saving them to your local machine. It's likely that a failed device 


# General Code Structure

At the core it's a port of pforth with the minimum number of changes.

On top of this we include Arduino & mbed libraries, create C wrappers and export them as part of the custom
function table. We try to make these C wrappers as small as possible. 

The original plan was to build extra forth definitions to support some functions (like Blocks) into a prebuilt 
pfdicdat.h. However, at the moment the pfdicdat.h doesn't contain any Forth definitions beyond standard pForth.

The on chip file system is not used for basic functionality and are entirely available for user extension.



# Future

 * Add more standard Arduino functions
 * Create a split dictionary, so copy to RAM isn't required (maybe just name area, not code area that has variables)
 * Add support for on-board multi-coloured LED
 * Support other features of Arduino Nano 33 BLE Sense board
 * Support BLOCKS as an alternative option to files
 

