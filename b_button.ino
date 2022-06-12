#define LONG_PRESS_THRESHOLD 3000 //ms
#define DEBOUNCE_TIME 20 //ms

volatile unsigned long tPushed;

ICACHE_RAM_ATTR void butPushed() {
  static unsigned long lastPushed;
  unsigned long pushed = micros();
  if (pushed - lastPushed > DEBOUNCE_TIME * 1000) {
    if (!digitalRead(BUTTON)) {
      lastPushed = pushed;

			tPushed = millis();
			//toggle state
			button_state = ON;
			incrDeviceState();

      attachInterrupt(digitalPinToInterrupt(BUTTON), butReleased, RISING);
    }
  }
}
ICACHE_RAM_ATTR void butReleased() {
  static unsigned long lastPushed;
  unsigned long pushed = micros();
  if (pushed - lastPushed > DEBOUNCE_TIME * 100) { //no need to debounce this
    if (digitalRead(BUTTON)) {
      lastPushed = pushed;

			//toggle state
			button_state = OFF;

      attachInterrupt(digitalPinToInterrupt(BUTTON), butPushed, FALLING);
    }
  }
}

void checkForLongPress(){
	if(button_state == ON)
		if(millis() - tPushed >= LONG_PRESS_THRESHOLD){
			button_state = LONG_PRESS;
			resetDeviceState(); //device OFF
		}
}

String buttonStatetoString(){
	String s = "BUTTON_STATE = ";
	return s + (button_state == ON ? "ON" : button_state == OFF ? "OFF" : "LONG_PRESS");
}

