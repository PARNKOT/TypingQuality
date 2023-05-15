#include <string.h>
#include <stdlib.h>
#include "options.h"


extern Option options[OPTIONS_COUNT];


void parseOptions(int argc, char** argv) {
    char option[WORD_LENGTH];

    for(int i = 1; i < argc; ++i) {
        if(strlen(argv[i]) > 1) {
            if(argv[i][0] == '-') {
                strcpy(option, argv[i]);
            } else {
                setOption(option, argv[i]);
            }
            
        }
    }
}

void setOption(char option[], char value[]) {
    for(int i = 0; i < OPTIONS_COUNT; ++i) {
        if(strcmp(options[i].letter, option) == 0 || strcmp(options[i].word, option) == 0) {
            if (options[i].value) {
                free(options[i].value);
            }
            int value_length = strlen(value);
            options[i].value = (char*)malloc(sizeof(char)*(value_length + 1));
            strcpy(options[i].value, value);
            *(options[i].value + strlen(value)) = '\0';
        }
    }
}

char* getOption(char option[]) {
    for(int i = 0; i < OPTIONS_COUNT; ++i) {
        if(strcmp(options[i].letter, option) == 0 || strcmp(options[i].word, option) == 0) {
            return options[i].value;
        }
    }

    return NULL;
}