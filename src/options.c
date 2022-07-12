/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** options
*/

#include "options.h"
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_options(options_t *options)
{
    options->baudrate = -1;
    options->input_filename = NULL;
    options->output_filename = NULL;
    options->port = NULL;
}

void get_options(int ac, char **av, options_t *options)
{
    int option;

    while ((option = getopt_long_only(ac, av, "f:o:b:p:", OPT_FLAGS, NULL)) != -1) {
        switch (option)
        {
        case 'f':
            options->input_filename = strdup(optarg);
            break;
        case 'o':
            options->output_filename = strdup(optarg);
            break;
        case 'p':
            options->port = strdup(optarg);
            break;
        case 'b':
            options->baudrate = atoi(optarg);
        default:
            break;
        }
    }
}

int check_options(options_t *options)
{
    if (options->input_filename && options->output_filename) {
        printf("Cannot read/write at the same time\n");
        return 1;
    }
    if (!options->input_filename && !options->output_filename) {
        printf("Please specify a file to read from / write to\n");
        return 1;
    }
    return 0;
}
