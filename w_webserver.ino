#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

// Replace with your network credentials
const char* ssid = "moushumib_2.4";
const char* password = "SONALI1SOURAV2";

const int output = 2;

String sliderValue = "0";

const char* PARAM_INPUT = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  return String();
}

void web_server_setup(){
  // Serial port for debugging purposes
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
		#ifdef SERIAL_DEBUG
    Serial.println("Connecting to WiFi..");
		#endif
  }

  // Print ESP Local IP Address
	#ifdef SERIAL_DEBUG
  Serial.println(WiFi.localIP());
	#endif

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      //analogWrite(output, sliderValue.toInt());
			update_ledstrip_brightness(sliderValue.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
		#ifdef SERIAL_DEBUG
    Serial.println(inputMessage);
		#endif
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
