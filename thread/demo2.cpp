#include <pthread.h>
#include <stdio.h>
#include <iostream>
struct char_print_parms
{
    char character; // ký tự để in
    int count;      // Số lần in ký tự
};
/* Hàm in số ký tự được cho bởi *PARAMETERS, trỏ đến cấu trúc char_print_parms. */
void *char_print(void *parameters)
{
    /* Cast the cookie pointer to the right type. */
    char_print_parms p = *((char_print_parms *)parameters);
    int i;
    for (i = 0; i < p.count; ++i)
        std::cout<<p.character;
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    char_print_parms thread1_args;
    char_print_parms thread2_args;
    char_print_parms *p1 = (char_print_parms *) malloc(sizeof *p1);
    char_print_parms *p2 = (char_print_parms *) malloc(sizeof *p2);
    /* Tạo luồng 1 để in 30,000 ký tự x */
    thread1_args.character = 'a';
    thread1_args.count = 300;
    *p1 = thread1_args;
    pthread_create(&thread1_id, NULL, &char_print, p1);
    /* Tạo luồng 2 để in 20,000 ký tự o. */
    thread2_args.character = 'b';
    thread2_args.count = 200;
    *p2 = thread2_args;
    pthread_create(&thread2_id, NULL, &char_print, p2);
    return 0;
}