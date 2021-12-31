Overall
=======

The CortexM4F on the Arduino Nano 33 BLE has hardware single-precision floating point support - hence this build enables floating point support and switches the build to single precision. We also warnings for double precision promotion so we can see where it will use software double precision support. This leads to some additional warning in the pForth code, but nothing problematic.


Command Line Build Options
===========================

We use (for both C and C++)

    -DPF_SUPPORT_FP -DPF_NO_FILEIO -DPF_NO_INIT -DPF_NO_STDIO -DPF_USER_CHARIO="../../user_chario.h"  -I../pre_built -DPF_USER_CUSTOM="nano33ble_custom.c"
    
        
    
We use malloc/free and CLIB currently.
    

For C:
    --std=c99 -fsigned-char -fno-builtin -fno-unroll-loops -fno-keep-inline-functions -pedantic -Wcast-qual -Wall -Wwrite-strings -Winline -Wmissing-prototypes -Wmissing-declarations -Wdouble-promotion


pf_all.h includes PF_EMBEDDED. This defines:

    PF_NO_INIT - Don't compile the code used to initially build the dictionary. This can be used to save space if you already have a prebuilt dictionary. 

    PF_NO_STDIO -  stdio.h Only used for ERR(msg) which is a print

    PF_NO_MALLOC - Replace malloc() and free() function with pForth's own version. See pf_mem.c for more details. 

    PF_NO_CLIB - Replace 'C' lib calls like toupper and memcpy with pForth's own version. This is useful for embedded systems. 
    
    PF_NO_FILEIO - System does not support standard file I/O so stub it out. Setting this flag will automatically set PF_STATIC_DIC. 

    PF_STATIC_DIC - Compile in static dictionary instead of loading dictionary. from file. Use "utils/savedicd.fth" to save a dictionary as 'C' source code in a file called "pfdicdat.h". 

We only use *some* of these, see above.


Enable hardware floating point
===============================


-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
 
As per README file that come with gcc toolchains and https://stackoverflow.com/questions/16768235/cortex-m4-gcc-float-behavior

 
Warn about double promotion
===========================
 
-Wdouble-promotion
 
 
pForth Specfic changes
====================== 

in 'pf_float.h':
    typedef float PF_FLOAT;


in 'rf_inc1.h':
    /* #define NULL  ((void *) 0) */
    
    
in 'rf_io.h'

         #define STRINGIFY_MACRO(x) STR_(x)
         #define STR_(x) #x

         #include STRINGIFY_MACRO(PF_USER_CHARIO)

Current Build Command Line (for reference)
==========================================

C build line:

"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4/bin/arm-none-eabi-gcc" -c  -g3 -nostdlib "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/defines.txt" "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/cflags.txt" -DARDUINO_ARCH_NRF52840 -MMD -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARDUINO=10812 -DARDUINO_ARDUINO_NANO33BLE -DARDUINO_ARCH_MBED_NANO -DARDUINO_ARCH_MBED -DARDUINO_LIBRARY_DISCOVERY_PHASE=0    "-I/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/api/deprecated" "-I/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/api/deprecated-avr-comp"  "-iprefix/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino" "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/includes.txt"  -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/ArduinoLang/0.1.0/src" -I"/Users/rob/Documents/Arduino/libraries/ArduinoBLE/src" -I"/Users/rob/Documents/Arduino/libraries/Adafruit_NeoPixel" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/BLEPeripheral/0.4.0/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/TimerOne/1.1.0" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/IRremote/3.5.1/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Keypad/3.1.1/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Encoder/1.4.2" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Encoder/1.4.2/utility" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Arduino_LSM9DS1/1.1.0/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/libraries/Wire" -MMD -MP -MF"core/core/arm_hal_random.c.d" -MT"core/core/arm_hal_random.c.o" -D__IN_ECLIPSE__=1 "/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/arm_hal_random.c"   -o "core/core/arm_hal_random.c.o"  -DPF_SUPPORT_FP -DPF_NO_FILEIO -DPF_NO_INIT -DPF_NO_STDIO -DPF_USER_CHARIO="../../user_chario.h" -I../pre_built -DPF_USER_CUSTOM="nano33ble_custom.c" --std=c99 -fsigned-char -fno-builtin -fno-unroll-loops -fno-keep-inline-functions -pedantic -Wcast-qual -Wall -Wwrite-strings -Winline -Wmissing-prototypes -Wmissing-declarations -Wdouble-promotion

C++ build line

"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4/bin/arm-none-eabi-g++" -c  -g3 -nostdlib "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/defines.txt" "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/cxxflags.txt" -DARDUINO_ARCH_NRF52840 -MMD -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARDUINO=10812 -DARDUINO_ARDUINO_NANO33BLE -DARDUINO_ARCH_MBED_NANO -DARDUINO_ARCH_MBED -DARDUINO_LIBRARY_DISCOVERY_PHASE=0     "-I/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/api/deprecated" "-I/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/api/deprecated-avr-comp" "-iprefix/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino" "@/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE/includes.txt"  -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/variants/ARDUINO_NANO33BLE" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/ArduinoLang/0.1.0/src" -I"/Users/rob/Documents/Arduino/libraries/ArduinoBLE/src" -I"/Users/rob/Documents/Arduino/libraries/Adafruit_NeoPixel" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/BLEPeripheral/0.4.0/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/TimerOne/1.1.0" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/IRremote/3.5.1/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Keypad/3.1.1/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Encoder/1.4.2" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Encoder/1.4.2/utility" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/libraries/Arduino_LSM9DS1/1.1.0/src" -I"/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/libraries/Wire" -MMD -MP -MF"core/core/WMath.cpp.d" -MT"core/core/WMath.cpp.o" -D__IN_ECLIPSE__=1 -x c++ "/Users/rob/eclipse/Sloeber.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/mbed_nano/2.6.1/cores/arduino/WMath.cpp"   -o "core/core/WMath.cpp.o"  -DPF_SUPPORT_FP -DPF_NO_FILEIO -DPF_NO_INIT -DPF_NO_STDIO -DPF_USER_CHARIO="../../user_chario.h" -I../pre_built -DPF_USER_CUSTOM="nano33ble_custom.c"


          
          
Current warnings
================

pforth - Apart from the double precision promotion warnings, there is a warning about signed/unsigned comparison in pf_inner.c on the line if ( TOS < sizeof(cell_t) ).

Arduino - the libraries have two warnings.


Building Unix version to create dictionary for embedded build
=============================================================

Go into the correct directory:
    cd platforms
    cd unix   
    
The Makefile has been changed to do the correct thing.
    make
    
Test pForth by running:
    ./pforth

It displays
    PForth V28-LE/64, built Dec 30 2021 22:28:58
    pForth loading dictionary from file pforth.dic
         File format version is 10 
         Name space size = 120000 
         Code space size = 300000 
         Entry Point     = 0 
         Cell Size       = 8 
         Little  Endian Dictionary

Move the pre-made dictionary (pfdicdat.h) from the build directory (unix) to premade/ folder.

Clean and rebuild BLE project.


 