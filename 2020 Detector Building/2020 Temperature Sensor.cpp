//The following code uses an Arduino system consisting of a thermistor to calculate the temperature of a sample of water
// and display the data on screen and in LED grouping
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <LCD.h>

//Adjust day of competition
float Range1 = 24.7;
float Range2 = 26;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, F;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//Define LCD pinout
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

//Define I2C Address - change if required
const int i2c_addr = 0x27;


//Temperature Zones
int GreenLed = 8;
int YellowLed = 9;
int RedLed = 10;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

const int numRows = 2;//Modification of the usage of rows and cols could be modified using these two functions 
const int numCols = 16;

void setup() {
  Serial.begin(9600);
  //Set Display type as 16 char, 2 rows
  lcd. begin(16, 2);

  //print on first row
  lcd.setCursor(0, 0);
 // lcd. print ("Hello World!"); //<- use to test lcd set cursor function 
  delay(500); 
//  clear("Hello World");
}

void loop() {
  //sensing
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 271.5; //used to be T = T - 273.15
  //LiquidCrystal_I2C lcd(12, 11, 5, 4, 3, 2);
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 271.5;//used to be T = T - 273.15
  //Farenheight Conversion
  F = T * 1.8 + 32;

  //Temperature Zone
  if (T < Range1) {
    digitalWrite(GreenLed, HIGH);
  }
  else if (T < Range2) {
    digitalWrite(YellowLed, HIGH);
  }
  else {
    digitalWrite(RedLed, HIGH);
  }

  //LCD Print
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.setCursor(0, 1);
  lcd.print(T);
  lcd.print("C");
  lcd.print("/");
  lcd.print(F);
  lcd.print("F");
  Serial.println(T);
  delay(500);

  digitalWrite(GreenLed, LOW);
  digitalWrite(YellowLed, LOW);
  digitalWrite(RedLed, LOW);

}
