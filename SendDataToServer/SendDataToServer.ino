#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
WiFiClient client;
const char* ssid = "Namaste_Nepal";
const char* password = "bibeksah";
 
const char* serverName = "http://myfirstiotrku.000webhostapp.com//post-data.php";
 
String apiKeyValue = "12345";
 
String sensorName = "Distance sensor";
String sensorLocation = "office";
int trigPin=5;
int echoPin=4;
long duration, cm, inches; 
 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to the Wifi Network");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi is Connected at this IP Address : ");
  Serial.println(WiFi.localIP());
 
 
}
 
void loop() {
  
  //Check WiFi connection status
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1; // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74; // Divide by 74 or multiply by 0.0135
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    http.begin(client,serverName);
    
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.println(cm);
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&SensorData=" + sensorName
                          + "&LocationData=" + sensorLocation + "&value1=" + cm
                          + "&value2=" +inches + "&value3=" + "NULL" + "";
     //String httpRequestData ="api_key=#54321&SensorData=distance sensor&LocationData=Aicpecf-office&value1=NULL&value2=NULL&value3=NULL";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
 
    int httpResponseCode = http.POST(httpRequestData);
     
 
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code1: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
 
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000);  
}
