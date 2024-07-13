#include <Servo.h>

Servo servohori; //horizontal servo(BOTTOM SERVO)
int servoh = 90; //assign servo at 0 degree
int servohLimitHigh = 170; //maximum range of servo is 180 degree(it is variable you can also change)
int servohLimitLow = 10;   //minimum range of servo is 10 degree(it is variable you can also change)

Servo servoverti; //vertical servo(TOP SERVO) 
int servov = 90; 
int servovLimitHigh = 170;
int servovLimitLow = 10;

int ldrtopl = A0; //top right LDR A1 pin  blue
int ldrtopr = A1; //top left LDR A2 pin    purple
                    // vcc                 green
int ldrbotl = A2; // bottom right LDR A0 pin   gray
int ldrbotr = A3; // bottom left LDR A3 pin    white


 void setup () 
 {
  servohori.attach(10); //horizontal servo connected to arduino pin 10
  servohori.write(90);
  
  servoverti.attach(9); //vertical servo connected to arduino pin 9
  servoverti.write(90);
  delay(1500); //delay
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  
  
  int topl = analogRead(ldrtopl); //read analog values from top left LDR
  int topr = analogRead(ldrtopr); //read analog values from top right LDR
  int botl = analogRead(ldrbotl); //read analog values from bottom left LDR
  int botr = analogRead(ldrbotr); //read analog values from bottom right LDR
  
  
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)
  {
    servov=servov -1;
    
    if (servov < servovLimitLow) 
     { 
      servov = servovLimitLow;
     }
    servoverti.write(servov);
    delay(100);
  }
  else if (avgbot < avgtop)
  {
    servov=servov +1;
    
    if (servov > servovLimitHigh)
  {
    servov = servovLimitHigh;
  }
    servoverti.write(servov);
    delay(100);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft < avgright)
  {
    servoh = servoh + 1;
    
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    servohori.write(servoh);
    delay(100);
  }
  else if (avgright < avgleft)
  {
    servoh = servoh - 1;
    
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    servohori.write(servoh);
    delay(100);
  }
  else 
  {
    servohori.write(servoh); // write means run servo
  }
  delay(100);
}