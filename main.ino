#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX, TX
String mess;
//
int lewagora = 5; 
int lewydol = 6;
int prawagora = 9;
int prawydol = 10;

void setup() {

  pinMode(lewagora,OUTPUT);
  pinMode(lewydol , OUTPUT);
   pinMode(prawagora, OUTPUT);
 pinMode(prawydol , OUTPUT);



  Serial.begin(9600);
  btSerial.begin(9600);
}

void setPower(int l,int p){
  analogWrite(lewagora,l);
  analogWrite(lewydol,l);

  analogWrite(prawagora,p);
  analogWrite(prawydol,p);
}
// ZMIANA KODU (DODALEM FUNKCJE setPower)
void setDirection(int d){
    switch(d){
    case -1:
    setPower(0,0);
    //SRODEK
    break;
    case 0:
    setPower(0 , 255);
    //LEWA
    break;
    case 1:
    setPower(100 , 255);
    //LEWAGORA
    break;
    case 2:
    setPower(255 , 255);
    //GORA
    break;
    case 3:
    setPower(255 , 100);
    //PRAWAGORA
    break;
    case 4:
    setPower(255 , 0);
    //PRAWA;
    break;
    case 5:
    //PRAWADOLNA;
    break;
    case 6:
    //DOL
    break;
    case 7:
    //DOLLEWY;
    break;
    default:
    setPower(0 , 0)
    }
    //Koniec zmiany
}

void loop() {

  if(btSerial.available()){
    mess = btSerial.readStringUntil('\n');
  }
////

  if(mess.length()>0){
    
    Serial.println(mess);
    
    if(mess[0]=='P'){
      int number = mess.substring(1).toInt();
    //   Serial.println(number);

      number = map(number,0,100,0,255);
      analogWrite(lewagora,number);
    }
    else if(mess[0]=='D'){
        int number = mess.substring(1).toInt();
        // Serial.println(number);
    }
//
    mess="";
  }


}