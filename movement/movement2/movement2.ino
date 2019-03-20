#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>
#include <Servo.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  	  1500 // microseconds
#define NUM_SENSORS		  6
#define MASTER_SPEED	  300

// these might need to be tuned for different motor types
#define REVERSE_SPEED     MASTER_SPEED // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     MASTER_SPEED
#define FLEE_SPEED		  2*MASTER_SPEED
#define FLEE_DURATION	  -1.25*MASTER_SPEED + 750
#define REVERSE_DURATION  -0.30*MASTER_SPEED + 300 // ms
#define TURN_DURATION     300 // ms


ZumoMotors motors;
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void edgeDetect() {
	sensors.read(sensor_values);
	if (sensor_values[0] > QTR_THRESHOLD ||
		sensor_values[1] > QTR_THRESHOLD ||
		sensor_values[2] > QTR_THRESHOLD) {
		// if leftmost sensor detects line, reverse and turn to the right
		motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
		delay(REVERSE_DURATION);
		motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
		delay(TURN_DURATION);
		flee();
		motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
	} else if (sensor_values[3] > QTR_THRESHOLD ||
		sensor_values[4] > QTR_THRESHOLD ||
		sensor_values[5] > QTR_THRESHOLD) {
		// if rightmost sensor detects line, reverse and turn to the left
		motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
		delay(REVERSE_DURATION);
		motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
		delay(TURN_DURATION);
		flee();
		motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
	} else {
		// otherwise, go straight
		motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
	}
}

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
			for (int i=0; i<=126; i += 4) {
				edgeDetect();
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

Scout scout(4, 5, 6);

void setup() {
	pinMode(LED, HIGH);
	Serial.begin(9600);
}


void flee() {
	motors.setSpeeds(FLEE_SPEED, FLEE_SPEED);
	for (int i = 0; i < FLEE_DURATION; i += 10){
		sensors.read(sensor_values);
		if (sensor_values[0] > QTR_THRESHOLD ||
			sensor_values[1] > QTR_THRESHOLD ||
			sensor_values[2] > QTR_THRESHOLD ||
			sensor_values[3] > QTR_THRESHOLD ||
			sensor_values[4] > QTR_THRESHOLD ||
			sensor_values[5] > QTR_THRESHOLD) {
			return;
		}
		delay(10);
	}
}


void loop() {
	scout.search();
}
