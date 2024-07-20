#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_empty(const char* numbers) {
    return numbers == NULL || strlen(numbers) == 0;
}

int convert_and_sum(const char* token) {
    int num = atoi(token);
    if (num <= 1000) {
        return num;
    }
    return 0;
}

int add(const char* numbers) {
    if (is_empty(numbers)) {
        return 0;
    }

    int sum = 0;
    const char* delimiter = ",\n";
    char* numbersCopy = strdup(numbers);
    char* token = strtok(numbersCopy, delimiter);

    while (token != NULL) {
        sum += convert_and_sum(token);
        token = strtok(NULL, delimiter);
    }

    free(numbersCopy);
    return sum;
}
