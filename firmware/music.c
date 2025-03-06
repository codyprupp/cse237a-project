#include "music.h"
#include "stepper.h"
#include <stdio.h>

// Store each consecutive note as {frequency, noteType}. For rests, set frequency=0. EVERY SONG MUST END WITH {0, 0}.
const float kids_mgmt_tempo = 122; // Tempo in BPM
const float kids_mgmt_melody[][2] = {{A4, QUARTER_NOTE}, {B4, QUARTER_NOTE}, {CS5, QUARTER_NOTE}, {E5, QUARTER_NOTE}, {FS5, QUARTER_NOTE}, {GS5, EIGHTH_NOTE}, {FS5, QUARTER_NOTE}, {E5, QUARTER_NOTE}, {CS5, WHOLE_NOTE}, {CS5, EIGHTH_NOTE}, {B4, WHOLE_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase[][2] = {{FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {FS3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {CS4, EIGHTH_NOTE}, {REST, HALF_NOTE}, {REST, QUARTER_NOTE}, {REST, EIGHTH_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase_end_1[][2] = {{GS3, QUARTER_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {REST, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {E3, EIGHTH_NOTE}, {0, 0}};
const float kids_mgmt_lower_phrase_end_2[][2] = {{REST, EIGHTH_NOTE}, {D4, EIGHTH_NOTE}, {CS4, EIGHTH_NOTE}, {B3, EIGHTH_NOTE}, {A3, QUARTER_NOTE}, {B3, EIGHTH_NOTE}, {A3, EIGHTH_NOTE}, {GS3, EIGHTH_NOTE}, {0, 0}};

const float twinkle_melody[][2] = {
    {C4, QUARTER_NOTE}, {C4, QUARTER_NOTE}, {G4, QUARTER_NOTE}, {G4, QUARTER_NOTE},
    {A4, QUARTER_NOTE}, {A4, QUARTER_NOTE}, {G4, HALF_NOTE},
    {F4, QUARTER_NOTE}, {F4, QUARTER_NOTE}, {E4, QUARTER_NOTE}, {E4, QUARTER_NOTE},
    {D4, QUARTER_NOTE}, {D4, QUARTER_NOTE}, {C4, HALF_NOTE},
    
    {G4, QUARTER_NOTE}, {G4, QUARTER_NOTE}, {F4, QUARTER_NOTE}, {F4, QUARTER_NOTE},
    {E4, QUARTER_NOTE}, {E4, QUARTER_NOTE}, {D4, HALF_NOTE},
    {G4, QUARTER_NOTE}, {G4, QUARTER_NOTE}, {F4, QUARTER_NOTE}, {F4, QUARTER_NOTE},
    {E4, QUARTER_NOTE}, {E4, QUARTER_NOTE}, {D4, HALF_NOTE},

    {C4, QUARTER_NOTE}, {C4, QUARTER_NOTE}, {G4, QUARTER_NOTE}, {G4, QUARTER_NOTE},
    {A4, QUARTER_NOTE}, {A4, QUARTER_NOTE}, {G4, HALF_NOTE},
    {F4, QUARTER_NOTE}, {F4, QUARTER_NOTE}, {E4, QUARTER_NOTE}, {E4, QUARTER_NOTE},
    {D4, QUARTER_NOTE}, {D4, QUARTER_NOTE}, {C4, WHOLE_NOTE},

    {0, 0} // End marker
};

const float clocks_melody[][2] = {
    {DS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {G4, EIGHTH_NOTE},
    {DS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {G4, EIGHTH_NOTE},
    {DS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, 

    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE},

    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {CS5, EIGHTH_NOTE}, {AS4, EIGHTH_NOTE},

    {C5, EIGHTH_NOTE}, {GS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE}, {GS4, EIGHTH_NOTE}, {F4, EIGHTH_NOTE},
    {C5, EIGHTH_NOTE}, {GS4, EIGHTH_NOTE},

    {0, 0} // End marker
};

void playMusic(const float song[][2], float tempo) {
    for (int i = 0; (song[i][0] != 0) || (song[i][1] != 0); i++) {
        printf("%f ", song[i][0]);
        fflush(stdout);
        playNoteDuration(song[i][0], (1000.0f / (tempo / 60.0f)) * song[i][1] * 0.95, 0);
        playNoteDuration(0, (1000.0f / (tempo / 60.0f)) * song[i][1] * 0.05, 0);
    }

    printf("\n");
}