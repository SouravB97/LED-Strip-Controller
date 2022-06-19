#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define LED_PIN 			D6
#define MUX_SEL 	 		D7
#define BUTTON 		 		D2
#define NUM_LEDS    	60
#define BRIGHTNESS  	0xFF
#define LED_TYPE    	WS2812B
#define COLOR_ORDER 	GRB

#define NUM_PATTERNS	22
#define FAST_LED_PATTERN_RANGE 9
#define MAX_WHITE_LEDS 30
//#define SERIAL_DEBUG

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//												 ___
//NODE_MCU_LED_PIN (A) ---|		\
//												|		 |-- (Y) LED STRIP DIN
//MOBO ARGB PIN		 (B) ---|___/
//MUX_SEL					 (S)______|


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


//enum device_state_e {
//	STATE0, //OFF
//	STATE1, //MOBO control
//	STATE2, //8 programmed modes
//	STATE3, //rainbow chaser (its pretty, so it gets its own mode)
//	STATE4  //cloud colours  (its calming, so it gets its own mode)
//};
#define STATE(N) (N)
#define LAST_STATE STATE(16)
typedef uint8_t device_state_e ;

enum button_state_e {ON, OFF, LONG_PRESS};

button_state_e button_state = OFF;
device_state_e device_state = STATE(6); //initial state

CRGBPalette16 currentPalette  = PartyColors_p;
TBlendType    currentBlending = LINEARBLEND;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
CRGB leds[NUM_LEDS];
