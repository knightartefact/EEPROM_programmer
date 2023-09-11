/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** options
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_
    #include <getopt.h>
    #define READ_EEPROM 1
    #define WRITE_EEPROM 2

static const struct option OPT_FLAGS[] = {
    {"output", required_argument, 0, 'o'},
    {"file", required_argument, 0, 'f'},
    {"baudrate", required_argument, 0, 'b'},
    {"port", required_argument, 0, 'p'},
    {0, 0, 0, 0}
};

typedef struct options_s {
    int baudrate;
    char *port;
    char *input_filename;
    char *output_filename;
    int command;
    int verify;
} options_t;

void get_options(int ac, char **av, options_t *options);
void init_options(options_t *options);
int check_options(options_t *options);

#endif /* !OPTIONS_H_ */
