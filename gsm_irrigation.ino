#include <SoftwareSerial.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT11 
#define DHTPIN 4

SoftwareSerial gsmSerial(9, 10);

LiquidCrystal_I2C lcd(0x3F, 16, 2);
bool aaa = false;

const int waterPumpPin = 7;
DHT dht(DHTPIN,DHT11);
int output_value;
String data;
int sensor_pin = A2;


void setup() {
  pinMode(waterPumpPin, OUTPUT);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  Serial.println("Initiallizion done");
  dht.begin();
  lcd.init();
  lcd.backlight();
 

  pinMode(sensor_pin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("SOLAR POWERED");
  lcd.setCursor(0, 1);
  lcd.print("IRRIGATION SYSTEM ");
  delay(2000);
  sendSMS("SOLAR POWERED SMART IRRIGATION SYSTEM IS INITIALIZING.");
  pinMode(waterPumpPin, OUTPUT);




}

void loop() {

  float temperature = dht.readTemperature();
  float humidity =dht.readHumidity();
  float tempF = dht.readTemperature(true);
  
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(tempF);


  lcd.init();
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print((int)temperature);
  lcd.print((char)223);
  lcd.print("C,");
  lcd.print((int)tempF);
  lcd.print((char)223);
  lcd.print("F");
  
  lcd.setCursor(0,1); 
  lcd.print("Humidity: ");
  lcd.print((int)humidity);
  lcd.print("%");
  delay(2000);

  lcd.init();
  lcd.setCursor(0,0); 
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,10,0,100);
  lcd.print("Mositure: ");
  lcd.print(output_value);
  lcd.print("%");
  delay(1000);
  Serial.println(output_value);

  data = "\nTemperature:" + String(temperature ) + "C or" + String(tempF)+ "F\n"
  + "Humidity:" + String(humidity) + "%\n" 
  + "Soil Moisture :" + String(output_value) + "%\n";

  lcd.setCursor(0,1);
  if(aaa==false){
  
     if(output_value<20){
      lcd.print("Motor ON");
      sendSMS("Water pump turned ON AUTOMATICALLY with the following data in the field:" + String(data));
      startWaterPump();
      
      
      aaa=!aaa;
     
    }
  }
  else if(aaa==true){
     if(output_value>20){
      lcd.print("Motor OFF");
      sendSMS("Water pump turned OFF AUTOMATICALLY with the following data in the field:" + String(data));
      stopWaterPump();
     
      aaa=!aaa;
     
     }
  }
  delay(2500);
  lcd.noAutoscroll();
  lcd.clear();

  

}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000);
  gsmSerial.println("AT+CMGS=\"MOBILE NUMBER\""); 
  delay(1000);
  gsmSerial.println(message);
  delay(1000);
  gsmSerial.println((char)26); 
  delay(1000);

}

void startWaterPump(){
  digitalWrite(waterPumpPin, LOW);
  

}
void stopWaterPump(){
  digitalWrite(waterPumpPin, HIGH);

}
