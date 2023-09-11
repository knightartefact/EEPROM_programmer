/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** file_conversion
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "file_conversion.h"

bin_array_t *hex_to_bin(char *hex_string)
{
    bin_array_t *array = malloc(sizeof(bin_array_t));
    char substring[3];
    int hex_size = strlen(hex_string);

    array->data = malloc(sizeof(int) * (hex_size + 1));
    array->size = 0;
    for (int i = 0; i < hex_size; i += 2) {
        strncpy(substring, hex_string + i, 2);
        substring[2] = 0;
        array->data[array->size] = (int)strtol(substring, NULL, 16);
        array->size++;
    }
    return array;
}

char *bin_to_hex(bin_array_t *array)
{
    char *hex_array = malloc(sizeof(char) * (array->size * 2 + 1));
    char hex_str[256];

    hex_array[0] = 0;
    for (int i = 0; i < array->size; i++) {
        sprintf(hex_str, "%02X", array->data[i]);
        strcat(hex_array, hex_str);
    }
    return hex_array;
}

