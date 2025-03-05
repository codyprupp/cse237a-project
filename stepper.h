#ifndef STEPPER_H
#define STEPPER_H

#define DIR_PIN 0
#define NUM_MOTORS 2

void playNoteDuration(float frequency, float duration_ms, int motor);
void playNote(float frequency, int motor);
void initMotors();
void stepMotor(int motor);

#endif