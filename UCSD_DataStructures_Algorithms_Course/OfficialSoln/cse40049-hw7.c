/******************************************************************************
 * CSE-40049 - Homework #7
 *
 * File:        cse40049-hw7.c
 * Author:      Ray Mitchell
 * Date:        5/17/2011
 * System:      Intel Core 2 Duo T9300 @ 2.50 GHz
 *              4.00 GB RAM
 *              64-bit Windows 7 Ultimate
 *
 * Program Description:  Output contents of array in various sort
 *              orders using a Heap.
 *
 * Program Output:
                People sorted by ascending name:
                        Name: Brian, Age: 40, Height: 73.000000
                        Name: Jill, Age: 28, Height: 68.000000
                        Name: Joe, Age: 23, Height: 70.750000
                        Name: Mike, Age: 25, Height: 70.000000
                        Name: Ray, Age: 37, Height: 76.250000
                People sorted by ascending age:
                        Name: Joe, Age: 23, Height: 70.750000
                        Name: Mike, Age: 25, Height: 70.000000
                        Name: Jill, Age: 28, Height: 68.000000
                        Name: Ray, Age: 37, Height: 76.250000
                        Name: Brian, Age: 40, Height: 73.000000
                People sorted by ascending height:
                        Name: Jill, Age: 28, Height: 68.000000
                        Name: Mike, Age: 25, Height: 70.000000
                        Name: Joe, Age: 23, Height: 70.750000
                        Name: Brian, Age: 40, Height: 73.000000
                        Name: Ray, Age: 37, Height: 76.250000
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

typedef struct Person_
{
    const char *name;
    int age;
    double height;
} Person;

void fatalError(const char *pMessage)
{
    fprintf(stderr, pMessage);
    exit(EXIT_FAILURE);
}

int comparePersonsByDescendingName(const void *pKey1, const void *pKey2)
{
    const Person *pPerson1 = (Person *)pKey1;
    const Person *pPerson2 = (Person *)pKey2;
    
    int strcmpResult = strcmp(pPerson1->name, pPerson2->name);
    if (strcmpResult < 0)
        return 1;
    if (strcmpResult > 0)
        return -1;
    return 0;
}

int comparePersonsByDescendingAge(const void *pKey1, const void *pKey2)
{
    const Person *pPerson1 = (Person *)pKey1;
    const Person *pPerson2 = (Person *)pKey2;

    if (pPerson1->age < pPerson2->age)
        return 1;
    if (pPerson1->age > pPerson2->age)
        return -1;
    return 0;
}

int comparePersonsByDescendingHeight(const void *pKey1, const void *pKey2)
{
    const Person *pPerson1 = (Person *)pKey1;
    const Person *pPerson2 = (Person *)pKey2;

    if (pPerson1->height < pPerson2->height)
        return 1;
    if (pPerson1->height > pPerson2->height)
        return -1;
    return 0;
}

void outputPerson(const Person *pPerson)
{
    printf("\tName: %s, Age: %d, Height: %f\n",
        pPerson->name,
        pPerson->age,
        pPerson->height);
}

void outputSorted(const Person people[],
        int numPeople,
        int (* compare)(const void *pKey1, const void *pKey2))
{
    Heap heap;
    void *data;
    int i;

    /* Initialize heap */
    heap_init(&heap, compare, NULL);

    /* Add people to heap */
    for (i = 0; i < numPeople; ++i)
        if (heap_insert(&heap, &people[i]) != 0)
            fatalError("Failed to insert person into heap");

    /* Extract and output people from heap */
    while (heap_size(&heap) > 0) {
        if (heap_extract(&heap, &data) != 0)
            fatalError("Failed to extract person from heap");
        outputPerson((const Person *)data);
    }

    /* Destroy heap */
    heap_destroy(&heap);
}

int main()
{
    /* People in no specific order */
    Person people[] = {
            { "Ray", 37, 76.25 },
            { "Joe", 23, 70.75 },
            { "Jill", 28, 68.00 },
            { "Brian", 40, 73.00 },
            { "Mike", 25, 70.00 }
    };

    /* Output people sorted by ascending name */
    printf("People sorted by ascending name:\n");
    outputSorted(people,
            sizeof(people) / sizeof(*people),
            comparePersonsByDescendingName);

    /* Output people sorted by ascending age */
    printf("People sorted by ascending age:\n");
    outputSorted(people,
            sizeof(people) / sizeof(*people),
            comparePersonsByDescendingAge);

    /* Output people sorted by ascending height */
    printf("People sorted by ascending height:\n");
    outputSorted(people,
            sizeof(people) / sizeof(*people),
            comparePersonsByDescendingHeight);

    return EXIT_SUCCESS;
}
