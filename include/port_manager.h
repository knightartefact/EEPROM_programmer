/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** port_manager
*/

#ifndef PORT_MANAGER_H_
    #define PORT_MANAGER_H_
    #include <stdio.h>

typedef struct port_io_s port_io_t;

int open_port(char *port_name, port_io_t *port_io);
void close_port(port_io_t *port_io);
int send_byte_string(char *str, FILE *port);
char *read_byte_stream(FILE *port);
void goto_eol(FILE *port);
int set_interface_attribs(int fd, int speed);

#endif /* !PORT_MANAGER_H_ */
