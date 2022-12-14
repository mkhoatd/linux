#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Ghi message vào stream với count lần
void writer(const char *message, int count, FILE *stream)
{
    for (; count > 0; --count)
    {
        fprintf(stream, "%s\n", message);
        fflush(stream);
        sleep(1);
    }
}
// Đọc ngẫu nhiên chuỗi từ stream void reader(FILE* stream)
void reader(FILE *stream)
{
    char buffer[1024];
    while (!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL)
        fputs(buffer, stdout);
}

int main()
{
    int fds[2];
    int pid;
    pipe(fds); // Tao pipe
    pid = fork();
    if (pid == 0)
    {
        // Tiến trình con
        FILE *stream;
        // Dong fd viet, k dung
        close(fds[1]);
        stream = fdopen(fds[0], "r");
        reader(stream);
        close(fds[0]);
    }
    else
    {
        // Tiến trình cha
        FILE *stream;
        // Dong fd doc, k dung
        close(fds[0]);
        stream = fdopen(fds[1], "w");
        writer("Hello, hello, hello!!!", 5, stream);
        close(fds[1]);
    }
    return 0;
}