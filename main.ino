#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX, TX
String mess;

int leftUp = 5;
int leftDown = 6;
int rightUp = 9;
int rightDown = 10;


static unsigned long lastTime = 0;

int multPower = 0;

void setup()
{
  pinMode(leftUp, OUTPUT);
  pinMode(leftDown, OUTPUT);
  pinMode(rightUp, OUTPUT);
  pinMode(rightDown, OUTPUT);

  pinMode(8, OUTPUT);

  pinMode(13, OUTPUT);
  

  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("Start");

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}


void setReverseDir(bool l,bool r){
  digitalWrite(8,l);
}

void setPower(int l, int r)
{
  int lM = map(l * multPower, 0, 10000, 0, 100);
  int rM = map(r * multPower, 0, 10000, 0, 100);

  if( lM > 100 || rM > 100) return;
  if( lM < 0 || rM < 0) return;

  analogWrite(leftUp, lM);
  analogWrite(11, lM);

  analogWrite(leftDown, lM);

  analogWrite(rightUp, rM);
  analogWrite(rightDown, rM);

   Serial.println(lM);
}


bool onOffSwith = true;

void loop()
{

  if (btSerial.available())
  {
    mess = btSerial.readStringUntil('\n');
  }

  if (mess.length() > 0)
  {
    lastTime = millis();

    if (mess[0] == 'P')
    {
      int number = mess.substring(1).toInt();
  
      if(number <= 0 ) number = 0;
      if(number > 10000) number = 0;

      multPower = number;
    }
    else if (mess[0] == 'D')
    {
      int number = mess.substring(1).toInt();
      setDirection(number);
    }
    
    mess = "";
  }

  if(millis() - lastTime > 1000){
  
    multPower = 100;
    

    if(onOffSwith) {setPower(1,1); onOffSwith = false;}
    else{
      setPower(0,0); onOffSwith = true;
    }

    lastTime = millis();
  }


}

void setDirection(int d)
{  switch (d)
  {
  case -1:
    setPower(1, 1);
    setReverseDir(false,false);
    //Center
    break;
  case 0:
    setPower(100, 100);   
    setReverseDir(true,false);
    //Left
    break;
  case 1:
    setPower(50, 100);
    //leftUp
    break;
  case 2:
    setPower(100, 100);
    setReverseDir(false,false);
    //Up
    break;
  case 3:
    setPower(100, 50);
    //RightUp
    break;
  case 4:
    setPower(100, 1);
    setReverseDir(false,true);
    //Right;
    break;
  case 5:
    //RightDown;
    setPower(1, 1);
    break;
  case 6:
    //Down
    setPower(1, 1);
    setReverseDir(true,true);
    break;
  case 7:
    //DOLLEWY;
    setPower(1, 1);
    break;
  default:
    setPower(1, 1);
  }
}