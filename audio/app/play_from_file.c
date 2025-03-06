#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>

int main(int argc, char* argv[]) {

    //grab notes using script:
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
    printf(notesfilepath);
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    float freq, dur;
    while(fscanf(file, "%f,%f", &freq, &dur) == 2) { 
        //TODO: play the note on the motor
        printf("temp test line\n");
    }
 
    return 0;
}