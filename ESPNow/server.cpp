// Setup the server to receive data over WiFi
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuration parameters for Access Point
char * ssid_ap = "CLARO_2GFAC73F";
char * password_ap = "38FAC73F";
IPAddress ip(192,168,0,4); // arbitrary IP address (doesn't conflict w/ local network)
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

// Set up the server object
ESP8266WebServer server;

// Keep track of the sensor data that's going to be sent by the client
float sensor_value = 0.0;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(ssid_ap,password_ap);
  // Print IP Address as a sanity check
  Serial.begin(115200);
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  // Configure the server's routes
  server.on("/",handleIndex); // use the top root path to report the last sensor value
  server.on("/update",handleUpdate); // use this route to update the sensor value
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleIndex() {
  server.send(200,"text/plain",String(sensor_value)); // we'll need to refresh the page for getting the latest value
}

void handleUpdate() {
  // The value will be passed as a URL argument
  sensor_value = server.arg("value").toFloat();
  Serial.println(sensor_value);
  server.send(200,"text/plain","Updated");
}
