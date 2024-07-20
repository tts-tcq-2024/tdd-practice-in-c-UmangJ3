#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>

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

void accumulate_negatives(const char* token, char* negative_numbers, int* found_negative) {
    int num = atoi(token);
    if (num < 0) {
        if (*found_negative) {
            strcat(negative_numbers, ",");
        }
        strcat(negative_numbers, token);
        *found_negative = 1;
    }
}

void check_for_negatives(const char* numbers, const char* delimiter) {
    char* numbersCopy = strdup(numbers);
    char* token = strtok(numbersCopy, delimiter);
    char negative_numbers[256] = "";
    int found_negative = 0;

    while (token != NULL) {
        accumulate_negatives(token, negative_numbers, &found_negative);
        token = strtok(NULL, delimiter);
    }

    free(numbersCopy);

    if (found_negative) {
        char error_message[300];
        sprintf(error_message, "negatives not allowed: %s", negative_numbers);
        throw std::runtime_error(error_message);
    }
}

char* create_delimiter(const char* delimiter_start, size_t len) {
    char* delimiter = (char*)malloc(len + 1);
    strncpy(delimiter, delimiter_start, len);
    delimiter[len] = '\0';
    return delimiter;
}

char* extract_custom_delimiter(const char* numbers) {
    const char* delimiter_start = numbers + 2;
    const char* delimiter_end = strchr(delimiter_start, '\n');
    if (delimiter_end) {
        size_t len = delimiter_end - delimiter_start;
        if (delimiter_start[0] == '[' && delimiter_start[len-1] == ']') {
            delimiter_start++;
            len -= 2;
        }
        return create_delimiter(delimiter_start, len);
    }
    return NULL;
}

char* get_delimiter(const char* numbers) {
    if (numbers[0] == '/' && numbers[1] == '/') {
        char* delimiter = extract_custom_delimiter(numbers);
        if (delimiter) {
            return delimiter;
        }
    }
    return strdup(",\n");
}

char* prepare_numbers_copy(const char* numbers, const char* delimiter) {
    char* numbersCopy = strdup(numbers);
    if (numbers[0] == '/' && numbers[1] == '/') {
        const char* num_start = strchr(numbers, '\n') + 1;
        return strdup(num_start);
    }
    return numbersCopy;
}

int sum_tokens(const char* numbers, const char* delimiter) {
    int sum = 0;
    char* numbersCopy = prepare_numbers_copy(numbers, delimiter);
    char* token = strtok(numbersCopy, delimiter);

    while (token != NULL) {
        sum += convert_and_sum(token);
        token = strtok(NULL, delimiter);
    }

    free(numbersCopy);
    return sum;
}

int add(const char* numbers) {
    if (is_empty(numbers)) {
        return 0;
    }

    char* delimiter = get_delimiter(numbers);
    const char* num_start = (numbers[0] == '/' && numbers[1] == '/') ? strchr(numbers, '\n') + 1 : numbers;
    
    check_for_negatives(num_start, delimiter);
    int sum = sum_tokens(num_start, delimiter);

    free(delimiter);
    return sum;
}
