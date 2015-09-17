/***************************************************************
 *     Adam Lindsey
 *     CIS314 -- Fall 2014
 *     Assignment 5, Problem 4
 *     initial program -- fibonacci.c
 ****************************************************************/
//iterative version of fibonacci sequence nth term generator
//This is the c program that will be the template for question 6

#include <stdio.h>
 
int main(int argc, char* args[]) {
   int n,nth;
   printf("Please enter nth element of sequence you would like: \n");
   scanf("%d", &n);
   nth = fib(n);
   printf("%d\n", nth);
   return 0;
}

int fib(int n) {
   if(n<=0)return 0;
   if(n==1)return 1;
   return fib(n-1)+fib(n-2);
}