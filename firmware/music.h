#ifndef MUSIC_H
#define MUSIC_H

#define A0 27.50
#define AS0 29.14
#define B0 30.87

#define C1 32.70
#define CS1 34.65
#define D1 36.71
#define DS1 38.89
#define E1 41.20
#define F1 43.65
#define FS1 46.25
#define G1 49.00
#define GS1 51.91
#define A1 55.00
#define AS1 58.27
#define B1 61.74

#define C2 65.41
#define CS2 69.30
#define D2 73.42
#define DS2 77.78
#define E2 82.41
#define F2 87.31
#define FS2 92.50
#define G2 98.00
#define GS2 103.83
#define A2 110.00
#define AS2 116.54
#define B2 123.47

#define C3 130.81
#define CS3 138.59
#define D3 146.83
#define DS3 155.56
#define E3 164.81
#define F3 174.61
#define FS3 185.00
#define G3 196.00
#define GS3 207.65
#define A3 220.00
#define AS3 233.08
#define B3 246.94

#define C4 261.63
#define CS4 277.18
#define D4 293.66
#define DS4 311.13
#define E4 329.63
#define F4 349.23
#define FS4 369.99
#define G4 392.00
#define GS4 415.30
#define A4 440.00
#define AS4 466.16
#define B4 493.88

#define C5 523.25
#define CS5 554.37
#define D5 587.33
#define DS5 622.25
#define E5 659.25
#define F5 698.46
#define FS5 739.99
#define G5 783.99
#define GS5 830.61
#define A5 880.00
#define AS5 932.33
#define B5 987.77

#define REST 0

// Duration modifiers
#define SIXTEENTH_NOTE 0.25
#define EIGHTH_NOTE 0.5
#define QUARTER_NOTE 1.0
#define HALF_NOTE 2.0
#define WHOLE_NOTE 4.0

extern const float kids_mgmt_melody[][2];
extern const float kids_mgmt_lower_phrase[][2];
extern const float kids_mgmt_lower_phrase_end_1[][2];
extern const float kids_mgmt_lower_phrase_end_2[][2];
extern const float twinkle_melody[][2];
extern const float clocks_melody[][2];

void playMusic(const float song[][2], float tempo);

#endif