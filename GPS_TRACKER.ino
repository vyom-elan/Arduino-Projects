#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900A(7, 8);
char incoming_char = 0;
String gMap = "http://www.google.com/maps/place/";
double Latitude, Longitude, Altitude, speed;
boolean GPSstatus = false;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps; // The TinyGPS++ object

void setup() {
  SIM900Apower();
  SIM900A.begin(9600); 
  Serial.begin(9600); 
  delay(100);
}

void SIM900Apower()
{
  pinMode(9, OUTPUT); 
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(2000);
  digitalWrite(9,LOW);
  delay(3000);
}


void loop() {

  while (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      getGPSdata();
  if (SIM900A.available() > 0) {
    incoming_char = SIM900A.read()
    if (incoming_char == 'R') {
      delay(10);
      Serial.print(incoming_char);
      incoming_char = SIM900A.read();
      if (incoming_char == 'I') {
        delay(10);
        Serial.print(incoming_char);
        incoming_char = SIM900A.read();
        if (incoming_char == 'N') {
          delay(10);
          Serial.print(incoming_char);
          incoming_char = SIM900A.read();
          if (incoming_char == 'G') {
            delay(10);
            Serial.print(incoming_char);
            delay(1000);
            SIM900A.println("ATH"); // decline the call
            if (Latitude + Longitude == 0) {
              No_GPS_Message();
            }
            else {
              Valid_GPS_Message();
            }
          }
        }
      }
    }
  }
}
void Valid_GPS_Message()
{
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  
  SIM900A.println("AT+CMGS=\"+918707810007\"\r");
  delay(1000);
  SIM900A.print(gMap); 
  delay(100);
  SIM900A.print(Latitude, 6);
  delay(100);
  SIM900A.print(",");
  delay(100);
  SIM900A.println(Longitude, 6);
  delay(100);
  SIM900A.println((char)26);//undo
  delay(1000);
}

void No_GPS_Message()
{
  SIM900A.println("AT+CMGF=1");    // Text Mode
  delay(1000); 
  SIM900A.println("AT+CMGS=\"+91 PH NO\"\r");
  delay(1000);
 // 
  SIM900.println("AT+CMGS=\"+91 PH nO"\r");
  //delay(1000);
  SIM900A.println("GPS DATA NOT AVAILABLE");
  delay(100);
  SIM900A.println("PLEASE TRY AGAIN LATER");
  delay(100);
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void getGPSdata() {
  if (gps.location.isValid()) {
    Latitude = gps.location.lat(), 6; // Latitude in degrees 
    Longitude = gps.location.lng(), 6; // Longitude in degrees 
    GPSstatus =  true;
  }
  else
    GPSstatus =  false;

  if (gps.altitude.isValid()) {
    Altitude = gps.altitude.meters(); // Altitude in meter
  }
  else
    GPSstatus =  false;

  delay(1000);
}
