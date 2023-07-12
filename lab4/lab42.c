#include <stdio.h>
int main() {  
  printf("size of a char is %lu byte\n", sizeof(char));
  printf("size of a unsigned char is %lu byte\n", sizeof(unsigned char));
  printf("size of a short is %lu bytes\n", sizeof(short));  
  printf("size of a int is %lu bytes\n", sizeof(int));  
  printf("size of a long is %lu bytes\n", sizeof(long));  
  printf("size of a unsigned long is %lu bytes\n", sizeof(unsigned long));
  printf("size of a float is %lu bytes\n", sizeof(float));
  printf("size of a double is %lu bytes\n", sizeof(double));
  printf("size of a long double is %lu bytes\n", sizeof(long double));
}