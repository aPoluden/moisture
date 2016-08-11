#include <SoftwareSerial.h>
// SMS structure

enum Cmd {
  STOP,
  START
};

struct SMS {
   String phone_number;
   String msg;
};

String PHONE_NUMBERS[] = {"+37067309726"};
SoftwareSerial SIM900(7, 8);


void setup() {
  //powerUp();
  Serial.begin(57600);
  SIM900.begin(19200);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");

  pinMode(2, OUTPUT);
}

// Main loop
void loop() {
    String sim_output = check_sim900_output();
    if (sim_output.length() != 0) {
        if (check_if_sms(sim_output)) {
            struct SMS sms = parse_sms(sim_output);
            // TODO
            if (validate_phone(sms.phone_number)) {
              process_commands(sms.msg.toInt());
            }
            // Check SMS content
            // Clear message memory
        } else {
          // Some serious info from sim900
          // TODO send data to my number
        }
    }
    String serial_input = check_serial();
    if (serial_input != "") {
      send_command_to_sim900(serial_input);
    }
}

// Sends commands to sim900 module
void send_command_to_sim900(String cmd) {
    SIM900.print(cmd);
}
// 
void process_commands(int cmd) {
  switch(cmd) {
    case START:
      digitalWrite(2, HIGH);
      break;
    case STOP:
      digitalWrite(2, LOW);
      break;
    default:
      Serial.println("Default");
      break;
  }
}

// Validate senders phone number
boolean validate_phone(String phone) {
  for (int i = 0; i <= sizeof(PHONE_NUMBERS); i++) {
    if (phone.equals(PHONE_NUMBERS[i])) {
        return true;
    }
  }
  return false;
}

// Check if serial available
String check_serial() {
  String serial_request = "";
  // Check if available bytes on serial
  while (Serial.available())  {
    // get byte from serial:
    char inChar = Serial.read();
    if (inChar == '\n') {
      return serial_request;
    } else {
      serial_request += inChar;
    }
  }
  return serial_request;
}

// Check if SIM900 has something
String check_sim900_output() {
   String sim_output = "";
   while (SIM900.available()) {
      sim_output += (char)SIM900.read();
   }
   if (sim_output != "") {
      Serial.print(sim_output);    
   }
   return sim_output;
}

// Check if sim900 is SMS message
boolean check_if_sms(String sim_output) {
  String sms_head = "+CMT";
  if (sim_output.indexOf(sms_head) > -1) {
    return true;
  } else {
    return false;
  }
}

// Parses Sim900 SMS
SMS parse_sms(String sms) {
    String phone = "";
    String msg = "";
    
    int phone_index_start = 9;
    int phone_index_finish = 21;
    int sms_index_start = 48;
    
    phone = sms.substring(phone_index_start, phone_index_finish);
    msg = sms.substring(sms_index_start);

    // Define and create struct obj
    struct SMS smsstrct;
    smsstrct.phone_number = phone;
    smsstrct.msg = msg;
    
    // Serial.println(phone);
    // Serial.println(msg);

    return smsstrct;
    
}

// TODO test
void sendSMS(String msg, String number) {
  SIM900.println("AT + CMGS = \"+12128675309\"");
  delay(100);
  SIM900.println("Hello, world. This is a text message from an Arduino Uno.");
  delay(100);
  SIM900.println((char)26);// End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);// give module time to send SMS
}

// Event handler on Serial(RX)
//void serialEvent() {
//  String serial_request = "";
//  // Check if available bytes on serial
//  while (Serial.available())  {
//    // get byte from serial:
//    char inChar = (char) Serial.read();
//    if (inChar == '\r') {
//      // Send command to SIM900 module
//      send_command_to_sim900(serial_request);
//    } else {
//      serial_request += inChar;
//      // RESPONSE += inChar;
//    }
//  }
//}

// ATD + MY_NUMBER call command
// AT+CMGF - SMS format
// AT+CMGS="867309726" MSG_BODY + CTRL+Z - to send msg
// AT+CMGD=1,4 - delete all messages

// Tasks
