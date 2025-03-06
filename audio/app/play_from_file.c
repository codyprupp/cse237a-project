#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>
#include <wiringPi.h>
#include "../../stepper.h"
#include "../../music.h"

int main(int argc, char* argv[]) {
    if (wiringPiSetup() < 0) {
        printf("ERROR: wiringPi initialization failed!\n");
        return 1;
    }

    initMotors();

    //run script to get notes file
    char * audiofile = argv[1];
    char * script = "pull_notes_to_file.py";
    char pycmd[512];

    snprintf(pycmd, sizeof(pycmd), "python3 %s %s", script, audiofile);

    int result = system(pycmd);

    if (result == -1) {
        printf("err\n");
    }
    
    //read notes txt file:

    char * notesfile = basename(argv[1]);

    notesfile[strlen(notesfile) - 4] = '\0';

    char notesfilepath[512];

    snprintf(notesfilepath, sizeof(notesfilepath), "notesfiles/%s.txt", notesfile); 

    FILE * file = fopen(notesfilepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    //iterate through notes read from script
    float freq, dur;
    while(fscanf(file, "%f,%f", &freq, &dur) == 2) { 
        if (notesfile[0] == 'b') {
            playNoteDuration(freq, dur*500, 0);
        } else {
            playNoteDuration(freq, dur * 1000, 0);
        }
        printf("%f %s\n", freq, notesfile);
    }
 
    return 0;
}