/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** file_conversion
*/

#ifndef FILE_CONVERSION_H_
    #define FILE_CONVERSION_H_

typedef struct bin_array_s {
    unsigned char *data;
    int size;
} bin_array_t;

bin_array_t *hex_to_bin(char *hex_string);
char *bin_to_hex(bin_array_t *array);

#endif /* !FILE_CONVERSION_H_ */
