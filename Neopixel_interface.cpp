/*
 * Neopixel_interface.cpp
 *
 *  Created on: 22 Dec 2021
 *      Author: Rob Probin
 */

#include "Neopixel_interface.h"
#include <string.h>
#include "pforth-master/csrc/pf_all.h"
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <Adafruit_NeoPixel.h>
#undef MIN
#undef MAX
#undef CODE_SIZE

/*
neoPixelType NeoPixel_RGB(void) { return NEO_RGB; }
neoPixelType NeoPixel_RBG(void) { return NEO_RBG; }
neoPixelType NeoPixel_GRB(void) { return NEO_GRB; }
neoPixelType NeoPixel_GBR(void) { return NEO_GBR; }
neoPixelType NeoPixel_BRG(void) { return NEO_BRG; }
neoPixelType NeoPixel_BGR(void) { return NEO_BGR; }

neoPixelType NeoPixel_WRGB(void) { return NEO_WRGB; }
neoPixelType NeoPixel_WRBG(void) { return NEO_WRBG; }
neoPixelType NeoPixel_WGRB(void) { return NEO_WGRB; }
neoPixelType NeoPixel_WGBR(void) { return NEO_WGBR; }
neoPixelType NeoPixel_WBRG(void) { return NEO_WBRG; }
neoPixelType NeoPixel_WBGR(void) { return NEO_WBGR; }

neoPixelType NeoPixel_RWGB(void) { return NEO_RWGB; }
neoPixelType NeoPixel_RWBG(void) { return NEO_RWBG; }
neoPixelType NeoPixel_RGWB(void) { return NEO_RGWB; }
neoPixelType NeoPixel_RGBW(void) { return NEO_RGBW; }
neoPixelType NeoPixel_RBWG(void) { return NEO_RBWG; }
neoPixelType NeoPixel_RBGW(void) { return NEO_RBGW; }

neoPixelType NeoPixel_GWRB(void) { return NEO_GWRB; }
neoPixelType NeoPixel_GWBR(void) { return NEO_GWBR; }
neoPixelType NeoPixel_GRWB(void) { return NEO_GRWB; }
neoPixelType NeoPixel_GRBW(void) { return NEO_GRBW; }
neoPixelType NeoPixel_GBWR(void) { return NEO_GBWR; }
neoPixelType NeoPixel_GBRW(void) { return NEO_GBRW; }

neoPixelType NeoPixel_BWRG(void) { return NEO_BWRG; }
neoPixelType NeoPixel_BWGR(void) { return NEO_BWGR; }
neoPixelType NeoPixel_BRWG(void) { return NEO_BRWG; }
neoPixelType NeoPixel_BRGW(void) { return NEO_BRGW; }
neoPixelType NeoPixel_BGWR(void) { return NEO_BGWR; }
neoPixelType NeoPixel_BGRW(void) { return NEO_BGRW; }

neoPixelType NeoPixel_KHZ800(void) { return NEO_KHZ800; }
neoPixelType NeoPixel_KHZ400(void) { return NEO_KHZ400; }
*/

typedef struct {
	const char* key;
	neoPixelType value;
} pixel_type_array_t;

static const pixel_type_array_t pixel_type_array[] = {
	{ "RGB", NEO_RGB },
	{ "RBG", NEO_RBG },
	{ "GRB", NEO_GRB },
	{ "GBR", NEO_GBR },
	{ "BRG", NEO_BRG },
	{ "BGR", NEO_BGR },

	{ "WRGB", NEO_WRGB },
	{ "WRBG", NEO_WRBG },
	{ "WGRB", NEO_WGRB },
	{ "WGBR", NEO_WGBR },
	{ "WBRG", NEO_WBRG },
	{ "WBGR", NEO_WBGR },

	{ "RWGB", NEO_RWGB },
	{ "RWBG", NEO_RWBG },
	{ "RGWB", NEO_RGWB },
	{ "RGBW", NEO_RGBW },
	{ "RBWG", NEO_RBWG },
	{ "RBGW", NEO_RBGW },

	{ "GWRB", NEO_GWRB },
	{ "GWBR", NEO_GWBR },
	{ "GRWB", NEO_GRWB },
	{ "GRBW", NEO_GRBW },
	{ "GBWR", NEO_GBWR },
	{ "GBRW", NEO_GBRW },

	{ "BWRG", NEO_BWRG },
	{ "BWGR", NEO_BWGR },
	{ "BRWG", NEO_BRWG },
	{ "BRGW", NEO_BRGW },
	{ "BGWR", NEO_BGWR },
	{ "BGRW", NEO_BGRW },

	{ "KHZ800", NEO_KHZ800 },
	{ "KHZ400", NEO_KHZ400 },
};


//neoPixelType NeoPixel_getPixelType(const char* s, int len)
cell_t NeoPixel_getPixelType(cell_t str, ucell_t len)
{
	// maybe should use a map here?
	const char* s = (const char*) str;
	for(size_t i=0; i<sizeof(pixel_type_array)/sizeof(pixel_type_array_t); i++)
	{
		const char* key = pixel_type_array[i].key;
		neoPixelType value = pixel_type_array[i].value;
		ucell_t key_len = strlen(key);
		if(key_len == len && memcmp(key, s, len) == 0)
		{
			return value;
		}
	}
	return 0;
}


//void* NeoPixel_create(uint16_t num_leds, int16_t pin, neoPixelType type)
ucell_t NeoPixel_create(ucell_t num_leds, cell_t pin, ucell_t type)
{
	return (ucell_t) new Adafruit_NeoPixel(num_leds, pin, type);
}

