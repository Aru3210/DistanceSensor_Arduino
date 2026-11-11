#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCDディスプレイの定義
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//超音波距離センサの定義
const int trigPin = 2;
const int echoPin = 3;

unsigned long duration = 0;
float distance = 0;


void setup()
{
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
 lcd.backlight();

 lcd.setCursor(0,0);
 lcd.print("DIstance Sensor");
}
void loop()
{
  //信号の初期化
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(10);

  //超音波を発射
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if(duration > 0)
  {
    distance = duration * 0.0343 / 2.0;

    lcd.setCursor(0,1);
    lcd.print("Distance");

    lcd.print(distance, 1);
    lcd.print(" cm   ");

    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.print(" cm");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("No Echo     ");

    Serial.println("No echo");
  }

  delay(300);

}