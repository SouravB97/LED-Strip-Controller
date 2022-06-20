Led strip controller for my Desk.
1 meter strip of 60 LEDs/m WS2812B LEDs, RGB.
Node MCU muxed with motherboard ARGB header with a TTL MUX.
1 push button to switch mode.
Entire thing is powered from motherboard 5V pin

//												 ___
//NODE_MCU_LED_PIN (A) ---|		\
//												|		 |-- (Y) LED STRIP DIN
//MOBO ARGB PIN		 (B) ---|___/
//MUX_SEL					 (S)______|

	List of states: <br>
		STATE(0) : All OFF, low power <br>
		STATE(1) : Motherboard control <br>
		STATE(2) : Cycle all states <br>
		STATE(3) : pretty lights <br>
		STATE(4) : Slow cloud colors, calming lights <br>
		STATE(5) : Lava lights <br>
		STATE(6) : Forest colours <br>
		STATE(7) : Flowing water <br>
		STATE(8) : Theater chase rainbow <br>
		STATE(9) : Random pattern <br>
		STATE(10): Red <br>
		STATE(11): Green <br>
		STATE(12): Blue <br>
		STATE(13): Cyan <br>
		STATE(14): Magenta <br>
		STATE(15): Yellow <br>
		STATE(16): Half Strip White <br>
