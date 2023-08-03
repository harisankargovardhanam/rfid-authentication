#include <ArduinoJson.h>          // https://github.com/bblanchon/ArduinoJson
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <string>
#include <NTPClient.h> //get the time from the ntp server
#include <WiFiUdp.h>

#define _SSID "wifi_username_here"        // Your WiFi SSID
#define _PASSWORD "wifi_pass_here"    // Your WiFi Password
#define PROJECT_ID "your_firebase_project_id_here"   // Your Firebase Project ID. Can be found in project settings.
StaticJsonDocument<96> doc; //use arduinojson website to compute the corresponding value according to your json file, here <96>
Firebase firebase(PROJECT_ID);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int i;
int resetId(){
  firebase.setInt("lastuser", 0); //a function to reset the user count
  }
void setup() {
// Open serial communications and wait for port to open:
  Serial.begin(9600);
  firebase.json(true);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
timeClient.begin();
timeClient.setTimeOffset(19800);
}
void loop() {// run over and over
  //interacting with the ntp server to get the current time for the logging information
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);
  String formattedTime = timeClient.getFormattedTime();

if (Serial.available() > 0)
  {
    delay(10);
    String s = Serial.readStringUntil('#'); //reading the string from serial monitor

    while(Serial.available() > 0) {Serial.read();}
    
    DeserializationError error = deserializeJson(doc, s);
    if (error) 
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    //Serial.println(error.c_str());

    //Adding the user info into the json file
    String usertype = doc["usertype"];
    String tag = doc["tag"];
    String Time = doc["time"];
    Serial.println(usertype);
    Serial.println(tag);
    Serial.println(Time);
    i = firebase.getInt("/lastuser"); //keep track of the user count
    String no = String(i+1);
    Serial.println("id --> "+no);
    firebase.setString("/Users/user_"+no+"/usertype", usertype);
    firebase.setString("/Users/user_"+no+"/tag", tag);
    firebase.setString("/Users/user_"+no+"/time", formattedTime+"\n"+currentDate);
    firebase.setInt("/lastuser", i+1);
    Serial.println("Data pushed!");
  }}
