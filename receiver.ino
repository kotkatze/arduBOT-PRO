/*
      Emitter NRF24L01 and PS2 controller

      Components:
        - Arduino Uno;
        - NRF24L01;

      Pinout:
      RF      UNO
      CE      9
      CSN     10
      SCK     13
      MISO    12
      MOSI    11




*/

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Servo Servo1;

RF24 radio(9, 10); // CE, CSN

uint64_t address[6] = {0x7878787878LL,
                       0xB3B4B5B6F1LL,
                       0xB3B4B5B6CDLL,
                       0xB3B4B5B6A3LL,
                       0xB3B4B5B60FLL,
                       0xB3B4B5B605LL
                      };

struct joystick {
  byte potLX;
  byte potLY;
  byte potRX;
  byte potRY;
  byte buttons1;
  byte buttons2;
};

joystick joystickData;

//int button0 = 0;
//int button1 = 0;
//int button2 = 0;
int servo1pos = 0; 

void setup() {
  // Inicia Serial
  Serial.begin(57600);
  Serial.println("Starting");

  Servo1.attach(3);

  // Configura e inicializa RF
  if (!radio.begin()) {
    Serial.println(F("Radio not responding!!"));
    while (1) {} // preso em loop
  }

  radio.setPALevel(RF24_PA_LOW);

  for (uint8_t i = 0; i < 6; ++i)
    radio.openReadingPipe(i, address[i]);

  radio.startListening();

  //zeraVariaveis();
}

void loop() {
  // Check if RF received data.
  if (radio.available()) {
    radio.read(&joystickData, sizeof(joystick));

  }


  // Print received data on Serial
  Serial.print("Pot LX: ");
  Serial.print(joystickData.potLX);
  Serial.print("; Pot LY: ");
  Serial.print(joystickData.potLY);
  Serial.print("; Pot RX: ");
  Serial.print(joystickData.potRX);
  Serial.print("; Pot RY: ");
  Serial.print(joystickData.potRY);

  Serial.print("; Button 1: ");
  Serial.print(joystickData.buttons1);
  Serial.print("; Button 2: ");
  Serial.println(joystickData.buttons2);
    
  delay(50);
}
