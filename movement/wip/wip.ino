#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>
#include <Pushbutton.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  	  1500 // microseconds
#define NUM_SENSORS		  6
#define MASTER_SPEED	  400

// these might need to be tuned for different motor types
#define REVERSE_SPEED     MASTER_SPEED 				// 0 is stopped, 400 is full speed
#define TURN_SPEED        300
#define FORWARD_SPEED     MASTER_SPEED
#define FLEE_SPEED		  2*MASTER_SPEED
#define FLEE_DURATION	  -1.25*MASTER_SPEED + 750
#define REVERSE_DURATION  -0.30*MASTER_SPEED + 300 	// ms
#define TURN_DURATION     200 						// ms

Pushbutton button(ZUMO_BUTTON);

ZumoMotors motors;
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

int triggerPort = 2;
int echoPort = 3;

int motorSpeed = 400;
int lSpeed = 105;
int rSpeed = 100;

const float turnAmount = 0.3;
int lExtra = MASTER_SPEED * turnAmount;
int rExtra = 0;

boolean charging = false;
int chargingThreshold = 40;

void setup() {
	pinMode(LED, HIGH);
	pinMode(triggerPort, OUTPUT);
	pinMode(echoPort, INPUT);
	Serial.begin(9600);
	button.waitForButton();
	motors.setSpeeds(FORWARD_SPEED - lExtra, FORWARD_SPEED - rExtra);
}

void loop() {
	sensors.read(sensor_values);
	if (sensor_values[0] < QTR_THRESHOLD ||
		sensor_values[1] < QTR_THRESHOLD ||
		sensor_values[2] < QTR_THRESHOLD) {
		lExtra = 0;
		rExtra = MASTER_SPEED * turnAmount;
		charging = false;
		// if leftmost sensor detects line, reverse and turn to the right
		motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
		delay(REVERSE_DURATION);
		motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
		delay(TURN_DURATION);
		flee();
		motors.setSpeeds(FORWARD_SPEED - lExtra, FORWARD_SPEED - rExtra);
	} else if (sensor_values[3] < QTR_THRESHOLD ||
			   sensor_values[4] < QTR_THRESHOLD ||
		   	   sensor_values[5] < QTR_THRESHOLD) {
		lExtra = MASTER_SPEED * turnAmount;
		rExtra = 0;
		charging = false;
		// if rightmost sensor detects line, reverse and turn to the left
		motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
		delay(REVERSE_DURATION);
		motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
		delay(TURN_DURATION);
		flee();
		motors.setSpeeds(FORWARD_SPEED - lExtra, FORWARD_SPEED - rExtra);
	} else if (!charging) {
		int distance = look();
		if (distance < chargingThreshold) {
			charging = true;
			motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
		}
	} else if (charging) {
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
	if (MASTER_SPEED > 380){
		return;
	}
	motors.setSpeeds(FLEE_SPEED, FLEE_SPEED);
	for (int i = 0; i < FLEE_DURATION; i += 10){
		sensors.read(sensor_values);
		if (sensor_values[0] < QTR_THRESHOLD ||
			sensor_values[1] < QTR_THRESHOLD ||
			sensor_values[2] < QTR_THRESHOLD ||
			sensor_values[3] < QTR_THRESHOLD ||
			sensor_values[4] < QTR_THRESHOLD ||
			sensor_values[5] < QTR_THRESHOLD) {
			return;
		}
		delay(10);
	}
}


int look() {
	digitalWrite(triggerPort, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPort, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPort, LOW);
	// int threshold = chargingThreshold*2*2915.45;
	long duration = pulseIn(echoPort, HIGH, 2200);
	int distance = duration*0.034/2;
	if (distance == 0) {
		distance = 1000;
	}
	return distance;
}
