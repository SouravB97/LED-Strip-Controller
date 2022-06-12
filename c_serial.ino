#ifdef SERIAL_DEBUG

unsigned long serial_currenttime, seril_lasttime = 0;

void	serialDebugPrints(int print_delay){
	String s = "Current State: ";
	s += deviceStatetoString();


    serial_currenttime = millis();
    if(serial_currenttime - seril_lasttime >= print_delay){
      seril_lasttime = serial_currenttime;

			Serial.println(s);
    }

}



#endif
