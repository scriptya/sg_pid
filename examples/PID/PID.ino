/*
  SCRIPTGALIH PID v0.01
  created by
  2017 Galih Setyawan

  how to use?
  .param(Kp, Ki, Kd, MODE); NORMAL or INTEGRAL
  .constraint(min output PID, max output PID);
  .setPoint(set point PID);
  .readSensor(value of output);
  .timeSampling(time sampling in ms);
  .showParam(); <- this function just for print parameter (Kp,Ki,Kd,TimeSampling,mode)
  .showUnitPID(); <- print output P, I, and D
  don't use delay()!
  
  Contact us : scriptgalih@gmail.com

  Universitas Gadjah Mada
  Yogyakarta

*/

#include "SG_PID.h"

pid balancing;
void setup() {
  Serial.begin(115200);
  balancing.param(5, 4, 0.02, NORMAL);
  balancing.constraint(-5000, 5000);
  balancing.setPoint(0);
  balancing.readSensor(0);
  balancing.timeSampling(1);
  balancing.showParam();

}

void loop() {
  int valSensor = random(-20, 20);
  balancing.readSensor(valSensor);
  
  Serial.print(valSensor); Serial.print("\t");
  balancing.calc();


  balancing.showUnitPID();
  Serial.print(balancing.showPID(), 4);
  Serial.println();
}
