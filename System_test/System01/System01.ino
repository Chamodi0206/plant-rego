
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // include the library code
#include "DHT.h"// include the library code

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial mySerial(10, 11); // RX, TX


#define sensorPin A2 // select the input pin for the potentiometer

const int dry= 595; // dry value
const int wet= 239; // wet value

const int buttonPin = 2; // the number of the pushbutton pin
int buttonState = 0; // variable for reading the pushbutton status
DHT dht(7, DHT11);


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600); // set up Serial library at 9600 bps
    Serial.begin(9600); // set up Serial library at 9600 bps
    delay(1000);
    lcd.begin();
    lcd.backlight(); // turn on the backlight

    pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input
     Serial.begin(9600);
  Serial.println("DHT test!");

  dht.begin();
}


void sendMessage(int value){
    // send the value to the serial port
    mySerial.println("AT+CMGF=1\r\n"); // set SMS mode to text
    delay(1000);
    mySerial.println("AT+CMGS=\"0715603380\"\r"); // set the phone number
    delay(1000);
    String SMS = "Hellow"; 
    mySerial.print("Humidity: "); // send the message
    mySerial.print(SMS);
    mySerial.write("%");
    delay(1000);
    mySerial.println((char)26); // ASCII code of CTRL+Z
    delay(1000);
}
void RecieveMessage(){
    mySerial.println("AT+CMGR=2,2,0,0,0"); // AT command to recieve the message
    delay(1000);
}

void loop(){
   delay(2000);

  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin); // read the input pin
    int precentage = map(sensorValue, wet, dry, 0, 10); // map the value to 0-100

    // print the value to the serial monitor
    Serial.print("Humidity: ");
    Serial.print(precentage);
    Serial.println("%");
    delay(1000); 

    // print the value to the LCD
    lcd.setCursor(1,0); // set the cursor to column 1, line 0
    lcd.print("Sensor Value: ");
    lcd.setCursor(3,1); // set the cursor to column 3, line 1
    lcd.print(sensorValue);
    lcd.print(" ");
    lcd.setCursor(7,1); // set the cursor to column 7, line 1
    
    lcd.setCursor(10,1); // set the cursor to column 10, line 1
    lcd.print(precentage);
    lcd.print("%");

    buttonState = digitalRead(buttonPin); // read the state of the pushbutton value
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // send the value to the serial port
        sendMessage(precentage);
      // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(f);
  Serial.println("°F ");
  Serial.print("Heat index : ");
  Serial.print(hic);
  Serial.print("°C ");
  Serial.print(hif);
  Serial.println("°F");

}
}
