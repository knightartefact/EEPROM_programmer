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
#include "file_conversion.h"
#include <errno.h>

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

int get_file_size(FILE *file)
{
    int size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char *read_full_data(port_io_t *port_io)
{
    int address = 0;
    char command[256];
    char *buffer = malloc(sizeof(char) * 65537);
    char *buf_chunk;

    while (address < MAX_ADDR) {
        if (address % 1024 == 0 && address != 0)
            putchar('.');
        sprintf(command, "R%04X\n", address);
        send_byte_string(command, port_io->port_stream);
        buf_chunk = read_byte_stream(port_io->port_stream);
        strcat(buffer, buf_chunk);
        free(buf_chunk);
        wait_for_instruction(port_io->port_stream, "OK");
        usleep(100);
        address += READ_SIZE;
    }
    putchar('\n');
    return buffer;
}

int write_full_data(port_io_t *port_io, char *file_data)
{
    int address = 0;
    char command[512];
    int file_index = 0;

    while (address < MAX_ADDR) {
        if (address % 1024 == 0 && address != 0)
            putchar('.');
        sprintf(command, "P40%04X%.128s\n", address, file_data + file_index);
        send_byte_string(command, port_io->port_stream);
        wait_for_instruction(port_io->port_stream, "OK");
        address += PAGE_SIZE;
        file_index += (PAGE_SIZE * 2);
    }
    putchar('\n');
    return 0;
}

int handle_command(port_io_t *port_io)
{
    if (port_io->options.command == READ_EEPROM) {
        bin_array_t *array;
        dprintf(STDOUT_FILENO ,"Reading data from EEPROM");
        array = hex_to_bin(read_full_data(port_io));
        int fd = open(port_io->options.output_filename, O_CREAT | O_WRONLY, 0666);
        write(fd, array->data, array->size);
        free(array->data);
        free(array);
        close(fd);
        return 0;
    }
    if (port_io->options.command == WRITE_EEPROM) {
        FILE *file = fopen(port_io->options.input_filename, "r");
        bin_array_t *array = malloc(sizeof(bin_array_t));
        char *file_data;

        array->data = malloc(sizeof(char) * get_file_size(file));
        array->size = get_file_size(file);
        fread(array->data, sizeof(char), get_file_size(file), file);
        fclose(file);
        file_data = bin_to_hex(array);
        dprintf(STDOUT_FILENO ,"Writing data to EEPROM");
        write_full_data(port_io, bin_to_hex(array));
        return 0;
    }
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
    port_io.options = options;
    set_interface_attribs(port_io.port_fd, options.baudrate);
    establish_connection(&port_io);
    sleep(1);
    handle_command(&port_io);
    close_port(&port_io);
    return 0;
}

int main(int ac, char **av)
{
    return (start_programmer(ac, av));
}
