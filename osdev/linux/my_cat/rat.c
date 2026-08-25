#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096 // берём 4KB буфера для чтения

int name_file(int argc, char *argv[]) { // проверяем, что имя файла передано
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    return 0;
}
int open_file(char *filename) { // открываем файл
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        write(STDERR_FILENO, "WARN: no such file or directory\n", 33);
        return -1;
    }
    return fd;
}

int main(int argc, char *argv[]) { // инициализация функций и чтение файла
    if (name_file(argc, argv)) {
        return 1;
    }
    int fd = open_file(argv[1]);
    if (fd < 0) {
        return 1;
    }
    char buffer[BUFFER_SIZE]; // буфер для чтения
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) { // читаем файл в цикле
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);
    return 0;
}
