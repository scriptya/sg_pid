# PID LIBRARY

SCRIPTGALIH PID v0.01

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

## pid function

* param(Kp, Ki, Kd, MODE); NORMAL or INTEGRAL
* constraint(min output PID, max output PID);
* setPoint(set point PID);
* readSensor(value of output);
* timeSampling(time sampling in ms);
* showParam(); <- this function just for print parameter (Kp,Ki,Kd,TimeSampling,mode)
* showUnitPID(); <- print output P, I, and D

## Warning !

```
for optimal process, do not use delay()
```

## Authors

* **Galih Setyawan** - *Initial work* - [scriptya](https://github.com/scriptya)


