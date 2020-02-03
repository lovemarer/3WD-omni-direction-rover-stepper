#include <AccelStepper.h>

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, 5,4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::DRIVER, 10,9);
AccelStepper stepper3(AccelStepper::DRIVER, 7,6);

const int ms3Pin   = 11;   // Ms3
const int ms2Pin   = 12;   // Ms2
const int ms1Pin   = 13;   // Ms1

float rover_radius = 15;
float wheel_radius = 5.22;
float constant_linearVelocity = (0.75*PI*wheel_radius);
float dx = 1;
float dy = -2;
float phi = 31.5/180*PI;
float dphi = 0;
float w = 0;
float v = 0;
float v_n = 0;
float v_x = 0;
float v_y = 0;
float v0 = 0;
float v1 = 0;
float v2 = 0;

float time_limit = 1.0;

void setup()
{  
    stepper1.setMaxSpeed(1000);
    stepper2.setMaxSpeed(1000);
    stepper3.setMaxSpeed(1000);
  
    stepper1.setSpeed(300.0);
    stepper2.setSpeed(300.0);
    stepper3.setSpeed(300.0); 

    Serial.begin(9600);

    pinMode(ms3Pin,OUTPUT);  
    pinMode(ms2Pin,OUTPUT);  
    pinMode(ms1Pin,OUTPUT); 

    digitalWrite(ms1Pin, LOW);
    digitalWrite(ms2Pin, LOW); 
    digitalWrite(ms3Pin, LOW); 


 
}

void loop()
{
  
  time_limit = (sqrt(dx*dx + dy*dy)/constant_linearVelocity)/10;
  
  v_x = dx / time_limit;
  v_y = dy / time_limit;
  w = dphi / time_limit;
  
  v   =  v_x * cos(phi) + v_y * sin(phi);
  v_n = -v_x * sin(phi) + v_y * cos(phi);
  
  v0 = -v * sin(PI / 3) + v_n * cos(PI / 3) + w * rover_radius;
  v1 =                  - v_n               + w * rover_radius;
  v2 =  v * sin(PI / 3) + v_n * cos(PI / 3) + w * rover_radius;
  

  
 // Set the current position to 0:
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);

  
  while(abs(stepper1.currentPosition()) < 800)
  {
    stepper1.setSpeed(v0*2);
    stepper2.setSpeed(v1*2);
    stepper3.setSpeed(v2*2); 
    
    stepper1.runSpeed();
    stepper2.runSpeed();
    stepper3.runSpeed();

    //Serial.println(v1*6);

    

    
  }


  delay(500);


}
