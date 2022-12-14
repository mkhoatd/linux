#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int spawn(char *program, char **arg_list)
{
    int child_pid = fork();
    if (child_pid != 0)
        return child_pid;
    else
    {
        execvp(program, arg_list);
        fprintf(stderr, "Loi xay ra trong execvpn");
        abort();
    }
}
int main()
{
    char *arg_list[] = {"ls", "-l", "/", NULL};
    spawn("ls", arg_list);
    printf("Ket thuc chuong trinh chinh \n");
    return 0;
}