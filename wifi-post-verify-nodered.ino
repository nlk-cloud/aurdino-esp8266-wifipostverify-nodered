// This program posts data to logs table in wifipostdemo database of wifi-post.php file in XAMPP server

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Access credentials

const char* ssid = "neel";
const char* pwd = "neesa1468";
const char* host = "http://192.168.2.6";
String get_host = "http://192.168.2.6:1880";
WiFiServer server(80);

void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    delay(20);
    WiFi.begin(ssid,pwd);

    // starting the server
    server.begin();

    Serial.println("Connecting");

    while(WiFi.status() != WL_CONNECTED)
    {
          delay(500);
          Serial.print(".");
    }

    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
 
    
}


void loop() {
  // put your main code here, to run repeatedly:
  post_device_status();
  delay(10000);

}

void post_device_status()
{
    WiFiClient client = server.available();
    HTTPClient http;

    String data, station, postData;
    int sensedata = 1;
    data = String(sensedata);   //String to interger conversion
    station = "A";

  //Post Data
  postData = data; //"status=" + data + "&station=" + station ;
  
  //String url = get_host+"/IOT/wifi-post.php";

  String url = get_host;
  http.begin(client,url);
  
  http.addHeader("Content-Type", "text/plain" ); //application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
 
}
