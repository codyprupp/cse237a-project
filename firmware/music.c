#include "music.h"
#include "stepper.h"
#include <stdio.h>

// Store each consecutive note as {frequency, noteType}. For rests, set frequency=0. EVERY SONG MUST END WITH {0, 0}.
const float kids_mgmt_tempo = 122; // Tempo in BPM
const float kids_mgmt_melody[][2] = {{A4, QUARTER_NOTE}, {B4, QUARTER_NOTE}, {CS5, QUARTER_NOTE}, {E5, QUARTER_NOTE}, {FS5, QUARTER_NOTE}, {GS5, EIGHTH_NOTE}, {FS5, QUARTER_NOTE}, {E5, QUARTER_NOTE}, {CS5, WHOLE_NOTE}, {CS5, EIGHTH_NOTE}, {B4, WHOLE_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase[][2] = {{FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {CS4, EIGHTH_NOTE}, {REST, HALF_NOTE}, {REST, QUARTER_NOTE}, {REST, EIGHTH_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase_end_1[][2] = {{GS3, QUARTER_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {E3, EIGHTH_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase_end_2[][2] = {{REST, EIGHTH_NOTE}, {D4, EIGHTH_NOTE}, {CS4, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {A3, QUARTER_NOTE}, {B3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {0, 0}};

void playMusic(const float song[][2]) {
    // printf("STARTING... (notes: %d)\n", numNotes); 

    for (int i = 0; (song[i][0] != 0) || (song[i][1] != 0); i++) {
        printf("%f ", song[i][0]);
        fflush(stdout);
        playNoteDuration(song[i][0], (1000.0f / (kids_mgmt_tempo / 60.0f)) * song[i][1], 0);
    }

    printf("\n");
}