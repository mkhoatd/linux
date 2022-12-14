// Chương trình ghi ngẫu nhiên một số lên file ánh xạ bộ nhớ

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0X100

int random_range (unsigned const low, unsigned const high) { 
  unsigned const range = high - low + 1;
  return low + (int) (((double)range) * rand() /(RAND_MAX + 1.0)); 
}

int main(int argc, char* const argv[]) {
  int fd;
  void* file_memory;
  /* Khoi tao bo so ngau nhien */
  srand (time (NULL));
  /* Chuan bi mot file du lon de chua so nguyen unsigned */
  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  lseek(fd, FILE_LENGTH+1, SEEK_SET);
  write(fd,"",1);
  lseek(fd, 0, SEEK_SET);
  /* Tao bo nho anh xa */
  file_memory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd,0);
  close(fd);
  /* Ghi so nguyen random len vung bo nho anh xa*/
  sprintf((char*) file_memory,"%d\n", random_range(-100,100));
  /* Go bo bo nho */
  munmap(file_memory, FILE_LENGTH);
  return 0;
} 

// run
// gcc mapped_memory_write.c -o mapped_memory_write 
// ./mapped_memory_write ./test.txt  