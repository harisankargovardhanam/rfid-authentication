#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#define SS_PIN 10
#define RST_PIN 5
#define KEY_RETURN 0xB0
SoftwareSerial espSerial(5, 6);
 
MFRC522 mfrc522 ( SS_PIN, RST_PIN ) ;
char Enter = KEY_RETURN;                //Return key is declared as Enter.
String readid;
String user1="rfidtag1"; 
String manager = "rfidtag2";
String win_pass = "windowspassword";
void generateJson(String usertype, String tag, String t){ //function to generate and append json document of userinfo through the serial monitor for the esp8266 to fetch.

  StaticJsonDocument<96> doc;

  doc["usertype"] = usertype;
  doc["tag"] = tag;
  doc["time"] = t;

  serializeJson(doc, espSerial);
} 
void setup( ) 
{
 Serial.begin(9600);
 Keyboard.begin();
 SPI.begin();
 mfrc522.PCD_Init();
 espSerial.begin(9600);
 delay(2000);
}

void temp(byte *buffer, byte bufferSize)//function to store card uid as a string datatype.
{
  readid="";
  for(byte i = 0;i<bufferSize; i++)
  {
    readid=readid+String(buffer[i], HEX);
  }
}
void authentication(){ //function to authenticate the windows lockscreen through keyboard
  Keyboard.press(KEY_LEFT_GUI);              //Press the left windows key.
  Keyboard.press('l');                       //Press the "l" key.
  Keyboard.releaseAll();                     //Release all keys.
  delay (100);
  Keyboard.press(Enter);                     //Press the Enter key.
  Keyboard.release(Enter);                   //Release the Enter key.
  delay(100);
  Keyboard.print(win_pass);                    // Change this value to your Windows PIN/Password.
  Keyboard.releaseAll();
  delay(100);
  Keyboard.press(Enter);
  Keyboard.releaseAll();
  
}
void loop( ) 
{
 if(!mfrc522.PICC_IsNewCardPresent()){return;}
 if(!mfrc522.PICC_ReadCardSerial()){return;} 
 temp(mfrc522.uid.uidByte, mfrc522.uid.size);
 if(readid==user1)
 { 
  authentication();
  generateJson("EMPLOYEE", user1, "time");
  Serial.println("Send to esp!");
 }
 else if (readid == manager){
  authentication();
  generateJson("MANAGER", manager,"time");
 }
 else
 {
  generateJson("INVALID USER", readid, "time");
 } 
}
