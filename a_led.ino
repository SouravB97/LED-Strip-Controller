unsigned long led_currenttime, led_lasttime = 0;
int led_state = HIGH;

void blinkLED(int led, int blinkDelay){
  digitalWrite(led,HIGH);
  delay(blinkDelay);
  digitalWrite(led,LOW);
  delay(blinkDelay);
}

void blink_without_delay(int led, int blinkDelay){
    led_currenttime = millis();
    //Serial.print("Current time: ");
    //Serial.println(led_currenttime);
    if(led_currenttime - led_lasttime >= blinkDelay){
      //Serial.print("Last time: ");
      //Serial.println(led_lasttime);
      led_lasttime = led_currenttime;
      led_state = !led_state;
      digitalWrite(led, led_state);
    }
}

