#include <Servo.h>/////
Servo servo_right_pin;  //to define the right servo
Servo servo_left_pin;  //to define the left servo 

int trac1 = 5; //set the NO1 tracing port to be 1(data[0])
int trac2 = 7; //set the NO2 tracing port to be 2(data[1])
int Ecoh=3;//pinout of echo
int Trig=2;//pinout of trig
int Distance; 
int time;

Servo myServo;  //servo

void setup() {
  // put your setup code here, to run once:
  //to initialize port 
  // Serial.begin(9600); 
  //to initialize port of the servo's pinout
  // myServo.attach(9);
  Serial.begin(9600);//to initial the serial port
  pinMode(Ecoh,INPUT);//to define the ultrasonic input pin
  pinMode(Trig,OUTPUT);//to define the ultrasonic output pin
  servo_right_pin.attach(9);//set right serial port to be 9
  servo_left_pin.attach(12);//set left serial port to be 10
  //distance
  // servo_pin_right.attach(9); //  set the pinout servo to be 9
  // servo_pin_left.attach(12);
 
  //initialize the section of D0 pinout of tracing sector
  pinMode(trac1, INPUT);
  pinMode(trac2, INPUT);

  digitalWrite(trac1,HIGH);
  digitalWrite(trac2,HIGH);

//loop();
}

void loop() {
  // put your main code here, to run repeatedly:
 
  distance();  

}

void Distance_test()//distance test 
{
    digitalWrite(Trig,LOW);//low level for 2ms
    delayMicroseconds(2);
    digitalWrite(Trig,HIGH);//high level for 10ms
    delayMicroseconds(10);
    digitalWrite(Trig,LOW);//keep the pinout low level
    float Fdistance=pulseIn(Ecoh,HIGH);//get the high level time
    Fdistance=Fdistance/58;//L(m)=t(s)*344/2
    Distance=Fdistance;
    if(Fdistance<400)
    {
      Serial.print("Distance:");// output the distance
      Serial.print(Fdistance);//show distance
      Serial.print("cm\n");
    }
    else
      Serial.print("!!!out of range!!!\n");
}

void distance()
{
  //judege the distance
  
    Distance_test();
    if(Distance<30)
    {
      while(Distance<50)
      {   
        car_right(2);
        car_stop(1);
        Distance_test();
      }
    }
    else
   tracing();
  
  
}

void tracing()
{
  int data[2] = {0};
  data[0] = digitalRead(5);
  data[1] = digitalRead(7);

  if(data[1]&&!data[0])  // examing the rightside of the black wire
  {
  servo_left_pin.writeMicroseconds(1700);// left wheel forwoard
  servo_right_pin.writeMicroseconds(1700);// right wheel backwoard
  Serial.println("Turn Right");
  delay( 100 );//执行时间excute time
  }

  else if(data[0]&&!data[1])  // examing the leftside of the black wire
  {
  servo_left_pin.writeMicroseconds(1300);// left wheel moving forwoard 
  servo_right_pin.writeMicroseconds(1300);// right wheel moving backwoard
  Serial.println("Turn Left");
  delay( 100 );// excute time
  }

  else // moving forwoard
  {
  car_go();
  }

  // Serial.println(data[0]);
  // Serial.println("---");
  // Serial.println(data[1]);
  // Serial.println("\n");
 
}

void car_go()
{
  servo_left_pin.writeMicroseconds(1650);//left wheel moving forwoard
  servo_right_pin.writeMicroseconds(1250);//right wheel moving backwoard
  Serial.println("Moving");
  //delay( 100*time );//excute time
}
void car_left(int time)//turn left
{
 servo_left_pin.write(-200);//left wheel goning backwoard
  servo_right_pin.write(-360);//right wheel going forwoard
  // delay( 100*time );//excute time
}
void car_back(int time)//go backwoard
{
  servo_left_pin.write(-360);//left wheel moving backwoard
 servo_right_pin.write(360);//right wheel moving backwoard
  // delay( 100*time );//excute time
}
void car_right(int time)//turn right
{
  servo_left_pin.write(360);//left wheel moving forwoard
  servo_right_pin.write(-200);//right wheel moving forwoard
  // delay( 100*time );//excute time 
}
void car_stop(int time)//vehichle stop 
{
   servo_left_pin.write(90);//left wheel stop
  servo_right_pin.write(90);//right wheel stop
  // delay( 100*time );//excute time 
}

