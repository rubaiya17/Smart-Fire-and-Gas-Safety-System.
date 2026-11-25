// C++ code
//
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

int gas_sensor = 0;

int tempsensor = 0;

int unnamed = 0;

int i = 0;

LiquidCrystal_I2C lcd_1(32, 16, 2);

Servo servo_9;

void setup()
{
  lcd_1.init();
  servo_9.attach(9, 500, 2500);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  lcd_1.backlight();
  servo_9.write(0);
}

void loop()
{
  gas_sensor = analogRead(A0);
  tempsensor = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -40, 125);
  Serial.println(tempsensor);
  Serial.println(gas_sensor);
  lcd_1.setCursor(0, 1);
  lcd_1.print("T :");
  lcd_1.print(tempsensor);
  lcd_1.print("C G :");
  lcd_1.print(gas_sensor);
  lcd_1.print("       ");
  lcd_1.setCursor(0, 0);
  if (gas_sensor >= 500 && tempsensor >= 50) {
    lcd_1.print("FIRE ALERT!    ");
    digitalWrite(4, HIGH);
    tone(7, 1.9152548672166444e+21, 150); // play tone 800 (G#66 = 1.9152548672166444e+21 Hz)
    tone(7, 57079043007393, 150); // play tone 500 (G#41 = 57079043007393 Hz)
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    servo_9.write(90);
  } else {
    if (gas_sensor >= 500) {
      lcd_1.print("GAS LEAK ALERT!    ");
      digitalWrite(4, HIGH);
      tone(7, 176967447100, 150); // play tone 400 (E33 = 176967447100 Hz)
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      servo_9.write(90);
    } else {
      if (tempsensor >= 50) {
        lcd_1.print("HIGH TEMP ALERT!    ");
        digitalWrite(4, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        servo_9.write(90);
      } else {
        if (gas_sensor >= 350 || tempsensor >= 38) {
          lcd_1.print("WARNING: CHECK!    ");
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(7, LOW);
          servo_9.write(45);
        } else {
          lcd_1.print("SYSTEM SAFE       ");
          digitalWrite(4, LOW);
          digitalWrite(7, LOW);
          lcd_1.print("SYSTEM SAFE        ");
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(7, LOW);
          servo_9.write(0);
        }
      }
    }
  }
  delay(400); // Wait for 400 millisecond(s)
}