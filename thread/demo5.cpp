#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <array>
/*Hàm tính toán trả về số nguyên tố thứ n, n là là giá trị được trỏ bởi *arg. */
void *compute(void *arg)
{
    int pri = 2;
    int n = *((int *)arg);
    while (1)
    {
        int i;
        int nguyento = 1;
        for (i = 2; i < pri; ++i)
            if (pri % i == 0)
            {
                nguyento = 0;
                break;
            }
        if (nguyento)
        {
            if (--n == 0) return (void*)pri;
        }
        ++pri;
    }
    return NULL;
}

int main()
{
    const int n_pt = 10;
    pthread_t thread;
    int n_cpy1 = n_pt;
    int prime;
    std::array<std::string, n_pt> arr;
    int n_cpy2 = n_pt;
    /* Bắt đầu luồng tính toán số nguyên tố thứ n. */
    pthread_create(&thread, NULL, &compute, &n_cpy1);
    /* Thực hiện vài việc ở đây... */
    /* Chờ luồng tính số nguyên tố hoàn thành, và lấy kết quả trả về.*/
    pthread_join(thread,  (void**) &prime); /* In ra số nguyên tố thứ n. */
    printf("So nguyen to thu %d la %d.\n", n_cpy1, prime);
    return 0;
}