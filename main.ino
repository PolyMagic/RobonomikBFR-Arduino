#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX, TX
String mess;
//
int esc1 = 5; 

void setup() {
  pinMode(esc1,OUTPUT);


  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop() {

  if(btSerial.available()){
    mess = btSerial.readStringUntil('\n');
  }


  if(mess.length()>0){
    
    Serial.println(mess);
    
    if(mess[0]=='P'){
      int number = mess.substring(1).toInt();
    //   Serial.println(number);

      number = map(number,0,100,0,255);
      analogWrite(esc1,number);
    }
    else if(mess[0]=='D'){
        int number = mess.substring(1).toInt();
        // Serial.println(number);
    }

    mess="";
  }


}