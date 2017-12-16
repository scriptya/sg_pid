/*
   v0.01
   created by
   2017 scriptgalih

   Contact us : scriptgalih@gmail.com

   Departemen Teknik Elektro dan Informatika
   Sekolah Vokasi
   Universitas Gadjah Mada
   Yogyakarta

*/

#define INTEGRAL 1
#define NORMAL 2

class pid {
    /*
      sv = set point
      pv = pembacaan sensor
      e  = error
      Kp = Gain Proportional
      Ki = Gain Integral
      Kd = Gain  Derivative
      Tc = Time Sampling (ms)
      mode = dU intergal / normal
    */
    float sv = 0, pv = 0, e, integralE, derivativeE, Kp = 0, Ki = 0, Kd = 0, dU = 0;
    int syntaxError = 0;
    unsigned long previousMillis = 0;
    float outP, outI, outD;
    float maxOut = 0;
    float minOut = 0;
    long lastTimeTC;
    float outPID, Tc;
    int mode;
    int first = 1;
  public:
    void param(float  Kp, float  Ki, float  Kd, int mode);
    void setPoint(float sv);
    void constraint(float minOut, float maxOut);
    void readSensor(float pv);
    void timeSampling(int Tc);
    float showPID() {
      return outPID;
    }
    void showParam() {
      Serial.print(" Kp:"); Serial.print(Kp);
      Serial.print(" Ki:"); Serial.print(Ki);
      Serial.print(" Kd:"); Serial.print(Kd);
      Serial.print(" Tc:"); Serial.print(Tc);
      Serial.print("ms mode:");
      if (mode == 1) {
        Serial.print("INTEGRAL");
      } else {
        Serial.print("NORMAL");
      }
    }
	void showUnitPID(){
      Serial.print(outP); Serial.print("\t");
      Serial.print(outI); Serial.print("\t");
      Serial.print(outD); Serial.print("\t");
    }
	//pid calculation
    int calc() {
      //catch error
      if (syntaxError == 1)while (1);
	  
	  //error calculation
      e = sv - pv;
	  
      //Derivative protection spike value
      if (first == 1) {
        first = 0;
        derivativeE = e;
      }
	  //time sampling detection
      unsigned long Time = micros();
      if (Time - lastTimeTC >= (Tc * 1000)) {
        float tc =  (Time - lastTimeTC) / 1000000.0;
        lastTimeTC = Time;
		
        //Proportional calculation
        outP = Kp * e;
		
        //Integral calculation
        integralE += e;
        outI = Ki * integralE * tc; 

        //Derivative calculation
        derivativeE = e - derivativeE;
        outD = (Kd * derivativeE) / tc; 
        derivativeE = e;
		
		//delta U output
        dU = outP + outI + outD;
		
		//case mode
        if (mode == 1) {
          outPID += dU;
        } else {
          outPID = dU;
        }
		
		//limit output value
        if (maxOut != 0 || minOut != 0) {
          if (outPID >= maxOut) {
            outPID = maxOut;
            integralE -= e;
          } else if (outPID <= minOut) {
            outPID = minOut;
            integralE -= e;
          }
        }
		//Serial.print(integralE);Serial.print("\t");

        return outPID;
      }
    }
};

void pid::param(float  vKp, float  vKi, float  vKd, int vmode) {
  Kp = vKp;
  Ki = vKi;
  Kd = vKd;
  mode = vmode;
}

void pid::readSensor(float vPv) {
  pv = vPv;
}

void pid::setPoint(float sp) {
  sv = sp;
}
void pid::timeSampling( int ts) {
  Tc = ts;
}

void pid::constraint(float Min, float Max) {
  minOut = Min;
  maxOut = Max;
  if (minOut > maxOut) {
    Serial.println("Error 1 \nThe value of min don't over velue of max \n.constraint(min,max)");
    syntaxError = 1;
  }
}
