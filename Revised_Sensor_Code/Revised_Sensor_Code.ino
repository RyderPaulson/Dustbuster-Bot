
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

float distance_1 = 0; 
float distance_2 = 0;
float distance_3 = 0;
//stores the distance measured by the distance sensor

// for dust sensor 
int measurePin = A5;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

int switchControl;
int delayint=1000;
int serialVal;

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
  /*
  if(digitalRead(switchPin)==HIGH){
    switchControl=0;
    //Serial.println(switchControl);
  }
  else if(digitalRead(switchPin)==LOW){
    switchControl=1;
    //Serial.println(switchControl);
  }
  else{
    Serial.println("Switch Error");
  }
  */
  switchControl=0;
  //While loop which stops working if the switch is flicked
  while(switchControl<1){
  //if the user has entered something in the serial monitor
  //Serial.println("switch on"); 

  distance_1 = getDistance1();
  distance_2 = getDistance2(); 
  distance_3 = getDistance3();  
  Serial.print("\nDistance 1: ");
  Serial.print(distance_1);
  Serial.print("\nDistance 2: ");
  Serial.print(distance_2);
  Serial.print("\nDistance 3: ");
  Serial.print(distance_3);

  if (distance_1 < 10)
  {
    if (distance_1 < distance_2 && distance_1 < distance_3) 
    { // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    
    Serial.println("\nDistance 1 Smallest");

    //make the RGB LED red
    analogWrite(redPin, 255);
    serialVal = 1;
    Serial.println(serialVal);
    Serial.write(serialVal, 4); 
    delay(500); 
    }
  }
  else if (distance_2 < 10)
  {
    if (distance_2 < distance_3 && distance_2 < distance_1) 
    { // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    Serial.println("\nDistance 2 Smallest");

    //make the RGB LED red
    analogWrite(redPin, 255);
    serialVal = 2;
    Serial.println(serialVal);
    Serial.write(serialVal, 4); 
    delay(500); 
    }
  }
  else if (distance_3 < 10)
  {
    if (distance_3 < distance_2 && distance_3 < distance_1) 
    { // if sensor 1 is closer to obstruction than sensor 3 but not sensor 2 
    Serial.println("\nDistance 3 Smallest");

    //make the RGB LED red
    analogWrite(redPin, 255);
    serialVal = 3;
    Serial.println(serialVal);
    Serial.write(serialVal,4); 
    delay(500); 
    }
  }
  else {  // if robot is not near any obstruction
    analogWrite(redPin, 0);
    serialVal = 0;
    Serial.println(serialVal);
    Serial.write(serialVal,4);  
    delay(500); 
  }

  // for dust sensor 
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

//  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if (dustDensity < 0){
    dustDensity = 0.00;
  }

  Serial.print("\nRaw Signal Value (0-1023):");
  Serial.print(voMeasured);


  Serial.print("\nVoltage:");
  Serial.print(calcVoltage);


  Serial.print("\nDust Density:");
  Serial.print(dustDensity);
  Serial.print("\n\n\n");
  }
  delay(1000);      //delay ____ms between each reading
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