void monitorUserInput(){
	checkForLongPress();	 //button
	#ifdef SERIAL_DEBUG
  updateBrightnessFromSerial(); //serial
	#endif

	//wifi
}
