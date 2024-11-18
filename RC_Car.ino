#include <SoftwareSerial.h>
int MP1=4;
int MP2=5;
int MP3=6;
int MP4=7;

int Trig=11;
int Echo=10;

bool isPathFinder=false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MP1,OUTPUT);
  pinMode(MP2,OUTPUT);
  pinMode(MP3,OUTPUT);
  pinMode(MP4,OUTPUT);

  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  stopMotors();
  Serial.println("Remote Controlled Mode activated");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char command=Serial.read();
    if(command=='M'){
      isPathFinder=!isPathFinder;
      if(isPathFinder==true){
        Serial.println("Path Finder Mode activated");
      }else{
        Serial.println("Remote Controlled Mode activated");
      }
    }
    if(isPathFinder){
      pathFinderMode();
    }else{
      remoteControlledMode(command);
    }
  }
}
void remoteControlledMode(char command){
  switch(command){
    case 'F': moveForward();  break;
    case 'B': moveBackward();  break;
    case 'L': turnLeft();  break;
    case 'R': turnRight();  break;
    default: stopMotors(); break;
  }
}
void pathFinderMode(){
  long distance = getdistance();
  if(distance>20){
    moveForward();
    delay(1000);
  }else{
    stopMotors();
    delay(200);
    turnRight();
    delay(1000);
    long distance1 = getdistance();
    if(distance1<20){
      stopMotors();
      delay(200);
      turnLeft();
      delay(1000);
      stopMotors();
      delay(200);
      turnLeft();
      delay(1000);
      long distance2 = getdistance();
      if(distance2<20){
        stopMotors();
        Serial.println("No Path Detected");
      }else{
        moveForward();
      }
    }else{
      moveForward();
    }
  }
}
void moveForward(){
  digitalWrite(8,255);
  digitalWrite(9,255);
  digitalWrite(MP1,HIGH);
  digitalWrite(MP2,LOW);
  digitalWrite(MP3,HIGH);
  digitalWrite(MP4,LOW);
}
void moveBackward(){
  digitalWrite(8,255);
  digitalWrite(9,255);
  digitalWrite(MP1,LOW);
  digitalWrite(MP2,HIGH);
  digitalWrite(MP3,LOW);
  digitalWrite(MP4,HIGH);
}
void turnRight(){
  digitalWrite(8,255);
  digitalWrite(9,255);
  digitalWrite(MP1,HIGH);
  digitalWrite(MP2,LOW);
  digitalWrite(MP3,LOW);
  digitalWrite(MP4,HIGH);
}
void turnLeft(){
  digitalWrite(8,255);
  digitalWrite(9,255);
  digitalWrite(MP1,LOW);
  digitalWrite(MP2,HIGH);
  digitalWrite(MP3,HIGH);
  digitalWrite(MP4,LOW);
}
void stopMotors(){
  digitalWrite(MP1,LOW);
  digitalWrite(MP2,LOW);
  digitalWrite(MP3,LOW);
  digitalWrite(MP4,LOW);
}
double getdistance(){
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  long duration = pulseIn(Echo,HIGH);
  long distance = duration * 0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}