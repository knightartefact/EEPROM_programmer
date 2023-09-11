/*
** EPITECH PROJECT, 2022
** serial_communication
** File description:
** compare_files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_size(FILE *file)
{
    int size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int main(int ac, char **av)
{
    char *file1 = av[1];
    char *file2  = av[2];
    if (ac != 3) {
        printf("Not enough arguments\n");
        return 1;
    }
    FILE *file1_stream = fopen(file1, "r");
    FILE *file2_stream = fopen(file2, "r");
    char *buffer1, *buffer2;
    int file_size1, file_size2, read1, read2;

    if (!file1_stream || !file2_stream) {
        printf("Couldn't open file\n");
        return 1;
    }
    file_size1 = get_file_size(file1_stream);
    file_size2 = get_file_size(file2_stream);
    buffer1 = malloc(sizeof(char) * (get_file_size(file1_stream) + 1));
    buffer2 = malloc(sizeof(char) * (get_file_size(file2_stream) + 1));
    read1 = fread(buffer1, sizeof(char), get_file_size(file1_stream), file1_stream);
    buffer1[file_size1] = 0;
    read2 = fread(buffer2, sizeof(char), get_file_size(file2_stream), file2_stream);
    buffer2[file_size2] = 0;
    printf("Read %d bytes from file1, and %d bytes from file2\n", file_size1, file_size2);
    printf("last byte value 1 = %02X\nlast byte value 2 = %02X\n", buffer1[32767], buffer2[32767]);
    fclose(file1_stream);
    fclose(file2_stream);
    if ((file_size1 != file_size2) || (read1 != read2)) {
        printf("Files are not the same size\n");
        return 1;
    }
    for (int i = 0; i < file_size1; i++) {
        if (buffer1[i] != buffer2[i]) {
            printf("Files differ at position %d\n", i);
            return 1;
        }
    }
    printf("Files are identical !\n");
    return 0;
}
