/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** port_manager
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include "eeprom_programmer.h"

int open_port(char *port_name, port_io_t *port_io)
{
    int port_fd = open(port_name, O_RDWR | O_NOCTTY);
    FILE *port_stream;

    if (port_fd == -1) {
        printf("Cannot open port %s\n", port_name);
        return 1;
    }
    port_stream = fdopen(port_fd, "w+");
    if (!port_stream) {
        printf("Cannot open port %s from fd\n", port_name);
        return 1;
    }
    port_io->port_fd = port_fd;
    port_io->port_stream = port_stream;
    return 0;
}

void close_port(port_io_t *port_io)
{
    fflush(port_io->port_stream);
    fclose(port_io->port_stream);
    close(port_io->port_fd);
}

int send_byte_string(char *str, FILE *port)
{
    int nb_bytes = strlen(str);
    size_t bytes_written = fwrite(str, sizeof(char), nb_bytes, port);

    if (bytes_written != nb_bytes) {
        printf("Didn't write every character in buffer\n");
        return 1;
    }
    return 0;
}

char *read_byte_stream(FILE *port)
{
    char *buffer = malloc(sizeof(char) * 2048);
    int index = 0;
    int character = 0;

    while (character != '\n') {
        character = fgetc(port);
        buffer[index] = character;
        index++;
    }
    if (buffer[index - 1] == '\n' || buffer[index - 1] == '\r')
        buffer[index - 1] = 0;
    if (buffer[index - 2] == '\r')
        buffer[index - 2] = 0;
    return buffer;
}

void goto_eol(FILE *port)
{
    while (fgetc(port) != '\n');
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }
    cfsetspeed(&tty, (speed_t)speed);
    tty.c_cflag |= (CLOCAL | CREAD);	/* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;		 /* 8-bit characters */
    tty.c_cflag &= ~PARENB;	 /* no parity bit */
    tty.c_cflag &= ~CSTOPB;	 /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;	/* no hardware flowcontrol */
    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}
