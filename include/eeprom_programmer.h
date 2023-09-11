/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** eeprom_programmer
*/

#ifndef EEPROM_PROGRAMMER_H_
    #define EEPROM_PROGRAMMER_H_
    #include <stdio.h>
    #include "options.h"
    #define MAX_ADDR 32768
    #define READ_SIZE 256
    #define PAGE_SIZE 64

typedef struct port_io_s {
    int port_fd;
    FILE *port_stream;
    options_t options;
} port_io_t;

#endif /* !EEPROM_PROGRAMMER_H_ */
