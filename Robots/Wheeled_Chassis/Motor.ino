#include <N64Controller.h>
#include <N64Interface.h>

#define DEG_STEP 15
#define SPEED_STEP 10
#include <Servo.h>
 
Servo s;
int8_t deg;
void update_servo() {
        
  	s.write(deg+45);
}
 
int8_t brzina;
 
int pwm_value ;
int DIR = 4 ;
int pinKontroler = 11;

N64Controller controller(pinKontroler);
 
void setup() {
	Serial.begin(115200);
	s.attach(A1);
	deg = 0;
	update_servo();
	brzina = 0;
 
        
 
 
 
  pinMode(DIR , OUTPUT);
 
}
 
void loop() {

 
  if(controller.D_left()) {
    deg -= DEG_STEP;
    Serial.print(deg);
    Serial.println("  skretanje");
    update_servo();
    delay(200);
  } 
  if(controller.D_right()) {
    deg += DEG_STEP;
    Serial.print(deg);
    Serial.println("  skretanje");
    update_servo();
    delay(200);
  }
  
  if (deg > 45) {
    deg = 45;
  } else if (deg < -45) {
    deg = -45;
  }
  
 
 if (controller.D_up()) {
    brzina += SPEED_STEP;
  } 
  else if (controller.D_down()) {
    brzina -= SPEED_STEP;
  }
 
  if (brzina > 100) {
    brzina = 100;
  } else if (brzina < -100) {
    brzina = -100;
  }
 
 
  if ( brzina > 0 && brzina <= 100) {
    pwm_value = map(brzina, 100, 0, 0, 255);
    Serial.print(brzina);
    Serial.println("Idem  napred");
    digitalWrite(DIR, HIGH );
    analogWrite(3, pwm_value); 
  } else if(brzina < 0 && brzina >= -100){
    pwm_value = map(brzina, -100, 0 , 255, 0);
    Serial.print(brzina);
    Serial.println("  Idem nazad");
    digitalWrite(DIR , LOW );
    analogWrite(3, -pwm_value);     
  }else if(brzina == 0){
    Serial.print(brzina);
    Serial.println("  brzina");
    analogWrite(3, 255);
  }
 
 
   controller.update();
  // Pauza za stabilizaciju
  delay(200);
}
