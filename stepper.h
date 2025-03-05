#ifndef STEPPER_H
#define STEPPER_H

#define DIR_PIN 0
#define NUM_MOTORS 2

// Note frequencies
#define C 130.81
#define D 146.83
#define E 164.81
#define F 174.61
#define G 196.00
#define A 220.00
#define B 246.94

void playNoteDuration(float frequency, float duration_ms, int motor);
void playNote(float frequency, int motor);
void initMotors();
void stepMotor(int motor);

#endif