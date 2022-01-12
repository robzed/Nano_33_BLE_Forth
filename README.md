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


# Basic Arduino Functions Provided

See https://www.arduino.cc/reference/en/

 * 'ms' - called delay() in Arduino land. ms is the forth standard word.
 * 'millis'
 * 'micros'
 * 'delayMicroseconds'


# Accessing the terminal

pForth uses ANSI escape sequences. These haven't been changed from the original.

This is the command line that I use to access pForth on the Nano 33 BLE:
    picocom --baud 115200 --imap lfcrlf /dev/cu.usbmodem1421201



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


# Blocks Support

## Overview

Since less than half of the flash is used, the second half is used for Forth blocks. Blocks
is a simple system used on Forth to save/load forth definitions. It's much simpler than
a full file system.

The Arduino flash block size for this chip is 4KBytes, which relates to Four 1K Forth blocks.

On loading a single block, internally it also caches another 3 blocks so that it can write
back an entire 4K flash block when saved. The buffers are algined with the flash block start.

You can avoid using any Forth block words, and just use the raw (R/W) word, which reads or writes (actually 
erase then writes) a 4KByte flash block. NOTICE: The first block is 0. 


## Alternatives Considered

Blocks are simple and easy, but not to everyone's liking. File systems (simple records 
or more full filename based) are often better for more advanced purposes. See the comment at 
the top of 'Flash_interface.cpp' for two options that give options more advanced than Blocks. 



## Block Words

The following words will be supported in future:
 * LIST ( u -- ) show the Forth block u, shown as 16 lines of 64 characters.
 * SCR  ( -- addr ) address of a variable that hold the last block shown by list.
 * LOAD ( u -- ) load (interpret) the Forth block u
 * BLOCK ( u -- a-addr) return a buffer for the block. If necessary (not already cached) read the block from Flash
 * BUFFER ( u -- a-addr) return an empty buffer for block
 * UPDATE ( -- ) mark the curr block as to be written.
 * EMPTY-BUFFERS ( -- ) Drop all buffers without saving (effectively mark all internal buffers as unassigned).
 * SAVE-BUFFERS ( -- ) Save all changed blocks to Flash. Mark as not updated.
 * FLUSH ( -- ) save-buffers then empty_buffers
 * RXTEXTBLOCK ( u -- ) write a block from the input terminal directly to a block. LF selects the next line (skipping next 64)
 * (R/W)  (addr u f -- errCode ) Low level Flash block read/write word. flag 1=read, 0=write, addr = buffer address, u=flash block number. Always transfers 4096 bytes!

 Notice buffer address returned by BLOCK and BUFFER are transient. See Forth standard 7.3.2. 
 
 ## Future Block Words

 * EDIT ( -- ) basic screen editor of the current (most recent) block referenced by LIST
 * THRU ( u1 u2 -- ) load (interpret) the Forth blocks u1 to u2, inclusive.
 * UPDATED? ( u -- f ) is the block u is marked updated?
 * EMPTY-BUFFER ( u -- ) drop buffer without saving, losing changes.
 * SAVE-BUFFER ( u -- ) save a specific block to Flash (if changed). Mark as not updated.
 * +LOAD ( u -- ) load the block specified as the current block + u - used with load/thru to chain. NOTE: If current in THRU - this will override. 
 * +THRU ( u1 u2 -- ) load current block + u1 to current block + u2 - used with load/thru to chain. NOTE: If current in THRU - this will override.
 
 ## Block notes

First Forth block number is 1. (But 4K Flash blocks start at 0).

Sometimes 'shadow screens' are used - code in odd block numbers, comments in even block 
numbers, but this is by convention and the block system does not enforce this.  

Typcially block 1 contains a number of thru/load command to load the whole application.

On boot, the Forth system will try to load block 1. Any error will cause it abort the
load and drop back to the command line.

The last character of one 64 byte line wraps straight into the first character of the following line so 
there is no newline, or other line divider in the blocks.  

The word \ (comment to end of line) operates differently for blocks - specifically it causes all characters until the 
end of the current 64-character 'line' to be ignored. This is done with character-position % 64 + 1.

No interpretation is given to characters > 128, so you can set your terminal to UTF-8 if necessary, and
you will get less than 64 characters per line. Conversely you light use Windows-1252 or other 8 bit 
character sets. Obviously if you share code with others you'll need to specify the encoding.

Forth doesn't care - as long as the byte code is >32, it will be fine, except 0xFF is used as a blank flash
in Forth word 'LIST'.



## Important NOTES about Flash wear

Each 4KByte block has 10000 erase/write cycles. Since when a Forth block is written, we 
erase and write all the 

If you use this for normal Forth words or general notes you are 	unlikely to hit this limit. 
e.g. 2 writes for a specfic block every day, would give over 13 years before the 
manufacturer limit was exceeded.

If you are going to use these for settings (some sort of non-volatile storage of sensor readings, 
mode, set state, then you will need to use some more advanced methodology - depending on 
the frequency of writing your data. In fact, you might want to NOT use Forth blocks 
for this use, since multiple writes are allowed to a single Flash block before an erase - but 
not by this Forth block system. This is outside of the scope of this Forth, but it's 
generally provided by wear leveling file systems, or specific NVM emulation for flash 
functions. Please see the Nordic documentation for details and potential application notes.

## Important NOTES about Power Loss

If you lose power when writing, then the four Forth blocks are at risk of being lost - both
old and new. It is critical you backup the data on your device - for example by listing
all blocks and saving them to your local machine. 


# Important Note about errors

Some functions return errors. 

However, BLE or Neopixel memory allocation failures will cause a C++ exception, which not if caught, 
and will cause an reset. Consideration was given to returning a zero using new (std::nothrow) to 
avoid exceptions, but it didn't look like a massive improvement - since then the Forth code
because more complex for an error that probably won't happen. So it was left. This strategy probably 
needs to be revewied. 




# General Code Structure

At the core it's a port of pforth with the minimum number of changes.

On top of this we include Arduino & mbed libraries, create C wrappers and export them as part of the custom
function table. We try to make these C wrappers as small as possible. 

We then build forth definitions to support some functions (like Blocks) into a prebuilt pfdicdat.h.

The forth blocks are not used for basic functionality and are entirely available for user extension.



# Future

 * Add more standard Arduino functions
 * Create a split dictionary, so copy to RAM isn't required (maybe just name area, not code area that has variables)
 * Add support for multi-coloured LED
 * Support other features of Arduino Nano 33 BLE Sense board

