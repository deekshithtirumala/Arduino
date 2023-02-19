#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define fire_pin A2
#define water_motor A3
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 //max -190  // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

//commands pins
#define forward_pin A5
#define backward_pin A4
#define right_pin 2
#define left_pin 13
bool automatic = false;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);  
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward=false;
boolean goesBackward = false;
int distance = 100;
int speedSet = 0;
int serialData = 0;
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 
  
void moveForward() {
  if(!goesForward){
    goesForward=true;
    goesBackward=false;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);  
    for(speedSet = 0;speedSet<=MAX_SPEED;speedSet+=2){//to avoid battery draining
      motor1.setSpeed(MAX_SPEED);
      motor2.setSpeed(MAX_SPEED);
      motor3.setSpeed(MAX_SPEED);
      motor4.setSpeed(MAX_SPEED);
    }
  }
  else{
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD); 
  }
}

void moveBackward() {
  if(!goesBackward){
    goesForward=false;
    goesBackward = true;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
    for(speedSet = 0;speedSet<=MAX_SPEED;speedSet+=2){//to avoid battery draining
      motor1.setSpeed(MAX_SPEED);
      motor2.setSpeed(MAX_SPEED);
      motor3.setSpeed(MAX_SPEED);
      motor4.setSpeed(MAX_SPEED);
    }
  }
  else{
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD); 
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
void setup() {
  Serial.begin(9600);
  Serial.println("started");
  pinMode(forward_pin, INPUT);
  pinMode(water_motor, OUTPUT);
  pinMode(backward_pin, INPUT);
  pinMode(right_pin, INPUT);
  pinMode(left_pin, INPUT);
  pinMode(fire_pin, INPUT);
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void auton() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
  //check fire no fire continous else loop here
  int fire = digitalRead(fire_pin);
  if (fire==0){
    moveStop();
  }
  while(fire==0){
    lookRight();
    delay(200);
    lookLeft();
    delay(200);
    Serial.println("watering objects");
    digitalWrite(water_motor,HIGH);
    fire = digitalRead(fire_pin);
  }
  digitalWrite(water_motor,LOW);
 if(distance<=30){
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
  
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    if(distanceR>=distanceL){
    
      turnRight();
      moveStop();
    }else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward();
  }
  distance = readPing();
}
int recieve_data(){
  delayMicroseconds(156); //reades the first input
  int serialData[3] = {0,0,0};
  for(int i=0; i<3;i++){
    serialData[i]= digitalRead(rx_pin);
    delayMicroseconds(104);
  }
  if(digitalRead(rx_pin)==0){
    return (4*serialData[0])+(2*serialData[1])+(1*serialData[2]);
  }
  else{
    return -1;
  }
}
void loop(){
  //if A4 is low then automatic is false.
  Serial.println(digitalRead(manual_pin));
  int f = digitalRead(forward_pin); //logic is inversed
  int b = digitalRead(backward_pin); //;logic is inversed
  int r = digitalRead(right_pin);
  int l = digitalRead(left_pin);
  if(f==0 && b==0 && r==1 && l==1){
    //automatic as all directions are high
    auton();
  }
  else if(f==0){
    moveForward();
  }
  else if(b==0){
    moveBackward();
  }
  else if(r==1){
    turnRight();
  }
  else if(l==1){
    turnLeft();
  }
}
