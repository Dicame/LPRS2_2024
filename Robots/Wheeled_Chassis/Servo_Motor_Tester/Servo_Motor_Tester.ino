#define DEG_STEP 15
#define SPEED_STEP 10
#include <Servo.h>
 
Servo s;
int8_t deg;
void update_servo() {
	s.write(deg+45);
}
 
int8_t brzina;
  
int pinTasterLevo = 8;  
int pinTasterDesno = 9;  
int pinTasterNapred = 11;
int pinTasterNazad = 12;
int pwm_value ;
int DIR = 4;
 
void setup() {
	Serial.begin(115200);
	s.attach(A1);
	deg = 0;
	update_servo();
	brzina = 0;
 
 
 
 
 
  pinMode(pinTasterLevo, INPUT_PULLUP);  
  pinMode(pinTasterDesno, INPUT_PULLUP);
  pinMode(pinTasterNapred, INPUT_PULLUP);  
  pinMode(pinTasterNazad, INPUT_PULLUP);
  pinMode(DIR, OUTPUT);
 
}
 
void loop() {
 
  if(digitalRead(pinTasterLevo) == LOW && deg > -45) {
    deg -= DEG_STEP;
    Serial.print(deg);
    Serial.println("  skretanje");
    update_servo();
    delay(200);
  } 
  if(digitalRead(pinTasterDesno) == LOW && deg < 45) {
    deg += DEG_STEP;
    Serial.print(deg);
    Serial.println("  skretanje");
    update_servo();
    delay(200);
  }
  
  if (deg > 45) {
    brzina = 100;
  } else if (brzina < -45) {
    brzina = -45;
  }
  
  
 
  if (digitalRead(pinTasterNapred) == LOW && brzina < 100) {
    brzina += SPEED_STEP;
  } 
  else if (digitalRead(pinTasterNazad) == LOW && brzina > -100) {
    brzina -= SPEED_STEP;
  }
 
  if (brzina > 100) {
    brzina = 100;
  } else if (brzina < -100) {
    brzina = -100;
  }
 
  int pwm_value = map(brzina, -100, 100, 0, 255);
 
 
  if ( brzina > 0 && brzina <= 100) {
    pwm_value = map(brzina, 100, 0, 0, 255);
    Serial.print(brzina);
    Serial.println("  brzina");
    analogWrite(3, pwm_value); 
    digitalWrite(DIR, HIGH );
  } else if(brzina < 0 && brzina >= -100){
    pwm_value = map(brzina, -100, 0 , 255, 0);
    Serial.print(brzina);
    Serial.println("  brzina");
    analogWrite(3, -pwm_value); 
    digitalWrite(DIR , LOW );
  }else if(brzina == 0){
    Serial.print(brzina);
    Serial.println("  brzina");
    analogWrite(3, 255);
  }
 
  // Pauza za stabilizaciju
  delay(200);
 
 
}
