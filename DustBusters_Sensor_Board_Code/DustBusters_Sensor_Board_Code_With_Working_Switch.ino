float getDistance1(); // front most
float getDistance2(); // right most 
float getDistance3(); // left most

// for distance sensors 
const int trig1Pin = 3;           //connects to the trigger pin on the first (front) distance sensor
const int echo1Pin = 2;           //connects to the echo pin on the first (front) distance sensor

const int trig2Pin = 5; //connects to the trigger pin on the second (right) distance sensor
const int echo2Pin = 4; //connects to the echo pin on the second (right) distance sensor

const int trig3Pin = 7; //connects to the trigger pin on the third (left) distance sensor
const int echo3Pin = 6; //connects to the echo pin on the third (left) distance sensor

const int redPin = 8; //pin to control the red LED inside the RGB LED

int switchPin = 10; //switch to turn the sensors on and off

float distance_1, distance_2, distance_3; //distance definitions

// for dust sensor 
int measurePin = A5;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

//Int to control the switch
int switchControl=0;
void setup() {
  // for switch 
  pinMode(switchPin, INPUT_PULLUP); //set this as a pullup to sense whether the switch is flipped

  Serial.begin (9600); //set up a serial connection with the computer

  // for distance sensors
  pinMode(trig1Pin, OUTPUT); //the trigger pin will output pulses of electricity
  pinMode(echo1Pin, INPUT); //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(trig2Pin, OUTPUT); //the trigger pin will output pulses of electricity
  pinMode(echo2Pin, INPUT); //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(trig3Pin, OUTPUT); //the trigger pin will output pulses of electricity
  pinMode(echo3Pin, INPUT); //the echo pin will measure the duration of pulses coming back from the distance sensor

  // for dust sensor 
  pinMode(ledPower,OUTPUT);

}







void loop() {
  //While loop for switch control
  if (digitalRead(switchPin)==HIGH) switchControl=1;
  if (digitalRead(switchPin)==LOW) switchControl=0;
  while(switchControl<1){
  //Calculate and store distance using functions
  distance_1 = getDistance1();
  distance_2 = getDistance2(); 
  distance_3 = getDistance3(); 

//Check if the switch is flicked on or off.   
  if(digitalRead(switchPin)==LOW) Serial.println("Switch reading low.");
  if(digitalRead(switchPin)==HIGH){
    Serial.print("Switch reading high. z = ");
    Serial.print(switchControl);
    Serial.print("\n");
  }

  //Will break the loop if the switch is flicked. 
  
     
  //Print out all of the distances for debugging. 
  Serial.println("distance 1: "); 
  Serial.println(distance_1, 3); 

  Serial.println("distance 2: "); 
  Serial.println(distance_2, 3); 

  Serial.println("distance 3: "); 
  Serial.println(distance_3, 3); 


  //Logic for movement
  if (distance_1 < 10){
    if (distance_1 < distance_2 && distance_1 < distance_3){ // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    
    Serial.println("smallest distance 1");

    //make the RGB LED red
    analogWrite(redPin, 255);
    Serial.write(100); 
    delay(500); 
    }
  }
  else if (distance_2 < 10){
    if (distance_2 < distance_3 && distance_2 < distance_1){ // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    Serial.println("smallest distance 2");

    //make the RGB LED red
    analogWrite(redPin, 255);
    Serial.write(200); 
    delay(500); 
    }
  }
  else if (distance_3 < 10){
    if (distance_3 < distance_2 && distance_3 < distance_1){ // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    Serial.println("smallest distance 3");

    //make the RGB LED red
    analogWrite(redPin, 255);
    Serial.write(300); 
    delay(500); 
    }
  }
  else{  // if robot is not near any obstruction
    analogWrite(redPin, 0);
    Serial.write(400); 
    delay(500); 
  }

  //Dust sensor
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

//  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if (dustDensity < 0) dustDensity = 0.00;

  Serial.println("Raw Signal Value (0-1023):");
  Serial.println(voMeasured);

  /*
  Serial.println("Voltage:");
  Serial.println(calcVoltage);
  */

  Serial.println("Dust Density:");
  Serial.println(dustDensity);
  Serial.print("\n\n\n\n\n");
  }
  Serial.println(switchControl);
  delay(1000);      //delay 300ms between each reading
}










/*
------------------------------------------------------------
//------------------FUNCTIONS-------------------------------
------------------------------------------------------------
*/









// for distance sensors 

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR 1
float getDistance1()
{
  float echoTime1; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance1; //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trig1Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1Pin, LOW);

  echoTime1 = pulseIn(echo1Pin, HIGH);  //use the pulsein command to see how long it takes for the
                                     //pulse to bounce back to the sensor

  calculatedDistance1 = echoTime1 / 148.0; //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance1; //send back the distance that was calculated
}

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR 2
float getDistance2()
{
  float echoTime2; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance2; //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trig2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2Pin, LOW);

  echoTime2 = pulseIn(echo2Pin, HIGH);  //use the pulsein command to see how long it takes for the
                                       //pulse to bounce back to the sensor

  calculatedDistance2 = echoTime2 / 148.0; //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance2; //send back the distance that was calculated
}

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR 3
float getDistance3()
{
  float echo3Time; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance3; //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trig3Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3Pin, LOW);

  echo3Time = pulseIn(echo3Pin, HIGH);  //use the pulsein command to see how long it takes for the
                                       //pulse to bounce back to the sensor

  calculatedDistance3 = echo3Time / 148.0; //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance3; //send back the distance that was calculated
}