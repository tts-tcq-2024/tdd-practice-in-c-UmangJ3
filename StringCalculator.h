#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>

int is_empty(const char* numbers) {
    return numbers == NULL || strlen(numbers) == 0;
}

int convert_and_sum(const char* token) {
    int num = atoi(token);
    return (num <= 1000) ? num : 0;
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

const char* find_delimiter_start(const char* numbers) {
    return numbers + 2; // Skip the "//" part
}

const char* find_delimiter_end(const char* delimiter_start) {
    return strchr(delimiter_start, '\n');
}

char* process_custom_delimiter(const char* delimiter_start, size_t len) {
    if (delimiter_start[0] == '[' && delimiter_start[len-1] == ']') {
        delimiter_start++;
        len -= 2;
    }
    return create_delimiter(delimiter_start, len);
}

char* extract_custom_delimiter(const char* numbers) {
    const char* delimiter_start = find_delimiter_start(numbers);
    const char* delimiter_end = find_delimiter_end(delimiter_start);
    
    if (delimiter_end) {
        size_t len = delimiter_end - delimiter_start;
        return process_custom_delimiter(delimiter_start, len);
    }
    return NULL;
}

char* default_delimiter() {
    return strdup(",\n");
}

char* get_delimiter(const char* numbers) {
    if (numbers[0] == '/' && numbers[1] == '/') {
        char* delimiter = extract_custom_delimiter(numbers);
        if (delimiter) {
            return delimiter;
        }
    }
    return default_delimiter();
}

const char* extract_numbers_part(const char* numbers) {
    if (numbers[0] == '/' && numbers[1] == '/') {
        const char* num_start = strchr(numbers, '\n');
        return (num_start) ? num_start + 1 : numbers;
    }
    return numbers;
}

int sum_tokens(const char* numbers, const char* delimiter) {
    int sum = 0;
    char* numbersCopy = strdup(numbers);
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
    const char* num_start = extract_numbers_part(numbers);
    
    check_for_negatives(num_start, delimiter);
    int sum = sum_tokens(num_start, delimiter);

    free(delimiter);
    return sum;
}
