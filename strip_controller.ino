#include "strip_defines.h"

void setup() {

	pinMode(MUX_SEL, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(BUTTON, INPUT);
	digitalWrite(MUX_SEL, 0); //select node mcu pin
	//digitalWrite(MUX_SEL, 1); //select mobo pin
	digitalWrite(LED_BUILTIN, 1); //0 means LED is ON

	attachInterrupt(digitalPinToInterrupt(BUTTON), butPushed, FALLING);

	#ifdef SERIAL_DEBUG
		Serial.begin(9600);
		Serial.setDebugOutput(true);
	#endif

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);	

}

void loop() {
	#ifdef SERIAL_DEBUG
		Serial.println("Entered "+ deviceStatetoString());
		//serialDebugPrints(1000);
	#endif

	//state wise code (executed without delay as long as no user input)
	//maximum delay is 100ms
	switch(device_state){
		case STATE(0):{	//STATE(0) is all OFF, low power
			clearStrip();
			waitForStateTrans();
		}	break;
		case STATE(1):{	//STATE(1) is motherboard control
			digitalWrite(MUX_SEL, 1); //select mobo pin
			waitForStateTrans();
			digitalWrite(MUX_SEL, 0); //select node mcu pin
		}	break;
		case STATE(2):{ //STATE(2) is nodemcu control
			static int pattern = 0;
			if (pattern > NUM_PATTERNS) pattern = 0;
			#ifdef SERIAL_DEBUG
				Serial.print("Pattern: "); Serial.println(pattern);
			#endif
			cycle_all_patterns(pattern++, 60);

		}	break;
		case STATE(3): { //pretty lights
		 	rainbowCycle(60);
		} break;
		case STATE(4): { //calming lights
		 cycle_all_patterns(12, 20); //slow cloud colors
		} break;
		case STATE(5): { //lava lights
		 cycle_all_patterns(21, 20);
		} break;
		case STATE(6): { //Forest colours
		 cycle_all_patterns(20, 20);
		} break;
		case STATE(7): { //flowing water
		 cycle_all_patterns(5, 60);
		} break;
		case STATE(8): { //theater chase rainbow
		 theaterChaseRainbow(75); // Rainbow-enhanced theaterChase variant
		} break;
		case STATE(9): { //random
		 cycle_all_patterns(15, 60);
		} break;
		//solid colors
		case STATE(10): {
		 colorWipe(strip.Color(255, 0, 0), 0); // Red
		} break;
		case STATE(11): {
		 colorWipe(strip.Color(0, 255, 0), 0); // Green
		} break;
		case STATE(12): {
		 colorWipe(strip.Color(0, 0, 255), 0); // Blue
		} break;
		case STATE(13): {
		 colorWipe(strip.Color(0, 255, 255), 0); // Cyan
		} break;
		case STATE(14): {
		 colorWipe(strip.Color(255, 0, 255), 0); // Magenta
		} break;
		case STATE(15): {
		 colorWipe(strip.Color(255, 255, 0), 0); // Yellow
		} break;
		case STATE(16): {
		 maxBrightnessWhite(); // MaxWhite
		} break;
		default:;
	}
	
	//monitoring user input
	monitorUserInput();	

	//blink_without_delay(LED_BUILTIN, 500);
}
