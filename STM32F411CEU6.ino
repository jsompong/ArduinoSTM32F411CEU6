/* Device type : MCU , Device CPU  : Cortex-M4
Size: 26.99 KB , Address : 0x08000000
Device ID   : 0x431 , Revision ID : Rev A
Device name : STM32F411xC/E , Flash size  : 512 KBytes
BL Version  : 0xD0   */

#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor
// System clock selection is performed on startup, 
// however the internal RC 8 MHz oscillator is selected as default CPU clock on reset. 
// PA13 SWDIO, PA14 SWCLK, PC14/PC15 OSC,
// USART on pins PA14/PA15 or PA9/PA10.
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, PA8, PA7, PA12, PA11);
int delayConSt = 5;         // number of delay taken
int stepCount = 0;         // number of steps the motor has taken

static uint8_t Digit5th = 0; // Defines the 5th digit weight
static uint8_t Digit4th = 0; // Defines the 4th digit weight
static uint8_t Digit3rd = 0; // Defines the 3rd digit weight
static uint8_t Digit2nd = 0; // Defines the 2nd digit weight
static uint8_t tempC = 0; // Defines the last digit weight

void setup() {
Serial.begin(2400);      // initialize the serial port:
Serial2.begin(2400); 
pinMode(PA0, OUTPUT);     pinMode(PA1, OUTPUT);  
// pinMode(PA2, OUTPUT);     pinMode(PA3, OUTPUT);
pinMode(PA4, OUTPUT);     pinMode(PA5, OUTPUT);
pinMode(PB0, OUTPUT);     pinMode(PB1, OUTPUT);   pinMode(PB2, OUTPUT);
pinMode(PB3, OUTPUT);     pinMode(PB4, OUTPUT);   pinMode(PB5, OUTPUT);
//B6  อาจเป็น   Tx1,    PA2 = Tx2, PA3 = Rx2,
//pinMode(PC0, OUTPUT);     pinMode(PC1, OUTPUT);   pinMode(PC2, OUTPUT);     
//pinMode(PC3, OUTPUT);     pinMode(PC4, OUTPUT);   pinMode(PC5, OUTPUT);

pinMode(PC13, OUTPUT);
Serial.println("..........................");
Serial.print("Baud Rate 2400 : ");
Serial.println("STM32F411CEU6 with Arduino");
Serial.println("24 October 2024");
Serial.println("STM32F411CEU6.inO");
Serial.println("..........................");

digitalWrite(PC13, HIGH);  delay(delayConSt);  digitalWrite(PC13, LOW);   delay(delayConSt);  
}

void loop() {
  static uint32_t state = 0;
  // ST-LINK SN  : 48FF6A064885525510260287
  // ST-LINK FW  : V2J45S7
  // Device ID   : 0x431  , Revision ID : Rev A
  // OPTION BYTES DATA ... Bank  : 0x00  ,  Address : 0x40023c14  , Size : 8 Bytes
  //digitalWrite(PC0, state ^= 1 );       delay(delayConSt);
  //digitalWrite(PC1, !digitalRead(PC1));  delay(delayConSt);
  //digitalWrite(PC2, !digitalRead(PC2));  delay(delayConSt);
  //digitalWrite(PC3, !digitalRead(PC3));  delay(delayConSt);
  //digitalWrite(PC4, !digitalRead(PC4));  delay(delayConSt);
  //digitalWrite(PC5, !digitalRead(PC5));  delay(delayConSt);
  digitalWrite(PC13, !digitalRead(PC13));  delay(delayConSt);

  digitalWrite(PB0, !digitalRead(PB0));  delay(delayConSt);
  digitalWrite(PB1, !digitalRead(PB1));  delay(delayConSt);
  digitalWrite(PB2, !digitalRead(PB2));  delay(delayConSt);
  digitalWrite(PB3, !digitalRead(PB3));  delay(delayConSt);
  digitalWrite(PB4, !digitalRead(PB4));  delay(delayConSt);
  digitalWrite(PB5, !digitalRead(PB5));  delay(delayConSt);

  digitalWrite(PA0, !digitalRead(PA0));  delay(delayConSt);
  digitalWrite(PA1, !digitalRead(PA1));  delay(delayConSt);
  // digitalWrite(PA2, !digitalRead(PA2));  delay(delayConSt);
  // digitalWrite(PA3, !digitalRead(PA3));  delay(delayConSt);
  digitalWrite(PA4, !digitalRead(PA4));  delay(delayConSt);
  digitalWrite(PA5, !digitalRead(PA5));  delay(delayConSt);

  myStepper.step(1);        // step one step:
  Serial.print("steps:");  Serial.println(stepCount);
  Serial2.print("steps:");  Serial2.println(stepCount);
  stepCount++;  delay(delayConSt);

 for (int i=0; i<30; i++) {
 Serial.print(Digit5th, DEC);
 Serial.print(Digit4th, DEC);
 Serial.print(Digit3rd, DEC);
 Serial.print(Digit2nd, DEC);
 Serial.println(tempC, DEC);
 Serial2.print(Digit5th, DEC);
 Serial2.print(Digit4th, DEC);
 Serial2.print(Digit3rd, DEC);
 Serial2.print(Digit2nd, DEC);
 Serial2.println(tempC, DEC);

 ++tempC; // increment last digit weight by one and returns the new value of x
if (tempC > 9) {  tempC = 0;  ++Digit2nd;   }            //last digit statement(s)
if (Digit2nd > 9) {  Digit2nd = 0;  ++Digit3rd;   }      //2nd digitstatement(s)
if (Digit3rd > 9) {  Digit3rd = 0;  ++Digit4th;   }      //3rd digitstatement(s)
if (Digit4th > 9) {  Digit4th = 0;  ++Digit5th;   }      //4th digitstatement(s)
if (Digit5th > 6) {  Digit5th = 0;   }                  //5th digits max = 60 tonne
 }
}
