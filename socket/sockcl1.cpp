#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <string>
#include <thread>
#include <chrono>

void write_text(int socket_fd, const char *text)
{
    /* Ghi so byte cua string, bao gom gia tri ket thuc NUL */ 
    int length = strlen(text);
    write(socket_fd, &length, sizeof(length));
    /* Ghi chuoi */
    write(socket_fd, text, length);
}

char * read_text(int socket_fd) {
    int length;
    char *text;
    if (read(socket_fd, &length, sizeof(length)) == 0)
    {
        return "";
    }
    text = (char *)malloc(length);
    read(socket_fd, text, length);
    return text;
}

bool isArmstrongNumber(int num)
{
    // Calculate the number of digits in the given number
    int digits = 0;
    int temp = num;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    // Calculate the sum of the cubes of the digits of the given number
    int sum = 0;
    temp = num;
    while (temp > 0)
    {
        // Extract the last digit of the number
        int digit = temp % 10;
        // Add the cube of the digit to the sum
        sum += pow(digit, digits);
        // Remove the last digit from the number
        temp /= 10;
    }

    // Return true if the sum of the cubes of the digits is equal to the number itself
    return sum == num;
}


struct socket_info {
    int socket_fd;
    const char* socket_name;
    sockaddr_un name;
};

socket_info init_socket(const char* socket_name) {
    socket_info skinfo;
    skinfo.socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    strcpy(skinfo.name.sun_path, socket_name);
    skinfo.socket_name = socket_name;
    skinfo.name.sun_family = AF_LOCAL;
    return skinfo;
}

int accept_connection(int socket_fd) {
    struct sockaddr_un client_name;
    socklen_t client_name_len;
    int client_socket_fd;
    /* Chap nhan ket noi */
    client_socket_fd = accept(socket_fd, (sockaddr *)&client_name, &client_name_len); 
    return client_socket_fd;
}

int handle_client(int client_socket_fd) {
    while (1)
    {
        int length;
        char *text;
        /* Doc do dai cua doan text tu socket. Neu ham read tra ve gia tri 0, client dong ket noi*/
        text = read_text(client_socket_fd);
        // cast char * to int
        int num = atoi(text);
        bool res = isArmstrongNumber(num);
        const char *message;
        if (res == 1) {
            std::string str_message = "So " + std::to_string(num) + " la so Amstrong";
            message = str_message.c_str();
        }
        else {
            std::string str_message = "So " + std::to_string(num) + " khong phai la so Amstrong";
            message = str_message.c_str();
        }
        write_text(client_socket_fd, message);
        // Giai phong vung dem
        free(text);
        return 1;
    }
}

void gioithieu() {
    using namespace std;
    const char* output=
        "***************************************************\n"
        "* Bai thi ket thuc mon: Lap trinh tren Linux      *\n"
        "* Ho va ten: Tran Dinh Minh Khoa                  *\n"
        "* Nhom: 20.11                                     *\n"
        "* Masv: 102200265                                 *\n"
        "* De so:                                          *\n"
        "***************************************************\n";
    cout<<output;

}

int server() {
    const char *socket_name = "bt";
    socket_info skinfo_sv = init_socket(socket_name);
    bind(skinfo_sv.socket_fd, (sockaddr *)&skinfo_sv.name, SUN_LEN(&skinfo_sv.name)); /* Lang nghe ket noi*/
    listen(skinfo_sv.socket_fd, 5);
    int quit;
    /* Lap lai chap nhan ket noi, xoay quanh server lien quan den client. Tiep tuc cho den khi client gui message "quit" */
    do
    {
        int client_socket_fd = accept_connection(skinfo_sv.socket_fd);
        /* Dieu khien ket noi */
        quit = handle_client(client_socket_fd);
        /* Dong va ket thuc ket noi */
        close(client_socket_fd);
    } while (!quit);
    /* Xoa file socket */ 
    close(skinfo_sv.socket_fd);
    unlink(skinfo_sv.socket_name);
    return 0;
}


int client() {
    gioithieu();
    socket_info skinfo = init_socket("bt");
    connect(skinfo.socket_fd, (sockaddr *)&skinfo.name, SUN_LEN(&skinfo.name));
    write_text(skinfo.socket_fd, "153");
    const char *rep = read_text(skinfo.socket_fd);
    std::string rep_str = rep;
    std::cout<<rep_str;
    close(skinfo.socket_fd);
    unlink(skinfo.socket_name);
    return 0;
}

int main() {
    int child_pid;
    // child_pid = fork();
    // if (child_pid == 0) server();
    // else client();
    client();
    return 0;
}