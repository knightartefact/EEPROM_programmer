/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** serial_com
*/

#include "port_manager.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include "eeprom_programmer.h"

void wait_for_instruction(FILE *port, char *instruction)
{
    while (strcmp(read_byte_stream(port), instruction));
}

void establish_connection(port_io_t *port_io)
{
    tcflush(port_io->port_fd, TCIOFLUSH);
    printf("Awaiting device\n");
    wait_for_instruction(port_io->port_stream, "START");
    printf("Connection established\n");
}

int start_programmer(int ac, char **av)
{
    options_t options;
    port_io_t port_io;

    init_options(&options);
    get_options(ac, av, &options);
    if (check_options(&options))
        return 1;
    if (open_port(options.port, &port_io))
        return 1;
    set_interface_attribs(port_io.port_fd, options.baudrate);
    establish_connection(&port_io);
    sleep(2);
    close_port(&port_io);
    return 0;
}

int main(int ac, char **av)
{
    return (start_programmer(ac, av));
    // set_interface_attribs(port_fd, 9600);
    // establish_connection(port, port_fd);
    // for (int i = 0; i < 4; i++) {
    //     send_byte_string("P400000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n", port);
    //     wait_for_instruction(port, "OK");
    //     address += 64;
    // }
    // printf("Successfully written data\n");
    // send_byte_string("R0000\n", port);
    // printf("%s\n", read_byte_stream(port));
    // wait_for_instruction(port, "OK");
}
