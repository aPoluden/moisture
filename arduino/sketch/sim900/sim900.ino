#include <SoftwareSerial.h>

// Serial
String REQUEST = "";
// SIM900 to Arduino
String RESPONSE = "";

struct SMS {
   char  sender_number[12];
   char  ts[20];
   char  msg[160];
};

boolean stringComplete = false;
String MY_NUMBER = "+37067309726;";

SoftwareSerial SIM900(7, 8);

// Program setup
void setup() {
  //powerUp();
  Serial.begin(57600);
  SIM900.begin(19200);
  REQUEST.reserve(200); // ??
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
}

// Main program
void loop() {
   while (SIM900.available()) {
      char msg_byte = SIM900.read();
      RESPONSE += msg_byte;
   }
   delay(1000);
   if (RESPONSE.length() != 0) {      
//    Process RESPONSE FROM SIM900
      parseSim900Response();
      RESPONSE = "";
   }
// print the string when a newline arrives:
  if (stringComplete) {
    // SEND msg to SIM900
    SIM900.println(REQUEST);
    SIM900.flush();
    // clear the string:
    REQUEST = "";
    Serial.flush();
    stringComplete = false;
  }
}

void parseSim900Response() {
  String sms_head = "+CMT";
  char buf [256];
  int phone_index_start = 9;
  int phone_index_finish = 21;
  int sms_index_start = 48;
  String phone = "";
  String sms = "";

  if (RESPONSE.indexOf(sms_head) > -1) {
    phone = RESPONSE.substring(phone_index_start, phone_index_finish);
    sms = RESPONSE.substring(sms_index_start);
    Serial.println(phone);
    Serial.println(sms);
  } else {
    // TODO send SIM900 output to dedicated number
    Serial.println("Not SMS");
  }
}

// SEND SMS NOT TESTED
void sendSMS(String msg) {
  SIM900.println("AT + CMGS = \"+12128675309\"");                                     // recipient's mobile number, in international format
  delay(100);
  SIM900.println("Hello, world. This is a text message from an Arduino Uno.");        // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
}

// Software reset for GPRS shield NOT WORKING
void powerUp() {
  pinMode(6, OUTPUT);
  digitalWrite(6,LOW);
  delay(1000);
  digitalWrite(6,HIGH);
  delay(2000);
  digitalWrite(6,LOW);
  delay(3000);
}

// Handle Serial RX from PC
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char) Serial.read();
    if (inChar == '\r') {
      stringComplete = true;
    } else {
      REQUEST += inChar;
    }
  }
}

// ATD + MY_NUMBER call command
// AT+CMGF - SMS format
// AT+CMGS="867309726" MSG_BODY + CTRL+Z - to send msg
// AT+CMGD=1,4 - delete all messages

// Text msg format
