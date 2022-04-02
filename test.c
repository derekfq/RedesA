#include<stdio.h>
#include<time.h>

void main()
{
    time_t t;
    time(&t);
    printf("\nTimestamp: %s\n",ctime(&t));
}