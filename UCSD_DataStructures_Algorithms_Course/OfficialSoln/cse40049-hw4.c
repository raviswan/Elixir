/******************************************************************************
 * CSE-40049 - Homework #4
 *
 * Author:      Ray Mitchell
 * Date:        4/27/2011
 * System:      Intel Core 2 Duo T9300 @ 2.50 GHz
 *              4.00 GB RAM
 *              64-bit Windows 7 Ultimate
 *
 * Program Description:  Uses stacks to add large numbers (i.e. numbers
 *              larger than can be represented by a long).
 *
 * Program Output:
        592 + 3784 = 4376
        12345678901234567890 + 98765432109876543210 = 111111111011111111100
        276869234260001238 + 1261724690823412450112 = 1262001560057672451350
        10161020340611234122 + 16723496149608101235 = 26884516490219335357
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stack.h"

void fatalError(const char *pMessage);
void pushNumeralsOntoStack(Stack *pStack, const char *pNum);
int getNextDigitFromStack(Stack *pStack);
void addLargeNumbers(const char *pNum1, const char *pNum2);

int main() {
    addLargeNumbers("592", "3784");
    addLargeNumbers("12345678901234567890", "98765432109876543210");
    addLargeNumbers("276869234260001238", "1261724690823412450112");
    addLargeNumbers("10161020340611234122", "16723496149608101235");

    return EXIT_SUCCESS;
}

void addLargeNumbers(const char *pNum1, const char *pNum2) {
    Stack num1Stack;
    Stack num2Stack;
    Stack resultStack;
    int calc = 0;
    void *pVoidData;
    char *pCharData;

    /* Output the two numbers */
    printf("%s + %s = ", pNum1, pNum2);

    /* Initialize the stacks */
    stack_init(&num1Stack, NULL);
    stack_init(&num2Stack, NULL);
    stack_init(&resultStack, free);

    /* Push numerals from two numbers onto stacks */
    pushNumeralsOntoStack(&num1Stack, pNum1);
    pushNumeralsOntoStack(&num2Stack, pNum2);

    /* As long as numerals remain to be summed */
    while (stack_peek(&num1Stack) || stack_peek(&num2Stack)) {
        /* Add the next numeral from each stack to calculation */
        calc += getNextDigitFromStack(&num1Stack);
        calc += getNextDigitFromStack(&num2Stack);

        /* Push one's place onto result stack */
        if ((pCharData = (char *) malloc(sizeof(char))) == NULL) {
            fatalError("Out of memory");
        }
        *pCharData = (char) (calc % 10 + '0');
        if (stack_push(&resultStack, pCharData) != 0) {
            fatalError("Error pushing onto stack");
        }

        /* Remove one's place from calculation */
        calc /= 10;
    }

    /* If carry left on calc, push carry onto result stack */
    if (calc != 0) {
        if ((pCharData = (char *) malloc(sizeof(char))) == NULL) {
            fatalError("Out of memory");
        }
        *pCharData = '1';
        if (stack_push(&resultStack, pCharData) != 0) {
            fatalError("Error pushing onto stack");
        }
    }

    /* Display numerals in result */
    while (stack_peek(&resultStack)) {
        /* Pop numeral from result stack */
        stack_pop(&resultStack, &pVoidData);
        pCharData = (char *) pVoidData;

        /* Display numeral */
        printf("%c", pCharData[0]);

        /* Free numeral's memory */
        free(pCharData);
    }
    printf("\n");

    /* Destroy the stacks */
    stack_destroy(&num1Stack);
    stack_destroy(&num2Stack);
    stack_destroy(&resultStack);
}

void fatalError(const char *pMessage) {
    fprintf(stderr, pMessage);
    exit(EXIT_FAILURE);
}

void pushNumeralsOntoStack(Stack *pStack, const char *pNum) {
    /* Push numerals in most-signifcant order onto stack */
    while (*pNum != '\0') {
        if (stack_push(pStack, pNum) != 0) {
            fatalError("Error pushing onto stack");
        }
        ++pNum;
    }
}

int getNextDigitFromStack(Stack *pStack) {
    int value = 0;
    void *pVoidData;
    char *pCharData;

    if (stack_peek(pStack)) {
        /* Pop digit from stack */
        stack_pop(pStack, &pVoidData);
        pCharData = (char *) pVoidData;

        /* Convert digit to int */
        value = *pCharData - '0';

        /* Free the memory of the digit if necessary */
        if (pStack->destroy != NULL) {
            pStack->destroy(pCharData);
        }
    }

    return value;
}

