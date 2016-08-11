#include <Regexp.h>
#include <SoftwareSerial.h>
/*
 * created by A.Poluden
 * artiomnkkm@gmail.com
 */

/* 
 * Cmd enum hold all availble commands
 * All commands is integers
 * SMS command example: SMS text(n m) where n is command m is pin number
 * 
 * UP - specify digital pin level to high
 * DOWN - specify digital pin level to low
 * STATUS - sends via SMS arduino pin status(UP, DOWN)
 */
enum Cmd {
  DOWN, UP, STATUS
};

/*
 * Pins enum hold all available pins to control
 */
enum Pins {
  ZERO, ONE, TWO, THREE, FOUR, FIVE
};

// SMS struct
struct SMS {
   String phone_number;
   String msg;
};

// SMS command structure
struct CMD {
  byte cmd;
  byte pin;
};

// phone numbers which have permissions to control arduino PINS
String PHONE_NUMBERS[] = {"+37067309726"};

// Arduino pins which could be controlled via SMS
int PINS[] = {};

// Software serial port wich is used to connect arduino uno and SIM900 module
SoftwareSerial SIM900(7, 8);

void setup() {
  //powerUp();
  Serial.begin(57600);
  SIM900.begin(19200);
  // Turn on message receiving
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  // Init pins
  for (int i = ZERO; i <= FIVE; i++) {
      pinMode(i, OUTPUT);
  }
}

void loop() {
    String sim_output = check_sim900_output();
    if (sim_output.length() != 0) {
        if (check_if_sms(sim_output)) {
            struct SMS sms = parse_sms(sim_output);
            if (validate_phone(sms.phone_number)) {
              process_commands(sms.msg);
            }
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

// Sends commands to SIM900 module
void send_command_to_sim900(String cmd) {
    SIM900.print(cmd);
}

void process_commands(String cmd) {
  struct CMD command = cmd_parse(cmd);
  // Magic number 266
  if (command.cmd != 266) {
    switch(command.cmd) {
      case UP:
        digitalWrite(command.pin, HIGH);
        Serial.println("UP");
        // TODO verify sms about pin level change
        break;
      case DOWN:
        Serial.println("DOWN");
        digitalWrite(command.pin, LOW);
        // TODO verify sms about pin level change
        break;
      case STATUS:
        // TODO return ALL pin stats
        break;
      default:
        Serial.println("Default");
        break;
    }
  }
}

// Parse SMS text to CMD struct
CMD cmd_parse(String cmd) {
  struct CMD commands;
  // Regex part
  char charBuf[cmd.length()];
  cmd.toCharArray(charBuf, cmd.length());
  MatchState ms;
  ms.Target(charBuf);
  char result = ms.Match("(%d)(%s)(%d)");
  
  if (result == REGEXP_MATCHED) {
    byte index = cmd.indexOf(" ");
    byte pin = cmd.substring(index, cmd.length()).toInt();
    byte command = cmd.substring(0, index).toInt();
    if (cmd_valid(command) && pin_valid(pin)) {
       commands.cmd = command;
       commands.pin = pin;
       Serial.println("Cmd and pins valid");
       return commands;
    } else {
      Serial.println("Cmd and pins not valid");
    }
  } else if (result == REGEXP_NOMATCH) {
    // TODO
  }
  else {
    // TODO some sort of error
  }
}

// Validate command parameter
boolean cmd_valid(int cmd) {
  for (int i = DOWN; i <= STATUS; i++) {
    if (i == cmd) return true;
  }
  return false;
}

// Validate pin parameter
boolean pin_valid(int pin) {
  for (int i = ZERO; i <= FIVE; i++) {
    if (i == pin) return true;
  }
  return false;
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

// Check if SIM900 has bytes
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

// Check if SIM900 output is SMS message
boolean check_if_sms(String sim_output) {
  String sms_head = "+CMT";
  if (sim_output.indexOf(sms_head) > -1) {
    return true;
  } else {
    return false;
  }
}

// SMS parser
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