//void* NeoPixel_create_default(void)
ucell_t NeoPixel_create_default(void)
{
	return (ucell_t) new Adafruit_NeoPixel();
}

//void NeoPixel_destroy(void* object)
void NeoPixel_destroy(ucell_t object)
{
	delete reinterpret_cast<Adafruit_NeoPixel*>(object);
}

//void NeoPixel_begin(void* object)
void NeoPixel_begin(ucell_t object)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->begin();
}
//void NeoPixel_show(void* object)
void NeoPixel_show(ucell_t object)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->show();
}

//void NeoPixel_setPin(void* object, int16_t p)
void NeoPixel_setPin(ucell_t object, cell_t p)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->setPin(p);
}

//void NeoPixel_setPixelColor(void* object, uint16_t n, uint8_t r, uint8_t g, uint8_t b)
void NeoPixel_setPixelColor(ucell_t object, ucell_t n, ucell_t r, ucell_t g, ucell_t b)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->setPixelColor(n, r, g, b);
}

//void NeoPixel_setPixelColorW(void* object, uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
void NeoPixel_setPixelColorW(ucell_t object, ucell_t n, ucell_t r, ucell_t g, ucell_t b, ucell_t w)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->setPixelColor(n, r, g, b, w);
}

//void NeoPixel_setPixelColor32(void* object, uint16_t n, uint32_t c)
void NeoPixel_setPixelColor32(ucell_t object, ucell_t n, ucell_t c)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->setPixelColor(n, c);
}

//void NeoPixel_fill(void* object, uint32_t c, uint16_t first, uint16_t count)
void NeoPixel_fill(ucell_t object, ucell_t c, ucell_t first, ucell_t count)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->fill(c, first, count);
}

//void NeoPixel_setBrightness(void* object, uint8_t brightness)
void NeoPixel_setBrightness(ucell_t object, ucell_t brightness)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->setBrightness(brightness);
}

//void NeoPixel_clear(void* object)
void NeoPixel_clear(ucell_t object)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->clear();
}

//void NeoPixel_updateLength(void* object, uint16_t n)
void NeoPixel_updateLength(ucell_t object, ucell_t n)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->updateLength(n);
}

//void NeoPixel_updateType(void* object, neoPixelType t)
void NeoPixel_updateType(ucell_t object, ucell_t t)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->updateType(t);
}

//bool NeoPixel_canShow(void* object)
ucell_t NeoPixel_canShow(ucell_t object)
{
	return reinterpret_cast<Adafruit_NeoPixel*>(object)->canShow()?-1:0;
}

//uint8_t* NeoPixel_getPixels(void* object)
ucell_t NeoPixel_getPixels(ucell_t object)
{
	return (ucell_t)reinterpret_cast<Adafruit_NeoPixel*>(object)->getPixels();
}

//uint8_t NeoPixel_getBrightness(void* object)
ucell_t NeoPixel_getBrightness(ucell_t object)
{
	return reinterpret_cast<Adafruit_NeoPixel*>(object)->getBrightness();
}

//int16_t NeoPixel_getPin(void* object)
cell_t NeoPixel_getPin(ucell_t object)
{
	return reinterpret_cast<Adafruit_NeoPixel*>(object)->getPin();
}

//uint16_t NeoPixel_numPixels(void* object)
ucell_t NeoPixel_numPixels(ucell_t object)
{
	return reinterpret_cast<Adafruit_NeoPixel*>(object)->numPixels();
}

//uint32_t NeoPixel_getPixelColor(void* object, uint16_t n)
ucell_t NeoPixel_getPixelColor(ucell_t object, ucell_t n)
{
	return reinterpret_cast<Adafruit_NeoPixel*>(object)->getPixelColor(n);
}

//uint8_t NeoPixel_sine8(uint8_t x)
ucell_t NeoPixel_sine8(ucell_t x)
{
	return Adafruit_NeoPixel::sine8(x);
}

//uint8_t NeoPixel_gamma8(uint8_t x)
ucell_t NeoPixel_gamma8(ucell_t x)
{
	return Adafruit_NeoPixel::gamma8(x);

}

//uint32_t NeoPixel_Color(uint8_t r, uint8_t g, uint8_t b)
ucell_t NeoPixel_Color(ucell_t r, ucell_t g, ucell_t b)
{
	return Adafruit_NeoPixel::Color(r, g, b);
}

//uint32_t NeoPixel_ColorW(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
ucell_t NeoPixel_ColorW(ucell_t r, ucell_t g, ucell_t b, ucell_t w)
{
	return Adafruit_NeoPixel::Color(r, g, b, w);
}

//uint32_t NeoPixel_ColorHSV(uint16_t hue, uint8_t sat, uint8_t val)
ucell_t NeoPixel_ColorHSV(ucell_t hue, ucell_t sat, ucell_t val)
{
	return Adafruit_NeoPixel::ColorHSV(hue, sat, val);
}

//uint32_t NeoPixel_gamma32(uint32_t x)
ucell_t NeoPixel_gamma32(ucell_t x)
{
	return Adafruit_NeoPixel::gamma32(x);
}

//void NeoPixel_rainbow(void* object, uint16_t first_hue, int8_t reps,
//             uint8_t saturation, uint8_t brightness,
//             bool gammify)
void NeoPixel_rainbow(ucell_t object, ucell_t first_hue, cell_t reps,
		ucell_t saturation, ucell_t brightness,
		ucell_t gammify)
{
	reinterpret_cast<Adafruit_NeoPixel*>(object)->rainbow(first_hue, reps, saturation, brightness, gammify);
}

