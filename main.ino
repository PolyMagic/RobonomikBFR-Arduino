#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX, TX
String mess;

int leftUp = 5;
int leftDown = 6;
int rightUp = 9;
int rightDown = 10;

void setup()
{
  pinMode(leftUp, OUTPUT);
  pinMode(leftDown, OUTPUT);
  pinMode(rightUp, OUTPUT);
  pinMode(rightDown, OUTPUT);

  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("Start");
}

int multPower = 0;
void setPower(int l, int p)
{
  int lM = map(l * multPower, 0, 10000, 0, 100);
  int pM = map(p * multPower, 0, 10000, 0, 100);

  if( lM > 100 || pM > 100) return;
  if( lM < 0 || pM < 0) return;

  Serial.println("l:"+ String(lM));
  Serial.println("p:"+ String(pM));

  analogWrite(leftUp, lM);
  analogWrite(leftDown, lM);

  analogWrite(rightUp, pM);
  analogWrite(rightDown, pM);
}


int lastTime = 0;

void loop()
{
  if (btSerial.available())
  {
    mess = btSerial.readStringUntil('\n');
  }
  ////

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
      // Serial.println(number);
      setDirection(number);
    }
    //
    mess = "";
  }

  if(millis() - lastTime > 1000){
    setPower(0,0);
  }
}

void setDirection(int d)
{  switch (d)
  {
  case -1:
    setPower(0, 0);
    //Center
    break;
  case 0:
    setPower(0, 100);
    //Left
    break;
  case 1:
    setPower(50, 100);
    //leftUp
    break;
  case 2:
    setPower(100, 100);
    //Up
    break;
  case 3:
    setPower(100, 50);
    //RightUp
    break;
  case 4:
    setPower(100, 0);
    //Right;
    break;
  case 5:
    //RightDown;
    setPower(0, 0);
    break;
  case 6:
    //Down
    setPower(0, 0);
    break;
  case 7:
    //DOLLEWY;
    setPower(0, 0);
    break;
  default:
    setPower(0, 0);
  }
}