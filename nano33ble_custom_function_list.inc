/*
 * nano33ble_custom_function_list.h
 *
 *  Created on: 21 Jan 2022
 *      Author: Rob Probin
 */

/* Compile Forth words that call your custom functions.
** Make sure order of functions matches that in LoadCustomFunctionTable().
** Parameters are: Name in UPPER CASE, Function, Index, Mode, NumParams
*/


	/* helper functions	*/
	X( Arduino_IFVer, "ARDUINO-IFVER", 					C_RETURNS_VALUE, 0, "( -- u ) return version of Arduino interface" ) // @suppress("Symbol is not resolved")

	/* Arduino functions */
	X( ARDUINO_delay, "MS", 							C_RETURNS_VOID , 1, "( u -- ) delay milliseconds" )
	X( ARDUINO_delayMicroseconds, "DELAYMICROSECONDS", 	C_RETURNS_VOID , 1, "( u -- ) delay microseconds" )
	X( ARDUINO_micros, "MICROS", 						C_RETURNS_VALUE, 0, "( -- u ) return microseconds" )
	X( ARDUINO_millis, "MILLIS", 						C_RETURNS_VALUE, 0, "( -- u ) return milliseconds" )
	X( heap_stats, "HEAP_STATS",						C_RETURNS_VALUE, 0, "( -- a-addr ) pointer to Mbed heap status")

	/* Neopixel functions */
	X( NeoPixel_create, "NP_CREATE", 					C_RETURNS_VALUE, 3, "( #leds pin type -- np-address ) create a neopixel" )
	X( NeoPixel_create_default, "NP_CREATE_DEFAULT", 	C_RETURNS_VALUE, 0, "( -- np-address ) create a neopixel" )
	X( NeoPixel_destroy, "NP_DESTROY", 					C_RETURNS_VOID , 1, "( np-address -- ) destroy a neopixel" )

	X( NeoPixel_getPixelType, "NP_GETPIXELTYPE",		C_RETURNS_VALUE, 2, "( str-addr len -- type ) e.g. RGB or KHZ800" )

	X( NeoPixel_begin, "NP_BEGIN", 						C_RETURNS_VOID , 1, "( np-address -- ) configure outputs" )
	X( NeoPixel_show, "NP_SHOW", 						C_RETURNS_VOID , 1, "( np-address -- ) output pixel data" )
	X( NeoPixel_setPin, "NP_SETPIN", 					C_RETURNS_VOID , 2, "( np-address pin -- ) set pin" )
	X( NeoPixel_setPixelColor, "NP_SETPIXELCOLOR", 		C_RETURNS_VOID , 5, "( np-address n r g b -- ) set colour" )
	X( NeoPixel_setPixelColorW, "NP_SETPIXELCOLORW", 	C_RETURNS_VOID , 6, "( np-address n r g b w -- ) set colour" )
	X( NeoPixel_setPixelColor32, "NP_SETPIXELCOLOR32", 	C_RETURNS_VOID , 3, "( np-address n c -- ) set colour" )
	X( NeoPixel_fill, "NP_FILL", 						C_RETURNS_VOID , 4, "( np-address c first count -- ) fill pixels with colour" )
	X( NeoPixel_setBrightness, "NP_SETBRIGHTNESS", 		C_RETURNS_VOID , 2, "( np-address u8 -- ) description" )
	X( NeoPixel_clear, "NP_CLEAR", 						C_RETURNS_VOID , 1, "( np-address -- ) clear pixels" )
	X( NeoPixel_updateLength, "NP_UPDATELENGTH", 		C_RETURNS_VOID , 2, "( np-address u16 -- ) change length" )
	X( NeoPixel_updateType, "NP_UPDATETYPE", 			C_RETURNS_VOID , 2, "( np-address u -- ) change type" )

	X( NeoPixel_canShow, "NP_CANSHOW", 					C_RETURNS_VALUE, 1, "( np-address -- flag ) show immediately or block" )
	X( NeoPixel_getPixels, "NP_GETPIXELS", 				C_RETURNS_VALUE, 1, "( np-address -- pixel-addr) get pixels" )
	X( NeoPixel_getBrightness, "NP_GETBRIGHTNESS", 		C_RETURNS_VALUE, 1, "( np-address -- u8 ) get brightness" )
	X( NeoPixel_getPin, "NP_GETPIN", 					C_RETURNS_VALUE, 1, "( np-address -- i16 ) get pin" )
	X( NeoPixel_numPixels, "NP_NUMPIXELS", 				C_RETURNS_VALUE, 1, "( np-address -- u16 ) get number of pixels" )
	X( NeoPixel_getPixelColor, "NP_GETPIXELCOLOR", 		C_RETURNS_VALUE, 2, "( np-address u16 -- u32 ) previously set pixel" )
	X( NeoPixel_sine8, "NP_SINE8", 						C_RETURNS_VALUE, 1, "( np-address u8 -- u8 ) sine table get" )
	X( NeoPixel_gamma8, "NP_GAMMA8", 					C_RETURNS_VALUE, 1, "( np-address u8 -- u8 ) input brightness to adjusted" )
	X( NeoPixel_Color, "NP_COLOR", 						C_RETURNS_VALUE, 3, "( np-address r g b -- u32 ) get colour" )
	X( NeoPixel_ColorW, "NP_COLORW", 					C_RETURNS_VALUE, 4, "( np-address r g b w -- u32 ) get colour" )
	X( NeoPixel_ColorHSV, "NP_COLORHSV", 				C_RETURNS_VALUE, 3, "( np-address hue sat val -- u32 ) get HSV colour" )
	X( NeoPixel_gamma32, "NP_GAMMA32", 					C_RETURNS_VALUE, 1, "( np-address u32 -- u32 ) gamma correct" )
	X( NeoPixel_rainbow, "NP_RAINBOW", 					C_RETURNS_VOID , 6, "( np-address hue1 reps sat bright gammify-flag -- ) make a rainbow" )

	/* BLE functions */
	X( BLE_event_fetch,  "BLE_EVENT@", 					C_RETURNS_VALUE, 2, "( dev-addr-out char-addr-out -- xt | 0) a BLE event, if any or 0" )
	X( BLESERVICE, "BLESERVICE", 						C_RETURNS_VALUE, 1, "( c-addr-uuid -- service-addr ) create a BLE serivice" )
	X( BLESERVICE_ADDCHARACTERISTIC, "BLESERVICE+CHAR", C_RETURNS_VOID , 2, "( service-addr char-addr -- ) add a characteristic to a service" )
	X( BLESERVICE_CHARACTERISTICCOUNT, "BLESERVICE#CHAR", C_RETURNS_VALUE, 1, "( service-addr -- u ) n = #characteristics" )
	X( BLECHAR, "BLECHAR", 								C_RETURNS_VALUE , 4, "( c-addr-uuid properties size fixed-flag -- char-addr ) create a characteristic" )
	X( BLECHAR_WRITEVALUE, "BLECHAR!", 					C_RETURNS_VALUE, 3, "( char-addr value len -- success-flag ) write characteristic " )
	X( BLECHAR_READVALUE, "BLECHAR@", 					C_RETURNS_VALUE, 3, "( char-addr value len -- #bytes ) read-characteristic" )
	X( BLECHAR_SETEVENTHANDLER, "BLECHAR_EVENTHANDLER!",C_RETURNS_VOID , 3, "( char-addr event xt -- ) set handler for characteristic event" )
	X( BLECHAR_ADDDESCRIPTOR, "BLECHAR+DESCRIP", 		C_RETURNS_VOID , 2, "( char-addr descr-addr -- ) add a description to a characteristic" )
	X( BLEDESCRIPTOR, "BLEDESCRIPTOR", 					C_RETURNS_VALUE, 3, "( uuid_c-addr c-addr len -- descr-addr ) create descriptor" )
	X( BLE_BEGIN, "BLE_BEGIN", 							C_RETURNS_VALUE, 0, "( -- sucess-flag ) init BLE device" )
	X( BLE_END, "BLE_END", 								C_RETURNS_VOID , 0, "( -- ) stop BLE device" )
	X( BLE_POLL, "BLE_POLL", 							C_RETURNS_VOID , 1, "( timeout|0 -- ) Poll for BLE radio events and handle them" )
	X( BLE_SETEVENTHANDLER, "BLE_EVENTHANDLER!", 					C_RETURNS_VOID , 2, "( device-addr xt -- ) add handler for BLE event" )
	X( BLE_CONNECTED, "BLE_CONNECTED", 								C_RETURNS_VALUE, 0, "( -- connected-flag ) is another device connected?" )
	X( BLE_DISCONNECT, "BLE_DISCONNECT", 							C_RETURNS_VALUE, 0, "( -- prev-connected-flag ) disconnect any devices connected, flag is previously connected" )
	X( BLE_ADDRESS, "BLE_ADDRESS", 									C_RETURNS_VALUE, 0, "( -- c-addr ) get device address as string" )
	X( BLE_RSSI, "BLE_RSSI", 										C_RETURNS_VALUE, 0, "( -- n ) return RSSI" )
	X( BLE_SETADVERTISEDSERVICEUUID, "BLE_SETADVERTISEDSERVICEUUID",C_RETURNS_VALUE, 1, "( uuid-c-addr -- success-flag ) set service UUID when advertising" )
	X( BLE_SETADVERTISEDSERVICE, "BLE_SETADVERTISEDSERVICE", 		C_RETURNS_VALUE, 1, "( service-addr -- success-flag ) set service UUID when advertising" )
	X( BLE_SETMANUFACTURERDATA, "BLE_SETMANUFACTURERDATA", 			C_RETURNS_VALUE, 2, "( c-addr len -- success-flag ) set manufacturing data when advertising" )
	X( BLE_SETLOCALNAME, "BLE_SETLOCALNAME", 						C_RETURNS_VOID , 1, "( c-addr -- ) set local name when advertising" )
	X( BLE_SETDEVICENAME, "BLE_SETDEVICENAME", 						C_RETURNS_VOID , 1, "( c-addr -- ) set device name in device name characteristic" )
	X( BLE_SETAPPEARANCE, "BLE_SETAPPEARANCE", 						C_RETURNS_VOID , 1, "( u16 -- ) Set the appearance in the built in appearance characteristic" )
	X( BLE_ADDSERVICE, "BLE_ADDSERVICE", 							C_RETURNS_VOID , 1, "( service-addr -- ) description" )
	X( BLE_ADVERTISE, "BLE_ADVERTISE", 								C_RETURNS_VALUE, 0, "( -- success-flag ) start advertising" )
	X( BLE_STOPADVERTISE, "BLE_STOPADVERTISE", 						C_RETURNS_VOID , 0, "( -- ) stop advertising" )
	X( BLE_CENTRAL, "BLE_CENTRAL", 									C_RETURNS_VALUE, 0, "( -- device-addr ) return BLEDevice representing the central. " )
	X( BLE_SETADVERTISINGINTERVAL, "BLE_SETADVERTISINGINTERVAL", 	C_RETURNS_VOID , 1, "( u16 -- ) set advertising interval in 0.625ms steps" )
	X( BLE_SETCONNECTIONINTERVAL, "BLE_SETCONNECTIONINTERVAL", 		C_RETURNS_VOID , 2, "( min-u16 max-u16 -- ) Set the minimum and maximum desired connection intervals in units of 1.25 ms" )
	X( BLE_SETCONNECTABLE, "BLE_SETCONNECTABLE", 					C_RETURNS_VOID , 1, "( flag -- ) Set if the device is connectable after advertising" )
	X( BLE_SCAN, "BLE_SCAN", 										C_RETURNS_VALUE, 1, "( with-duplicates-flag -- ) scan for devices" )
	X( BLE_SCANFORNAME, "BLE_SCANFORNAME", 							C_RETURNS_VALUE, 3, "( name-c-addr len with-duplicates-flag -- ) scan for devices with a name" )
	X( BLE_SCANFORADDRESS, "BLE_SCANFORADDRESS", 					C_RETURNS_VALUE, 3, "( addr-c-addr len with-duplicates-flag -- ) scan for devices with an address" )
	X( BLE_SCANFORUUID, "BLE_SCANFORUUID", 							C_RETURNS_VALUE, 3, "( uuid-c-addr len with-duplicates-flag -- ) scan for devices with a uuid" )
	X( BLE_STOPSCAN, "BLE_STOPSCAN", 								C_RETURNS_VOID , 0, "( -- ) stop scan" )
	X( BLE_AVAILABLE, "BLE_AVAILABLE", 								C_RETURNS_VALUE, 0, "( -- device-addr) get scan device" )

	/* Flash functions */
	X( read_write_flash_size, "(R/W_Size)", 			C_RETURNS_VALUE, 0, "( -- u ) flash block size" )
	X( number_of_flash_blocks, "(R/W_#Blocks)", 		C_RETURNS_VALUE, 0, "( -- u ) Number of flash blocks available" )
	X( read_write_flash_block, "(R/W)", 				C_RETURNS_VALUE, 3, "( buffer-addr block# read? -- error ) read or write flash block" )

	/* IMU functions, also see https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/ */
	X( IMU_begin, "IMU_BEGIN", 										C_RETURNS_VALUE, 0, "( -- success-flag ) init IMU" )
	X( IMU_end, "IMU_END", 											C_RETURNS_VOID , 0, "( -- ) deinit IMU" )
	X( IMU_readAcceleration, "IMU_READACCELERATION", 				C_RETURNS_VALUE, 3, "( x-addr-out y-addr-out z-addr-out -- success-flag ) read acceleration" )
	X( IMU_readGyroscope, "IMU_READGYROSCOPE", 						C_RETURNS_VALUE, 3, "( x-addr-out y-addr-out z-addr-out -- success-flag ) read gyro" )
	X( IMU_accelerationAvailable, "IMU_ACCELERATIONAVAILABLE", 		C_RETURNS_VALUE, 0, "( -- new-data-flag ) new data available?" )
	X( IMU_gyroscopeAvailable, "IMU_GYROSCOPEAVAILABLE", 			C_RETURNS_VALUE, 0, "( -- new-data-flag ) new data available?" )
	X( IMU_accelerationSampleRate, "IMU_ACCELERATIONSAMPLERATE", 	C_RETURNS_VOID , 1, "( float-addr-out -- ) read sample rate in Hz" )
	X( IMU_gyroscopeSampleRate, "IMU_GYROSCOPESAMPLERATE",			C_RETURNS_VOID , 1, "( float-addr-out -- ) read sample rate in Hz" )
	X( IMU_readMagneticField, "IMU_READMAGNETICFIELD", 				C_RETURNS_VALUE, 3, "( x-addr-out y-addr-out z-addr-out -- success-flag ) read magnetic field" )
	X( IMU_magneticFieldSampleRate, "IMU_MAGNETICFIELDSAMPLERATE", 	C_RETURNS_VOID , 1, "( float-addr-out -- ) read sample rate in Hz" )
	X( IMU_magneticFieldAvailable, "IMU_MAGNETICFIELDAVAILABLE", 	C_RETURNS_VALUE, 0, "( -- new-data-flag ) new data available?" )

	X( filesystem_mkdir, "MKDIR", C_RETURNS_VALUE, 2, "( c-name mode -- error ) ")
	X( filesystem_opendir, "OPENDIR", C_RETURNS_VALUE, 1, "( c-name -- dir ) ")
	X( filesystem_readdir, "READDIR", C_RETURNS_VALUE, 2, "( dir entry -- status ) ")
	X( filesystem_closedir, "CLOSEDIR", C_RETURNS_VALUE, 1, "( dir -- error ) ")
	X( filesystem_sizedir, "#DIR", C_RETURNS_VALUE, 1, "( dir -- u ) ")
	X( filesystem_sizedirentry, "XDIRENTRY", C_RETURNS_VALUE, 1, "( selector -- size ) ")
#ifdef SEPERATE_REMOVE_RENAME
	X( filesystem_fsremove, "FSREMOVE", C_RETURNS_VALUE, 1, "( c-name -- dir ) ")
	X( filesystem_fsrename, "FSRENAME", C_RETURNS_VALUE, 2, "( old-c-name new-c-name -- dir ) ")
#endif
	X( filesystem_stat, "FSSTAT", C_RETURNS_VALUE, 2, "( c-name output_buff -- error ) ")
	X( filesystem_statvfs, "FSSTATVFS", C_RETURNS_VALUE, 2, "( c-name output_buff -- error ) ")
	X( filesystem_XFSSTAT, "XFSSTAT", C_RETURNS_VALUE, 1, "( selector -- size ) ")
	X( filesystem_XFSSTATVFS, "XFSSTATVFS", C_RETURNS_VALUE, 1, "( selector -- size ) ")

// End of CUSTOM_FUNCTION_LIST list of custom functions, names, etc.


