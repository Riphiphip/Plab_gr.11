#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1500 // microseconds
#define NUM_SENSORS 6

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200
#define FLEE_SPEED		  400
#define FLEE_DURATION	  500
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

ZumoMotors motors;
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

int motorSpeed = 400;
int lSpeed = 105;
int rSpeed = 100;

void setup() {
	pinMode(LED, HIGH);
}

void loop() {

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

void setSpeed(int speed) {
	for (int i = 0; i < speed; i += 150) {
		motorSpeed = i;
		motors.setSpeeds(motorSpeed, motorSpeed);
		delay(30);
	}
	motors.setSpeeds(speed, speed);
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
