/******************************************************************************
 * CSE-40049 - Homework #2
 *
 * Author:      Ray Mitchell
 * Date:        10/11/2010
 * System:      Intel Core 2 Duo T9300 @ 2.50 GHz
 *              4.00 GB RAM
 *              64-bit Windows 7 Ultimate
 *
 * Program Description:  Uses a linked list to represent, display, and evaluate
 *              polynomials.
 *
 * Program Output:
        x + 1 = 2 when x = 1
        x^2 - 1 = 3.1209 when x = 2.03
        -3x^3 + 0.5x^2 - 2x = -372.5 when x = 5
        -0.3125x^4 - 9.915x^2 - 7.75x - 40 = -72731671.69 when x = 123.45
 *****************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
 * Append (insert at the end) constant to pPolynomial.
 */
void appendTerm(List *pPolynomial, double constant) {
    double *pConstant;

    /* Allocate constant to be appended to list */
    if (!(pConstant = (double *)malloc(sizeof(double)))) {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    *pConstant = constant;

    /* Append constant to the list */
    if (list_ins_next(pPolynomial, list_tail(pPolynomial), pConstant) != 0) {
        fprintf(stderr, "Error occurred inserting value into linked list");
        exit(EXIT_FAILURE);
    }
}

/*
 * Output the polynomial to stdout using proper formatting.
 */
void display(List *pPolynomial) {
    ListElmt *pTerm;
    int power;
    double constant;
    int wasFirstTermDisplayed = 0;

    /* For each term */
    for (pTerm = list_head(pPolynomial), power = list_size(pPolynomial) - 1;
            pTerm != NULL;
            pTerm = list_next(pTerm), --power) {
        /* Get term's constant */
        constant = *((double *)list_data(pTerm));
        if (constant == 0.0) {
            continue;
        }

        /* Output sign */
        if (!wasFirstTermDisplayed) {           /* First term */
            if (constant < 0) {
                printf("-");
            }
        }
        else {                                  /* Not first term */
            if (constant < 0) {
                printf(" - ");
            }
            else {
                printf(" + ");
            }
        }

        /* Output absolute value of constant */
        constant = fabs(constant);
        if (constant != 1.0 || power == 0) {
            printf("%.10g", constant);
        }

        /* Output power */
        switch(power) {
        case 0:
            break;
        case 1:
            printf("x");
            break;
        default:
            printf("x^%d", power);
            break;
        }

        wasFirstTermDisplayed = 1;
    }
}

/*
 * Evaluate the polynomial for the given value of x and return the result.
 */
double evaluate(List *pPolynomial, double x) {
    ListElmt *pTerm;
    int power;
    double constant;
    double value = 0.0;

    /* For each term */
    for (pTerm = list_head(pPolynomial), power = list_size(pPolynomial) - 1;
            pTerm != NULL;
            pTerm = list_next(pTerm), --power) {
        /* Get term's constant */
        constant = *((double *)list_data(pTerm));
        if (constant == 0.0) {
            continue;
        }

        /* Compute term's value and add to overall value */
        value += constant * pow(x, power);
    }

    return value;
}

int main() {
    List polynomial;
    double x;

    /* Test x + 1.0, with x = 1.0 */
    x = 1.0;
    list_init(&polynomial, free);
    appendTerm(&polynomial,   1.0);      /*   1.0    * x^1 */
    appendTerm(&polynomial,   1.0);      /*   1.0    * x^0 */
    display(&polynomial);
    printf(" = %.10g when x = %.10g\n", evaluate(&polynomial, x), x);
    list_destroy(&polynomial);

    /* Test x^2 - 1.0, with x = 2.03 */
    x = 2.03;
    list_init(&polynomial, free);
    appendTerm(&polynomial,   1.0);      /*   1.0    * x^2 */
    appendTerm(&polynomial,   0.0);      /*   0.0    * x^1 */
    appendTerm(&polynomial,  -1.0);      /*  -1.0    * x^0 */
    display(&polynomial);
    printf(" = %.10g when x = %.10g\n", evaluate(&polynomial, x), x);
    list_destroy(&polynomial);

    /* Test -3.0x^3 + 0.5x^2 - 2.0x, with x = 5.0 */
    x = 5.0;
    list_init(&polynomial, free);
    appendTerm(&polynomial,  -3.0);      /*  -3.0    * x^3 */
    appendTerm(&polynomial,   0.5);      /*   0.5    * x^2 */
    appendTerm(&polynomial,  -2.0);      /*  -2.0    * x^1 */
    appendTerm(&polynomial,   0.0);      /*   0.0    * x^0 */
    display(&polynomial);
    printf(" = %.10g when x = %.10g\n", evaluate(&polynomial, x), x);
    list_destroy(&polynomial);

    /* Test -0.3125x^4 - 9.915x^2 - 7.75x - 40.0, with x = 123.45 */
    x = 123.45;
    list_init(&polynomial, free);
    appendTerm(&polynomial,  -0.3125);   /*  -0.3125 * x^4 */
    appendTerm(&polynomial,   0.0);      /*  -0.0    * x^3 */
    appendTerm(&polynomial,  -9.915);    /*  -9.915  * x^2 */
    appendTerm(&polynomial,  -7.75);     /*  -7.75   * x^1 */
    appendTerm(&polynomial, -40.0);      /* -40.0    * x^0 */
    display(&polynomial);
    printf(" = %.10g when x = %.10g\n", evaluate(&polynomial, x), x);
    list_destroy(&polynomial);

    return EXIT_SUCCESS;
}
