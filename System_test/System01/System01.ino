
const int buttonPin = 2; //button pin 
const int button = 0; // button status
#define sensorPin A0 // select the input pin 

const int dry= 595; // dry value
const int wet= 239;

void setup(){
 
  pinMode(buttonPin, INPUT);// Set buttonPin - pin 2 as an output
  // pinMode(buttonPin, INPUT_PULLUP); and can use the inbuilt resistor

  Serial.begin(9600); //Open the serial monitor in chanel 9600

}

void loop(){
 
  int button = digitalRead(buttonPin); // get the button read
  if(button == 0){
    int sensorValue = analogRead(sensorPin);
    int precentage = map(sensorValue, dry, wet, 0, 100);
    Serial.println(precentage);
    delay(1000);
    }
  
  
}
