#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK 5
#define COMPUTATIONS 20

int main() {
    int small, x, y, z, j, num, temp, k, count, countk, i, current, divONE, divTWO;
    long curtime;
    count = 0;
    countk = 0;
    for (num = MINNUM; num <= MAXNUM; num++) {
        k = 0;
        temp = num; /* store 'num' as 'temp' so we can print it later as it is */
        while (temp % 2 == 0) {  /* check if 2 is a divisor */
            temp /= 2;
            k++;
            divONE = 2;
        }
        while (temp % 3 == 0) {  /* check if 3 is a divisor */
            temp /= 3;
            k++;
            divONE = 3;
        }
        for (i = 5; i * i <= temp && k < MAXK; i += 6) {  /* check for prime divisors */
            while (temp % i == 0) {
                temp /= i;
                k++;
                divONE = i;
            }
            while (temp % (i + 2) == 0) {
                temp /= i + 2;
                k++;
                divONE = i + 2;
            }
        }
        if (temp > 1) {  /* if 'temp' is greater than 1 , variable 'k' increase by 1 because the number that left is prime */
            k++;
        }
        if (k >= 2 && k <= MAXK) {  /* check if the number is k-almost for k >=2 and k <= MAXK */
            countk++;
        }
        if (k == 2) {  /* check if the number is semiprime */
            count++;
            if (divONE * divONE != num) {
                divTWO = num / divONE;  /* store the second divisor of the interesting number */
                if (divTWO < divONE) {  /* if the second divisor is smaller than the first, swap them */
                    small = divTWO;
                    divTWO = divONE;
                    divONE = small;
                }
                if (divTWO - divONE <= 0.01 * divTWO ) { /* check if the substraction of the two divisors is 1% or less of the biggest divisor to make sure that is an interesting number */
                    printf("%d * %d = %d is an interesting semiprime\n", divONE, divTWO, num);
                }
            }
        }
    }
    printf("\nFound %d k-almost prime numbers (2 <= k <= %d)\nFound %d semiprimes\n",countk, MAXK, count );
    curtime = time(NULL);  /* current time */
    srand((unsigned int) curtime);  /* initialize random number generator */
    printf("\nCurrent time is %ld\n\n", curtime);
    printf("Checking %d random numbers\n\n", COMPUTATIONS);
    for (j = 0; j < COMPUTATIONS; j++) {
        y = rand();  /* first random number */
        z = rand();  /* second random number */
        k = 0;
        x = ((y % 32768) + 1) * ((z % 32768) + 1) + 1;  /* the "formula" to find the number we need */
        current = x; /* store 'current' as 'x' so we can print it later as it is */
        for (i = 2; i * i <= current; i++) {
            while (current % i == 0) {  /* check for prime divisors */
                current /= i;
                k++;
            }
        }
        if (current > 1) {  /* if 'current' is greater than 1 , variable 'k' increase by 1 because the number that left is prime */
            k++;
        }
        printf("%10d is a %d-almost prime number\n", x, k);
    }
}
