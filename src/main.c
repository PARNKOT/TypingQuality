#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
    #include <sys/time.h>
#elif _WIN32 || _WIN64
    #include <windows.h>
#endif

#include "options.h"
#include "utils.h"
//struct timeval {};

typedef struct {
    int percent;
    struct timeval time_start;
    struct timeval time_end;
    long time_interval_s;
    long time_interval_ms;
} Metrics;


void mainLoop();
int compareStrings(char* s1, char* s2);
int compareWords(char *word1, char *word2);
Metrics readUserStringAndCalcMetrics(char* str_to_repeat, size_t length);


Option options[OPTIONS_COUNT] = {
    {"-f", "--file"},
};

FILE *file;

void print_file(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    
    while(getline(&line, &len, file) != -1) {
        printf("%s", line);
    }

    if (line) {
        free(line);
    }
}

void print_metrics(const Metrics *metrics) {
    printf("\nMetrics:\n\tPercent: %i %%\n\tStart time: %li\n\tEnd time: %li\n\tTime interval [ms]: %li\n\n",
           metrics->percent, metrics->time_start.tv_sec, metrics->time_end.tv_sec,
           metrics->time_interval_ms);
}

int main(int argc, char** argv) {
    #if __linux__
    printf("Posix OS\n\n");
    #elif _WIN32 || _WIN64
    printf("Windows OS\n\n");
    #endif

    parseOptions(argc, argv);
    
    if (file = fopen(getOption("-f"), "r")) {
        mainLoop();
        fclose(file);
    } else {
        perror("Couldn't open file");
    }

    return 0;
}


void mainLoop() {
    char *file_line = NULL;
    char *user_line = NULL;
    
    int total_percent = 0;
    long total_time_ms = 0;

    int sentences_count = 0;


    size_t current_len = 0;

    while(getline(&file_line, &current_len, file) != -1) {
        if (strcmp(file_line, "\n") == 0) {
            continue;
        }

        Metrics metrics;

        metrics = readUserStringAndCalcMetrics(file_line, current_len);
        print_metrics(&metrics);

         total_percent += metrics.percent;
         total_time_ms += metrics.time_interval_ms;
         sentences_count += 1;  
    }

    printf("\nAverage percent:\t%i %%\n", total_percent/sentences_count);
    printf("Total time:\t\t%ld ms\n", total_time_ms);

    if (file_line) {
        free(file_line);
    }
}

Metrics readUserStringAndCalcMetrics(char* str_to_repeat, const size_t length) {
    char user_line[length];
    Metrics metrics;

    printf("-> %s<- ", str_to_repeat);

    gettimeofday(&metrics.time_start, NULL);

    scanf("%[^\n]%*c", user_line);

    gettimeofday(&metrics.time_end, NULL);

    metrics.time_interval_s = (metrics.time_end.tv_sec - metrics.time_start.tv_sec);
    metrics.time_interval_ms = (((metrics.time_interval_s * 1000000) +
                                  metrics.time_end.tv_usec) - (metrics.time_start.tv_usec))/1000;

    metrics.percent = compareStrings(str_to_repeat, user_line);

    return metrics;
}

#if __linux__ || __unix || __unix__
int compareStrings(char* base, char* s) {
    char *word1, *word2;
    char *last1, *last2;
    int matches = 0;
    int sum_length = 0;

    word1 = __strtok_r(base, " ,", &last1);
    word2 = __strtok_r(s, " ,", &last2);
    while( word1 != NULL && word2 != NULL ) {
        sum_length += strlen(word1);
        matches += compareWords(word1, word2);

        word1 = __strtok_r(NULL, " ", &last1);
        word2 = __strtok_r(NULL, " ", &last2);
    }

    while(word1 != NULL) {
        sum_length += strlen(word1) - 1;
        word1 = __strtok_r(NULL, " ", &last1);
    }

    return matches*100/(sum_length-1);
}

#elif _WIN32 || _WIN64
int compareStrings(char* base, char* s) {
    char *word1, *word2;
    int last1 = 0, last2 = 0;
    int matches = 0;
    int sum_length = 0;
    
    word1 = strtok_my(base, ' ', &last1);
    word2 = strtok_my(s, ' ', &last2);
    while( word1 != NULL && word2 != NULL ) {
        sum_length += strlen(word1);
        matches += compareWords(word1, word2);

        free(word1);
        free(word2);
        word1 = strtok_my(base, ' ', &last1);
        word2 = strtok_my(s, ' ', &last2);
    }

    while(word1 != NULL) {
        sum_length += strlen(word1) - 1;
        free(word1);
        word1 = strtok_my(base, ' ', &last1);
    }

    if (word2) {
        free(word2);
    }

    return matches*100/(sum_length-1);
}

#endif

int compareWords(char *word1, char *word2) {
    int count_matches = 0;
    
    while(*word1 != '\0' && *word2 != '\0') {
        *word1 == *word2 ? ++count_matches : 0;
        *word1 != '\0' ? ++word1 : 0;
        *word2 != '\0' ? ++word2 : 0;
    }

    return count_matches;
}
