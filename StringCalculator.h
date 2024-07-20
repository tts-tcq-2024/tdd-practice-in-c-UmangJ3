#include <stdlib.h>
#include <stdio.h>

int add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    int sum = 0;
    const char* delimiter = ",\n";
    char* numbersCopy = strdup(numbers);
    char* token = strtok(numbersCopy, delimiter);

    while (token != NULL) {
        int num = atoi(token);
        if (num <= 1000) {
            sum += num;
        }
        token = strtok(NULL, delimiter);
    }

    free(numbersCopy);
    return sum;
}


