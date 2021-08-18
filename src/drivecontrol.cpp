#include <Arduino.h>

int pin1, pin2, ult, eep,but;
int motor_active = 0;
int but_state = 0;
int can_drive = 0;
int speed = 0; 
int turn_motor_off();
int drive_forward(int);

/**
 *#pin1 the first input for the motor with the pin(4) and the AttachPin(15)
 *#pin2 the secound input for the motor with the pin(0) and the AttachPin(16)
 *#the Pin for the Button (34) is now input.
 *#eep just enable in the start with the pin (17)
 *#ult  just enable in the start with the pin (16) 
 * */

int initial_motor(int pinnum1, int pinnum2, int ultnum, int eepnum, int tastenum) {
  pin1 = pinnum1;
  pin2 = pinnum2;
  ult = ultnum;
  eep = eepnum;
  but  = tastenum;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(ult, OUTPUT);
  pinMode(eep, OUTPUT);
  pinMode(but, INPUT); 
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(ult, LOW);
  digitalWrite(eep, LOW);
  ledcAttachPin(pin1,15);
  ledcAttachPin(pin2,16);
  ledcSetup(15,12000,8);
  ledcSetup(16,12000,8);
  return 0;
}

void break_vehicle(int rotation_angle) {
  int break_strength = map(abs(rotation_angle), 0, 35, 20, 100);
  drive_forward(speed - break_strength);
}



int turn_motor_off() {
  speed = 0;
  motor_active = 0;
  ledcWrite(15, LOW);
  ledcWrite(16, LOW);
  return 0;
}
/**
 * Value is between min/speed 150 and 255 max/speed
 * when the value under or more then this area, will be automatically to max spead
 * */
int drive_forward(int value) {
  motor_active = 1;
  digitalWrite(eep, HIGH);
  digitalWrite(ult, HIGH);  
/**
 * read the button, and when it is high change the button_activ from high to low or from low to high
 * then when the butt
 * */
    if  (value < 150 || value > 255) {
      value = 255;
    }
  speed = value;
    ledcWrite(15,value);
    digitalWrite(pin2, LOW);
  return 0;
}



void drive(){
  but_state = digitalRead(but); 
  if (but_state == HIGH) {
    delay(500);
    if (can_drive == 0) {
      can_drive = 1;
    } else {
      can_drive = 0;
    }
  }
  //--------

  //---------

  if (can_drive == 0) {
    if (motor_active != 0) {
      turn_motor_off();
    }
  } else if (can_drive == 1) {
    if (motor_active != 1) {
      //drive_forward(255);
      drive_forward(255);
    }
  }
  //Serial.println(motor_active);
  //delay(1000);
}

/**
 * dirve backward.. for later when someone need it 
 */
int drive_backward(int value) {
 
 if  (value < 150 || value > 255)
  {
    value = 255;
      }
  ledcWrite(16,value);
  digitalWrite(pin1, LOW);
  digitalWrite(ult, HIGH);
  digitalWrite(eep, HIGH);
  return 0;
}
