#include <stdlib.h>
#include <stdio.h>

/*
 * This program prints out the semiprimes between two positive
 * integers, a and b inclusive. It first asks for user input for
 * the two numbers, checks if positive and if the first number
 * is less than the second, and then computes the semi primes.
 * is_prime determines if a number of prime by iterating from 2
 * to number - 1 and checking for remainders when you divide the
 * number by i. print_semiprimes determines if semiprimes exist
 * by using a counter to count the number of times something is
 * printed and returns accordingly. The function implements the
 * formula given in the MP assignment.
 *
 * partner: pranay2
 * */

/* declare functions before hand */
int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
    int a, b;
    printf("Input two numbers: "); // get user input
    scanf("%d %d", &a, &b);
    if( a <= 0 || b <= 0  ){ // check for positive integers
        printf("Inputs should be positive integers\n");
        return 1;
    }

    if( a > b  ){ // check for a > b
        printf("The first number should be smaller than or equal to the second number\n");
        return 1;
    }

    // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
     print_semiprimes(a,b); //print out semiprimes
       
}

/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number) {
    for (int i = 2; i < number; i++) { //iterate from 2 to n-1
        if (number % i == 0) { // if no remainder when dividing, then not prime
            return 0;
        }
    }
    return 1;
}

/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b) {
    int count = 0; // counter for number of times printed
    for (int n = a; n <= b; n++) { //follows formula given in MP4 spec
        for (int k = 2; k <= n-1; k++) {
            if (is_prime(k) == 1 &&  n%k == 0 && is_prime(n/k) == 1) {
                printf("%d ", n);
                ++count; // increment counter
                break; // go to next loop once printed
            }
        }
    }
    if (count > 0) return 1; //return 1 if printed more than once
    else return 0;
}
