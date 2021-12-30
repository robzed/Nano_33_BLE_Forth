/*
 * Neopixel_interface.h
 *
 *  Created on: 22 Dec 2021
 *      Author: Probin
 *      License: MIT
 *
 */

#ifndef NEOPIXEL_INTERFACE_H_
#define NEOPIXEL_INTERFACE_H_

#include "pforth-master/csrc/pf_all.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
neoPixelType NeoPixel_RGB(void);
neoPixelType NeoPixel_RBG(void);
neoPixelType NeoPixel_GRB(void);
neoPixelType NeoPixel_GBR(void);
neoPixelType NeoPixel_BRG(void);
neoPixelType NeoPixel_BGR(void);

neoPixelType NeoPixel_WRGB(void);
neoPixelType NeoPixel_WRBG(void);
neoPixelType NeoPixel_WGRB(void);
neoPixelType NeoPixel_WGBR(void);
neoPixelType NeoPixel_WBRG(void);
neoPixelType NeoPixel_WBGR(void);

neoPixelType NeoPixel_RWGB(void);
neoPixelType NeoPixel_RWBG(void);
neoPixelType NeoPixel_RGWB(void);
neoPixelType NeoPixel_RGBW(void);
neoPixelType NeoPixel_RBWG(void);
neoPixelType NeoPixel_RBGW(void);

neoPixelType NeoPixel_GWRB(void);
neoPixelType NeoPixel_GWBR(void);
neoPixelType NeoPixel_GRWB(void);
neoPixelType NeoPixel_GRBW(void);
neoPixelType NeoPixel_GBWR(void);
neoPixelType NeoPixel_GBRW(void);

neoPixelType NeoPixel_BWRG(void);
neoPixelType NeoPixel_BWGR(void);
neoPixelType NeoPixel_BRWG(void);
neoPixelType NeoPixel_BRGW(void);
neoPixelType NeoPixel_BGWR(void);
neoPixelType NeoPixel_BGRW(void);

neoPixelType NeoPixel_KHZ800(void);
neoPixelType NeoPixel_KHZ400(void);
*/

// Constructor: number of LEDs, pin number, LED type
ucell_t NeoPixel_create(ucell_t num_leds, cell_t pin, ucell_t type);
ucell_t NeoPixel_create_default(void);
void NeoPixel_destroy(ucell_t object);


// pass in a type string and get a type
cell_t NeoPixel_getPixelType(cell_t str, ucell_t len);


// should we provide a method where these can be allocated on the dictionary?
//size_t sizeof_NeoPixel(void);
//void* create_NeoPixel_fixed_(void* storage, uint16_t num_leds, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800);
//void* create_NeoPixel_default_fixed(void* storage)
//void destroy_NeoPixel_fixed(void* object);

// see the Adafruit_NeoPixel class for descriptions
void NeoPixel_begin(ucell_t object);
void NeoPixel_show(ucell_t object);
void NeoPixel_setPin(ucell_t object, cell_t p);
void NeoPixel_setPixelColor(ucell_t object, ucell_t n, ucell_t r, ucell_t g, ucell_t b);
void NeoPixel_setPixelColorW(ucell_t object, ucell_t n, ucell_t r, ucell_t g, ucell_t b, ucell_t w);
void NeoPixel_setPixelColor32(ucell_t object, ucell_t n, ucell_t c);
void NeoPixel_fill(ucell_t object, ucell_t c, ucell_t first, ucell_t count);
void NeoPixel_setBrightness(ucell_t object, ucell_t brightness);
void NeoPixel_clear(ucell_t object);
void NeoPixel_updateLength(ucell_t object, ucell_t n);
void NeoPixel_updateType(ucell_t object, ucell_t t);

ucell_t NeoPixel_canShow(ucell_t object);
ucell_t NeoPixel_getPixels(ucell_t object);
ucell_t NeoPixel_getBrightness(ucell_t object);
cell_t NeoPixel_getPin(ucell_t object);
ucell_t NeoPixel_numPixels(ucell_t object);
ucell_t NeoPixel_getPixelColor(ucell_t object, ucell_t n);
ucell_t NeoPixel_sine8(ucell_t x);
ucell_t NeoPixel_gamma8(ucell_t x);
ucell_t NeoPixel_Color(ucell_t r, ucell_t g, ucell_t b);
ucell_t NeoPixel_ColorW(ucell_t r, ucell_t g, ucell_t b, ucell_t w);
ucell_t NeoPixel_ColorHSV(ucell_t hue, ucell_t sat, ucell_t val);
ucell_t NeoPixel_gamma32(ucell_t x);
void NeoPixel_rainbow(ucell_t object, ucell_t first_hue, cell_t reps,
		ucell_t saturation, ucell_t brightness,
		ucell_t gammify);

#ifdef __cplusplus
}
#endif



#endif /* NEOPIXEL_INTERFACE_H_ */
