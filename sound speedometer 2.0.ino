// include external libraries needed for
// working with temp sensor and LCD display
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
SimpleDHT11 dht11;
LiquidCrystal_I2C lcd(0x27,20,4);

// define constants for easy reference 
// to arduino pin numbers
#define trigPin 2
#define echoPin 3
#define pinDHT11 4

// define variables
long  duration;          
long soundSpeed;
long  distanceInCm = 29;
int   uptime = 0;        
byte  temperature = 0; 
byte  humidity = 0;
byte  data[40] = {0};

// the setup code below will run once 
// when device is turned on
void setup() {
  // initialize input/output pins
  // for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize serial port output
  Serial.begin (9600);

  // initialize LCD display
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SPEED   : ");
  lcd.setCursor(0, 1);
  lcd.print("TEMP    : ");
  lcd.setCursor(0,2);
  lcd.print("HUMIDITY: ");
  lcd.setCursor(0,3);
  lcd.print("UPTIME  : ");
}

// the main code below will run 
// in the loop forever
void loop() {
  
  // make ultrasonic sensor send signal, 
  // wait for response, and measure time
  // to get a response (in microseconds)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 35000) * 10;

  // calculate speed of sound in m/s
  soundSpeed = 200000 * distanceInCm / duration;
  
  // obtain measurements from 
  // temperature/humidity sensor DTH11
  dht11.read(pinDHT11, &temperature, &humidity, data);
  
  // output info to serial port
  Serial.println("");
  Serial.print("Uptime in sec:\t" + String(uptime));
  Serial.print("\tSpeed in m/s:\t" + String((int)soundSpeed));
  Serial.print("\tTemp in *C\t" + String(temperature));
  Serial.print("\tHumidity in %:\t" + String(humidity));

  // print message to LCD screen 
  lcd.setCursor(10, 0);
  lcd.print(String(int(soundSpeed)) + " m/s  ");
  lcd.setCursor(10, 1);
  lcd.print(String(temperature) + " *C   ");
  lcd.setCursor(10, 2);
  lcd.print(String(humidity) + " %   ");
  lcd.setCursor(10, 3);
  lcd.print(String(uptime) + " sec ");

  // wait before looping to next measurement cycle
  delay(1000);
  uptime = uptime + 1;
}
