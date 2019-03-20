#include <Servo.h>

class Scout{

  private:
  
  Servo servo;
  int triggerPort;
  int echoPort;
  long duration;
  int distance;
  
  public: 
  
  Scout::Scout(int trigger, int echo, int s) {
    triggerPort = trigger;
    echoPort = echo;
    servo.attach(s);
    servo.write(0);
    triggerPort = trigger;
    echoPort = echo;
    pinMode(triggerPort, OUTPUT);
    pinMode(echoPort, INPUT);
  }

  int Scout::search() {
    for (int i=0; i<=126; i++) {
      servo.write(i);
      delay(10);
      digitalWrite(triggerPort, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPort, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPort, LOW);
      duration = pulseIn(echoPort, HIGH);
      distance = duration*0.034/2;
      if (distance < 30){
        return i;
      }
    }
    servo.write(0);
    return -1;
  }
  
};

void setup() {
  Scout scout(2, 3, 9);
  delay(1000);
  scout.search();
}

void loop() {
  
}
