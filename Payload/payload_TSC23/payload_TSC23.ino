/*
ANDØYA SPACE EDUCATION - Nyttelast til Custom 35mm rakett
Dette programmet er rammeverket for en enkel nyttelast basert på Arudino Nano 33 BLE sense. 
Nyttelasten måler temperatur, luftfuktighet, trykk, akselerasjon, rotasjon og magnetfelt. 
Data skrives på et SD kort.

Utstyr:
- Arduino Nano 33 BLE Sense
  https://store.arduino.cc/collections/boards/products/arduino-nano-33-ble-sense
- SparkFun OpenLog
  https://www.sparkfun.com/products/13712
- SD kort
- LiPo batteri 3,7V, 240mAh, 6,7mm x 13mm x 35mm
- På/av knapp
- Ledninger  
*/

// - BIBLIOTEKER, VARIABLER OG KONSTANTER -
// Sjekk at bibliotekene er innstallert i ArduinoIDE!
#include <Arduino_HS300x.h>                                     //Sensor for tempperatur og luftfuktighet
#include <Arduino_LPS22HB.h>                                    //Sensor for trykk 
#include <Arduino_BMI270_BMM150.h>                              //Sensor for akselerasjon, rotasjon og magnetfelt

float temp, hum, pres, ax, ay, az, rx, ry, rz, bx, by, bz;      //Definerer variablene som skal brukes
unsigned long int t;                                            //Teller tid i ant. millisekund

// - SYSTEMOPPSETT -
void setup() {
Serial1.begin(9600);                                             //Starter seiell kommunikasjon

if(!HS300x.begin()) {                                           //Sjekker at sensor for tempperatur og luftfuktighet fungerer 
  Serial1.println("Failed to initialize HS3003");
  while(1);
  }
if(!BARO.begin()) {                                             //Sjekker at sensor for trykk fungerer
  Serial1.println("Failed to initialize BARO");
  while(1);
  }

if(!IMU.begin()) {                                              //Sjekker at sensor for akselerasjon, rotasjon og magnetfelt fungerer
  Serial1.println("Failed to initialize IMU!");
  while(1);
  }

Serial1.print("Time");                                           //Skriver overskrifter til datafilen på SD kortet
Serial1.print(";");
Serial1.print("Temperature");
Serial1.print(";");
Serial1.print("Humidity");
Serial1.print(";");
Serial1.print("Pressure");
Serial1.print(";");
Serial1.print("Accel_x");
Serial1.print(";");
Serial1.print("Accel_y");
Serial1.print(";");
Serial1.print("Accel_z");
Serial1.print(";");
Serial1.print("Rot_x");
Serial1.print(";");
Serial1.print("Rot_y");
Serial1.print(";");
Serial1.print("Rot_z");
Serial1.print(";");
Serial1.print("Mag_x");
Serial1.print(";");
Serial1.print("Mag_y");
Serial1.print(";");
Serial1.print("Mag_z");
Serial1.println();
}

// - MÅLING AV DATA -
void loop() {temp = HS300x.readTemperature();                   //Leser temperaturen (°C)
hum = HS300x.readHumidity();                                    //Leser luftfuktigheten (%H2O)
pres = BARO.readPressure();                                     //Leser trykket (hPa)
if(IMU.accelerationAvailable()) {                               
  IMU.readAcceleration(ax, ay, az);                             //Leser akselerasjonen (g)
  }
if(IMU.gyroscopeAvailable()) {
  IMU.readGyroscope(rx, ry, rz);                                //Leser rotasjonen (dps)
  }
if(IMU.magneticFieldAvailable()) {
  IMU.readMagneticField(bx, by, bz);                            //Leser magnetfeltet (μT)
  }
t = millis();

Serial1.print(t);                                                //Skriver data til SD kortet
Serial1.print(";");
Serial1.print(temp);
Serial1.print(";");
Serial1.print(hum);
Serial1.print(";");
Serial1.print(pres);
Serial1.print(";");
Serial1.print(ax);
Serial1.print(";");
Serial1.print(ay);
Serial1.print(";");
Serial1.print(az);
Serial1.print(";");
Serial1.print(rx);
Serial1.print(";");
Serial1.print(ry);
Serial1.print(";");
Serial1.print(rz);
Serial1.print(";");
Serial1.print(bx);
Serial1.print(";");
Serial1.print(by);
Serial1.print(";");
Serial1.print(bz);
Serial1.println();
//delay();                                                      //ekstra tid (ms) mellom hver loop
}
