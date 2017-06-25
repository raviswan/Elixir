/******************************************************************************
 * CSE-40049 - Homework #3
 *
 * Author:      Ray Mitchell
 * Date:        4/20/2011
 * System:      Intel Core 2 Duo T9300 @ 2.50 GHz
 *              4.00 GB RAM
 *              64-bit Windows 7 Ultimate
 *
 * Program Description:  Uses quicksort to sort and display an array of
 *              cars by make then model, by descending MPG, and by
 *              make then descending MPG.
 *
 * Program Output:
                Outputting cars in original unsorted order
                        Make   Model MPG
                        ----   ----- ---
                      Toyota   Camry  33
                        Ford   Focus  40
                       Honda  Accord  34
                        Ford Mustang  31
                       Honda   Civic  39
                      Toyota   Prius  48
                       Honda     Fit  35
                      Toyota Corolla  35
                        Ford  Taurus  28

                Outputting cars sorted by make then model
                        Make   Model MPG
                        ----   ----- ---
                        Ford   Focus  40
                        Ford Mustang  31
                        Ford  Taurus  28
                       Honda  Accord  34
                       Honda   Civic  39
                       Honda     Fit  35
                      Toyota   Camry  33
                      Toyota Corolla  35
                      Toyota   Prius  48

                Outputting cars sorted by descending MPG
                        Make   Model MPG
                        ----   ----- ---
                      Toyota   Prius  48
                        Ford   Focus  40
                       Honda   Civic  39
                      Toyota Corolla  35
                       Honda     Fit  35
                       Honda  Accord  34
                      Toyota   Camry  33
                        Ford Mustang  31
                        Ford  Taurus  28

                Outputting cars sorted by make then descending MPG
                        Make   Model MPG
                        ----   ----- ---
                        Ford   Focus  40
                        Ford Mustang  31
                        Ford  Taurus  28
                       Honda   Civic  39
                       Honda     Fit  35
                       Honda  Accord  34
                      Toyota   Prius  48
                      Toyota Corolla  35
                      Toyota   Camry  33
 *****************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define MAX_STRING_LENGTH 64

typedef struct Car_ {
    char make[MAX_STRING_LENGTH];
    char model[MAX_STRING_LENGTH];
    int mpg;                        /* Miles per gallon */
} Car;

/* Prototypes */
int compareCarsByMakeThenModel(const void *pData1, const void *pData2);
int compareCarsByDescendingMPG(const void *pData1, const void *pData2);
int compareCarsByMakeThenDescendingMPG(const void *pData1, const void *pData2);
void outputCars(Car cars[], int numCars);

int main() {
    Car cars[] = {
        { "Toyota", "Camry", 33 },
        { "Ford", "Focus", 40 },
        { "Honda", "Accord", 34 },
        { "Ford", "Mustang", 31 },
        { "Honda", "Civic", 39 },
        { "Toyota", "Prius", 48 },
        { "Honda", "Fit", 35 },
        { "Toyota", "Corolla", 35 },
        { "Ford", "Taurus", 28 }
    };
    int numCars = sizeof(cars) / sizeof(cars[0]);

    /* Output cars in original unsorted order */
    printf("Outputting cars in original unsorted order\n");
    outputCars(cars, numCars);

    /* Output cars sorted by make then model */
    printf("\nOutputting cars sorted by make then model\n");
    qksort(cars, numCars, sizeof(Car),
        0, numCars - 1, compareCarsByMakeThenModel);
    outputCars(cars, numCars);

    /* Output cars sorted by descending MPG */
    printf("\nOutputting cars sorted by descending MPG\n");
    qksort(cars, numCars, sizeof(Car),
        0, numCars - 1, compareCarsByDescendingMPG);
    outputCars(cars, numCars);

    /* Output cars sorted by make then descending MPG */
    printf("\nOutputting cars sorted by make then descending MPG\n");
    qksort(cars, numCars, sizeof(Car),
        0, numCars - 1, compareCarsByMakeThenDescendingMPG);
    outputCars(cars, numCars);

    getchar();

    return EXIT_SUCCESS;
}

int compareCarsByMakeThenModel(const void *pData1, const void *pData2) {
    const Car *pCar1 = (Car *)pData1;
    const Car *pCar2 = (Car *)pData2;
    int result;

    if ((result = strcmp(pCar1->make, pCar2->make)) == 0)
        result = strcmp(pCar1->model, pCar2->model);

    return result;
}

int compareCarsByDescendingMPG(const void *pData1, const void *pData2) {
    const Car *pCar1 = (Car *)pData1;
    const Car *pCar2 = (Car *)pData2;
    int result;

    if (pCar1->mpg > pCar2->mpg)
        result = -1;
    else if (pCar1->mpg < pCar2->mpg)
        result = 1;
    else
        result = 0;

    return result;
}

int compareCarsByMakeThenDescendingMPG(const void *pData1,
        const void *pData2) {
    const Car *pCar1 = (Car *)pData1;
    const Car *pCar2 = (Car *)pData2;
    int result;

    if ((result = strcmp(pCar1->make, pCar2->make)) == 0)
        if (pCar1->mpg > pCar2->mpg)
            result = -1;
        else if (pCar1->mpg < pCar2->mpg)
            result = 1;
        else
            result = 0;

    return result;
}

void outputCars(Car cars[], int numCars) {
    int i;
    printf("%12s%8s%4s\n", "Make", "Model", "MPG");
    printf("%12s%8s%4s\n", "----", "-----", "---");
    for (i = 0; i < numCars; ++i) {
        printf("%12s%8s%4d\n", cars[i].make, cars[i].model, cars[i].mpg);
    }
}
