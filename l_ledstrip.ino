// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void cycle_all_patterns(int patternCurrent, int updates_per_second){
    switch (patternCurrent) {
      case 22:  { currentPalette = OceanColors_p;         	currentBlending = LINEARBLEND; break; }
      case 21:  { currentPalette = LavaColors_p;         		currentBlending = LINEARBLEND; break; }
      case 20:  { currentPalette = ForestColors_p;         	currentBlending = LINEARBLEND; break; }
      case 19:  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; break; }
      case 18:  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  	 break; }
      case 17:  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; break; }
      case 16:  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; break; }
      case 15:  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; break; }
      case 14:  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; 		 break; }
      case 13:  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; break; }
      case 12:  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; break; }
      case 11:  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; break; }
      case 10:  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  	 break; }
      case 	9:  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; break; }		
			case 8: 
		  	rainbowCycle(20);
				break;
      case 7:
        theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
        break;
      case 6:
        rainbow(20); // Flowing rainbow cycle along the whole strip
        break;     
      case 5:
        theaterChase(strip.Color(0, 0, 127), 50); // Blue
        break;
      case 4:
        theaterChase(strip.Color(127, 0, 0), 50); // Red
        break;
      case 3:
        theaterChase(strip.Color(127, 127, 127), 50); // White
        break;
      case 2:
        colorWipe(strip.Color(0, 0, 255), 50); // Blue
        break;
      case 1:
        colorWipe(strip.Color(0, 255, 0), 50); // Green
        break;        
      default: //case 0
        colorWipe(strip.Color(255, 0, 0), 50); // Red
        break;
    }

		if(patternCurrent >= FAST_LED_PATTERN_RANGE)
			updateFastLed(updates_per_second);
}

void updateFastLed(int updates_per_second){
    //static uint8_t startIndex = 0;
    //startIndex = startIndex + 1; /* motion speed */
		for(int startIndex = 0; startIndex <256; startIndex++){
			FillLEDsFromPaletteColors(startIndex);
			FastLED.show();
			if(userGivingInput()) return; FastLED.delay(1000 / updates_per_second);
		}
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    if(userGivingInput()) return; delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    if(userGivingInput()) return; delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    if(userGivingInput()) return; delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      if(userGivingInput()) return; delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      if(userGivingInput()) return; delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void clearStrip(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, (strip.Color(0, 0, 0)));
  }
  strip.show();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = BRIGHTNESS;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

//due to current limitations all LEDs can't be turned to white simultaneously
//so we turn on N LEDs in the middle of the strip
void maxBrightnessWhite(){
		int blank_range1 	= (NUM_LEDS - MAX_WHITE_LEDS)/2;
		int blank_range_2 = NUM_LEDS - blank_range1;

		for(int i = 0; i < NUM_LEDS; i++){
			if(i <= blank_range1 || i >= blank_range_2) strip.setPixelColor(i, (strip.Color(0, 0, 0)));
			else  strip.setPixelColor(i, (strip.Color(255, 255, 255)));
		}
  	strip.show();
}

int userGivingInput(){
	return button_state != OFF;	
}

// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
