#include <Keypad.h>
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[rows] = { 7,6,5,4 };  //connect to the row pinouts of the keypad
byte colPins[cols] = { 3,2,10,11 };    //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
//--------------------//
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
//---------------------//
#include <Servo.h>
Servo servo;

const int buzzer = 8;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(4, 0);
  lcd.print("LOCKED!");
  lcd.setCursor(1, 1);
  lcd.print("ENTER PASSWORD");
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
servo.attach(9);
pinMode(buzzer, OUTPUT);
  
  
}

int count = 0;
int i = 0;
String password = "124";
int len = password.length() ;
String input;

void loop() {
  while (i < len) {
    char code = 0;
    
      code = keypad.getKey();
    
    if(Serial.available() > 0){
       code = Serial.read();
    }
   
    if (code) {
      input += code;
      i++;
      if (i == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PASSWORD:");
      }
      lcd.setCursor(i + 4, 1);
      lcd.print("*");
      delay(10);
    }
 }
  if (input.length() == len) {
      Serial.print("PasswordEntered:");
      Serial.println(input);
    if (password == input) {
      Serial.println("Correct");
      digitalWrite(3, HIGH);

      Serial.println("Now your house is unlocked");
      lcd.clear();
      lcd.setCursor(1, 0);
      tone(2, 180, 100);
      lcd.print("ACCESS GRANTED");
      digitalWrite(13, HIGH);
       delay(2000);
       digitalWrite(13, LOW);
        lcd.clear();
       lcd.setCursor(2, 0);
       lcd.print("you have 10s");
       lcd.setCursor(4, 1);
       lcd.print("to enter");

       
      for(int i=0; i<=65;i++){
            servo.write(i);
            delay(10);
      }
      delay(10000);

      for(int i=65; i>=0;i--){
            servo.write(i);
            delay(7);
      }
  
      digitalWrite(3, LOW);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("LOCKED!");
      lcd.setCursor(1, 1);
      lcd.print("ENTER PASSWORD");
    } 
    else {
      Serial.println("Someone tried to break the lock of your house");
      delay(1000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("INVALID");
      lcd.setCursor(4, 1);
      lcd.print("PASSWORD");
    
      
      
      digitalWrite(4, HIGH);
      digitalWrite(12, HIGH);
      tone(buzzer, 1000);
      delay(2000);
       noTone(buzzer);
      digitalWrite(4, LOW);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("ENTER");
      lcd.setCursor(0, 1);
      lcd.print("CORRECT PASSWORD");
    }
    input = "";
   i=0;
  }
}