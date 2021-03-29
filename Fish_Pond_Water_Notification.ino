#include <LiquidCrystal.h>

const int RS=8, EN=9, D4=4, D5=5, D6=6, D7=7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int trig = 10;
const int echo = 11;
const int led = 2;
const int relay = 3;
const int button1 = 12;
const int button2 = 13;
long duration;
int buttonstate1, buttonstate2, distance;

void setup() {
  // put your setup code here, to run once:
pinMode(trig, OUTPUT);
pinMode(led, OUTPUT);
pinMode(relay, OUTPUT);
pinMode(button1, INPUT);
pinMode(button2, INPUT);
pinMode(echo, INPUT);
Serial.begin(9600);
lcd.begin(16,2);
lcd.setCursor(2,0);
lcd.print("Welcome Back");
lcd.setCursor(5,1);
lcd.print("Master");
delay(3000);
lcd.clear();
digitalWrite(relay, HIGH);
delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
buttonstate1 = digitalRead(button1);
buttonstate2 = digitalRead(button2);

digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH); 
delayMicroseconds(10);
digitalWrite(trig, LOW);

duration = pulseIn(echo, HIGH);
distance = duration*(0.034/2);

Serial.print("Distance: ");
Serial.println(distance);

if (buttonstate1 == HIGH && buttonstate2 == LOW){
  digitalWrite(relay, LOW);   //the relay is on because the relay is active LOW
  digitalWrite(led, HIGH);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Filling the");
  lcd.setCursor(0,1);
  lcd.print("pond water");
  delay(2000);
}
else if (buttonstate1 == LOW && buttonstate2 == HIGH){
  digitalWrite(relay, HIGH);  //the relay is off
  digitalWrite(led, LOW);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water filling");
  lcd.setCursor(0,1);
  lcd.print("stops");
  delay(2000);
}
if (distance <= 20){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water in the");
  lcd.setCursor(0,1);
  lcd.print("pond is enough");
  delay(200);
}
else if (distance >= 60){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water in the");
  lcd.setCursor(0,1);
  lcd.print("pond is not enough");
  delay(200);
}
}
