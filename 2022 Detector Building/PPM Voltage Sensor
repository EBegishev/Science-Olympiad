//The following code employs Arduino, electrical prongs, DS18B20 temperature sensor, and a fixed resistor
// to calculate temperature, voltage, and PPM. 
#include <LiquidCrystal_I2C.h> 
#include <LCD.h> 
#include <OneWire.h> 
#include <DallasTemperature.h> 

int BlueLed = 2; 
int GreenLed = 4;  
int RedLed = 3; 

int ECMain = A0; 
int Ground = A1; 
int Power = A4; 
int R1 = 1000; 
int Ra = 25;  

//Adjust day of competition 
float Range1 = 1440; 
float Range2 = 3060; 
//LCD pinout 

const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3; 

//I2C Address 
const int i2c_addr = 0x27; 

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE); //I2C Defining 
const int numRows = 2;//Modification of the usage of rows and cols 
const int numCols = 16; 

float Conv = 0.5; //Variables 
float K = 2.88; 
float TempCoef = 0.0210; //0.0212 for 25 degrees C   

#define ONE_WIRE_BUS 6           
const int TPPositive = 7;   
const int TPNegative = 5; 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 

float Temperature = 10; 
float EC = 0; 
float EC25 = 0; 
int ppmCrude = 0; 
int ppmMain = 0; 
float ECMDirect = 0; 
float Vin = 5; 
float Vdrop = 0; 
float Rc = 0; 
float buffer = 0;  

void setup() 
{ 

  Serial.begin(9600); 
  pinMode(TPNegative, OUTPUT );  
  digitalWrite(TPNegative, LOW ); 
  pinMode(TPPositive, OUTPUT ); 
  digitalWrite(TPPositive, HIGH ); 
  pinMode(ECMain, INPUT); 
  pinMode(Power, OUTPUT); 
  pinMode(Ground, OUTPUT); 
  digitalWrite(Ground, LOW); 

  delay(100); 
  sensors.begin(); 
  delay(100); 
  R1=(R1+Ra); 

  Serial.begin(9600); 
  lcd. begin(16, 2); 

  //print on first row 
  lcd.setCursor(0, 0); 
 // lcd. print ("Hello World!"); //LCD cursor test 

  delay(500);  

//  clear("Hello World"); 
  Serial.println("Developed for the 2022 Science Olympiad Detector Building Event"); 
  Serial.println("Penfield #37; Erick Begishev"); 

}; 

void loop() 

{ 

ECCalc();           
SerialPrint();   
delay(5500); 
   

} 


void ECCalc(){ 

sensors.requestTemperatures(); 
Temperature = sensors.getTempCByIndex(0); 
digitalWrite(Power, HIGH); 
ECMDirect = analogRead(ECMain); 
ECMDirect = analogRead(ECMain); 
digitalWrite(Power, LOW); 

Vdrop = (Vin * ECMDirect) / 1024.0; //EC Convertion 
Rc = (Vdrop*R1) / (Vin-Vdrop); 
Rc = Rc - Ra;  
EC = 1000 / (Rc*K); 
EC25 = EC / (1 + TempCoef * (Temperature - 25.0)); 
ppmCrude = (EC25)*(Conv * 1000); 
ppmMain = abs(ppmCrude) 

 
;} 

void SerialPrint(){ 
Serial.print("Rc: ");  
Serial.print(Rc); 
Serial.print(" EC: "); 
Serial.print(EC25); 
Serial.print(" Simens  "); 
Serial.print(ppmCrude); 
Serial.print(" ppmCrude  "); 
Serial.print(ppmMain); 
Serial.print( " ppmMain  "); 
Serial.print(Temperature); 
Serial.println(" Celsius "); 

//LCD Print 

lcd.setCursor(0, 0);  
lcd.print("Volt = "); 
lcd.print(EC25); 
lcd.setCursor(0, 1); 
lcd.print("PPM = "); 
lcd.print(ppmCrude); 
//lcd.print("C"); 
//lcd.print("/"); 
//lcd.print(F); 
//lcd.print("F"); 
//Serial.println(T);  

//Temperature Zone 

if (ppmMain < Range1) { 
  digitalWrite(BlueLed, HIGH); 
} 

else if (ppmMain < Range2) { 
 digitalWrite(GreenLed, HIGH); 
} 

else { 
  digitalWrite(RedLed, HIGH); 
  } 

delay(500); 

 

digitalWrite(BlueLed, LOW); 
digitalWrite(GreenLed, LOW); 
digitalWrite(RedLed, LOW); 

}; 
