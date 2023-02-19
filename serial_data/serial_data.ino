//#define data 9
//
//void setup(){
//  pinMode(data,INPUT);
//  Serial.begin(9600);                                          
//}
//void loop(){
//  Serial.println(digitalRead(data));
//  delay(100);
//}


#define data1 2

void setup(){
  pinMode(data1, INPUT);
  Serial.begin(9600);
}

int count = 0;
String s = "";
void loop(){
  unsigned long duration = pulseIn(data1, LOW);
  //Serial.println(duration);
  if(duration>49500 && duration<50000){
    count+=1;
    // high for 10ms and low for 30ms-0
    //high for 20ms and low for 20ms-1
    // high for 30ms and low for 10ms -2
    
    unsigned long high_dur = pulseIn(data1, HIGH);
    unsigned long low_dur = pulseIn(data1, LOW);
    //Serial.println(high_dur);
    //Serial.println(low_dur);
    if(high_dur<10000 && low_dur>29000){
      s+="1000";
    }
    else if(high_dur<=20000 && low_dur>19000){
      s+="1100";
    }
    else if(high_dur<=30000 && low_dur>9000){
      s+="1110";
    }
    if (s!=""){
      Serial.println(s);
      s="";
    }
  }

  
}
/*
//esp32
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
*/
