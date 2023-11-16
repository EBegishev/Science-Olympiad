//Program developed for 2023 Season, with the goal of being used to accurately measure weight. 
//Weight calculation came with a ~5-15% weight error due to Force Sensitive Resistor's (FSR) Material Properties

//A program was also created for a Strain Gauge load cell
//However, due to problems in manufacturing (CNC) and deadlines, smaller theoretical weight error was never achieved 

int fsrPIN = A1; // the FSR and 10K pulldown are connected to a1
int fsrReading; // the analog reading from the FSR resistor divider
int fsrVoltage; // the analog reading converted to voltage
unsigned long fsrResistance; // The voltage converted to resistance, can be very big so make "long"
float Mass;
float Mass2;

//Adjust day of competition
float Range1 = 200;
float Range2 = 300;
float Offset = 0; 

int GreenLed = 4;
int BlueLed = 2;
int RedLed = 3;

void setup(void) {
Serial.begin(9600); 
}

void loop(void) {

if (Mass < Range1) {
  digitalWrite(GreenLed, HIGH);
}
else if (Mass < Range2) {
  digitalWrite(BlueLed, HIGH);
}
else {
  digitalWrite(RedLed, HIGH);
}

fsrReading = analogRead(fsrPIN);
Serial.print("Analog = ");
Serial.println(fsrReading);

fsrVoltage = map(fsrReading, 0, 1023, 0, 5000); //voltage mapping
Serial.print("Voltage(mV) = ");
Serial.println(fsrVoltage);

if (fsrVoltage == 0) {
Serial.println("No Weight Present");
} else {
fsrResistance = 5000 - fsrVoltage; //converting to mv
fsrResistance *= 10000; // 10K ohm resistor
fsrResistance /= fsrVoltage;
Serial.print("FSR resistance in ohms = ");
Serial.println(fsrResistance);
}

Mass = (2*pow(10,6))*pow(fsrResistance,-0.91) + Offset; 
Serial.print("Mass (Res)(valid) : ");
Serial.println(Mass,1);

Mass2 = (2*pow(10,-8)*pow(fsrVoltage,3)) - (5*pow(10,-5)*pow(fsrVoltage,-2)) + (0.1982*fsrVoltage) - 30.594 + Offset;
Serial.print("Mass (Volt)(possibly invalid) : ");
Serial.println(Mass2,1);

Serial.println("....................");
delay(5000);

digitalWrite(BlueLed, LOW);
digitalWrite(GreenLed, LOW);
digitalWrite(RedLed, LOW);

}
