#include <ESP8266WiFi.h>

//initializate network parameters
float volts = 0.0, temperatureC = 0.0;

//initializate network parameters
const char* ssid = "CLARO_2GFAC73F";
const char* password = "38FAC73F";
const char* host = 192.168.0.4;

//set up the client objet
WiFiClient client;

//configure deep sleep in between measurements
const int sleepTimeSeconds = 2;

void setup(){
	//configure the sensor pin
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	WiFi.begin(ssid,password);
	Serial.begin(115200);
	while(WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.println();
	Serial.print("IP Address (AP): ", Serial.println(WiFi.localIP());
	//get a measurement from the sensor
	volts = analogRead(A1)*3.3/1024; //10-Bit ADC on a 3.3vdc board
	temperatureC = (volts - 0.5) * 100; // Conversion from voltage to temperature follows the TMP36 datasheet
  Serial.print("Temperature C: "); Serial.println(temperatureC);
  // Connect to the server and send the data as a URL parameter
  if(client.connect(host,80)) {
    String url = "/update?value=";
    url += String(temperatureC);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +  "\r\n" +
                 "Connection: keep-alive\r\n\r\n"); // minimum set of required URL headers
    delay(10);
    // Read all the lines of the response and print them to Serial
    Serial.println("Response: ");
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(sleepTimeSeconds * 1e6);
}

void loop() {
  // put your main code here, to run repeatedly:

}


