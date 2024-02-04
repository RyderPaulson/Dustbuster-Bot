void rightMotor(int motorSpeed); 
void leftMotor(int motorSpeed); 

//PIN VARIABLES

int switchPin = 11;             //switch to turn the robot on and off

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 7;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 6;            //control pin 2 on the motor driver for the right motor
const int PWMA = 5;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 4;           //speed control pin on the motor driver for the left motor
const int BIN2 = 3;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 2;           //control pin 1 on the motor driver for the left motor

//the right motor will be controlled by the motor A pins on the motor driver
const int SAIN1 = 10;           //control pin 1 on the motor driver for the spinning motor
const int SAIN2 = 9;            //control pin 2 on the motor driver for the spinning motor
const int SPWMA = 8;            //speed control pin on the motor driver for the spinning motor

//robot behaviour variables
int backupTime = 600;           //amount of time that the robot will back up when it senses an object
int turnTime = 300;             //amount that the robot will turn once it has backed up

// to link both arduinos

char val; 
 // value -> used to store incoming serial data from other board

void setup() {

  Serial.begin(9600); 

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(SAIN1, OUTPUT);
  pinMode(SAIN2, OUTPUT);
  pinMode(SPWMA, OUTPUT);

}

void loop() {
  
  if (Serial.available() > 0)
  {

    Serial.read(val);
    Serial.println(val);

  }

  if (digitalRead(11) == LOW) 
  {         // switch is flipped on

    rightMotor(200);
    leftMotor(200); 
    spinningMotor(200); 
    
    if ((val >= 100)&&(val <= 199)) 
    {   //if an object is detected
        //Serial.println("front distance: ");
        //Serial.println(distance); 
        //back up and turn
        //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

      //back up
      rightMotor(-100);
      leftMotor(-100);
      delay(backupTime);

      //turn away from obstacle
      rightMotor(100);
      leftMotor(-100);
      delay(turnTime);
    } 
    
    else if ((val >= 200)&&( val <= 299))    //if an object is detected
    {
          //Serial.println("side distance: ");
          //Serial.println(distance_2);
          //back up and turn
        
          //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

      //back up
      rightMotor(-100);
      leftMotor(-100);
      delay(backupTime);

          //turn away from obstacle
      rightMotor(-100);
      leftMotor(100);
      delay(turnTime);
    } 
    else if ((val >= 300)&&(val <= 399))   //if an object is detected
    { 
          //Serial.println("side distance: ");
          //Serial.println(distance_2);
          //back up and turn
        
          //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

          //back up
      rightMotor(-100);
      leftMotor(-100);
      delay(backupTime);

          //turn away from obstacle - THIS IS IF OBSTRUCTION IS MOST IN FRONT
      rightMotor(-200);
      leftMotor(200);
      delay(turnTime);
    }  
    delay(500); 
  }
  else // if switch is off
  {
    rightMotor(0);
    leftMotor(0);
    spinningMotor(0); 
  }  
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void spinningMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(SAIN1, HIGH);                         //set pin 1 to high
    digitalWrite(SAIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(SAIN1, LOW);                          //set pin 1 to low
    digitalWrite(SAIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(SAIN1, LOW);                          //set pin 1 to low
    digitalWrite(SAIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(SPWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
