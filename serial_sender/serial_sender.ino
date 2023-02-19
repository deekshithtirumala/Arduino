#define data1 4

void setup(){
  pinMode(data1,OUTPUT);
  Serial.begin(9600);
  digitalWrite(data1, HIGH);
}

void loop(){
  delay(2000);
  digitalWrite(data1, LOW); // send the negetive pulse.
  delay(50);
  //changing the high for 2ms and low for 1ms
  //chaning duration here
  digitalWrite(data1,HIGH);
  delay(2);
  digitalWrite(data1,LOW);
  delay(2);
  digitalWrite(data1,HIGH);
  delay(30);
  //changing the high for 2ms and low for 1ms
  //chaning duration here
  
  digitalWrite(data1,LOW);
  delay(2);
  digitalWrite(data1,HIGH);
  delay(2);
  digitalWrite(data1,LOW);
  delay(10);
  //output - 1
  digitalWrite(data1,HIGH);
}
