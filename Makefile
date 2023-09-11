##
## EPITECH PROJECT, 2022
## serial_communication
## File description:
## Makefile
##

SRC	=	src/eeprom_programmer.c\
		src/port_manager.c\
		src/options.c\
		src/file_conversion.c\

OBJ	=	$(SRC:.c=.o)

NAME	=	eeprogrammer

CPPFLAGS	=	-Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re fclean clean
