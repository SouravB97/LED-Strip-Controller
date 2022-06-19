
device_state_e current_state = device_state;
device_state_e next_state = current_state + 1;

String deviceStatetoString(){

	char buffer[16];
  sprintf(buffer, "STATE%0d", device_state);
	return String(buffer);
}

void waitForStateTrans(){
	if(button_state == OFF){ //wait for user to push the button
			delay(20);
		#ifdef SERIAL_DEBUG
			Serial.println(buttonStatetoString());
			delay(1000);
		#endif
		while(button_state == OFF)
			delay(20); //avoid WDT reset
	}
}

void incrDeviceState(){
	current_state = next_state;
	next_state = current_state == LAST_STATE ? STATE(0) : current_state+1;
	updateState();
}

void resetDeviceState(){
	//next_state = current_state - 1; //retain exact state since pushing the button for sleep actually increments a state
	next_state = current_state; //retain state
	bext_state = STATE(1); //roll over state machine
	current_state = STATE(0);
	updateState();
}

inline void updateState(){
	device_state = current_state;
}
