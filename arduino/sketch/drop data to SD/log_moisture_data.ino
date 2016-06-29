#include <SD.h>
#include <SPI.h>

int chip = 4;
int moistureSensorPinAn = 0;
int moistureSensorPinDi = 7;
long previousMillis = 0;

bool cardInserted = false;

File myFile;
Sd2Card card;

class Pump {
  public:
     bool busy = false;
} pump;

int getMoistureValueAn(int analogPin) {
  return analogRead(analogPin);
}

double getMoistureValueDi(int digitalPin) {
  return digitalRead(digitalPin);
} 

void writeData(String data) {
  if (myFile) {
    myFile.println(data);
  } else {
    Serial.println("error opening test.txt");
  }
}

void closeFile() {
  myFile.close();
  Serial.println("File closed");
}
/////////// Setup ////////////
void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  
  if (card.init(SPI_HALF_SPEED, chip)) {
     pinMode(10, OUTPUT);
     digitalWrite(10,HIGH);
     
     if (!SD.begin(chip)) {
        Serial.println("initialization failed!");
        return;
     }
     cardInserted = true;
     Serial.println("initialization done.");
     if (!SD.exists("data.txt")) {
       myFile = SD.open("data.txt", FILE_WRITE);
     } else {
       SD.remove("data.txt");
       myFile = SD.open("data.txt", FILE_WRITE);
     }
  }
}

////////// Loop ///////////
void loop() {
  unsigned long currentMillis = millis();
  int digit = getMoistureValueAn(moistureSensorPinAn);

  if (digit == 0 && cardInserted) {
    cardInserted = false;
    closeFile();
  }
  
  if (currentMillis - previousMillis >= 60000) {
     Serial.println("Minute");
     previousMillis = currentMillis;
     if (cardInserted) {
        String str = String(digit);
        str.concat(",");
        writeData(str);
     }
   }
}
