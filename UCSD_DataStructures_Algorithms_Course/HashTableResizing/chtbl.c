	/*
 * chtbl.c
 */
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "chtbl.h"
#include "math.h"
 #include "stdio.h"

int chtbl_init(CHTbl *htbl, int buckets, double maxLoadFactor, double resizeMultiplier, int(*h)(const void *key), int(*match)(const void *key1, const void *key2), void(*destroy)(void *data)){
    int i;

    /* Allocate space for the hash table. */
    if ((htbl->table = (List *) malloc(buckets * sizeof(List))) == NULL)
        return -1;

    /* Initialize the buckets. */
    htbl->buckets = buckets;

    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Encapsulate the functions. */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->maxLoadFactor = maxLoadFactor;
    htbl->resizeMultiplier =  resizeMultiplier;

    /* Initialize the number of elements in the table. */
    htbl->size = 0;

    return 0;
}

void chtbl_destroy(CHTbl *htbl) {

    int i;

    /* Destroy each bucket. */
    for (i = 0; i < htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    /* Free the storage allocated for the hash table. */
    free(htbl->table);

    /* No operations are allowed now, but clear the structure as a
     * precaution. */
    memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl **htbl, const void *data, int newElementFlag){
    void *temp;
    int bucket, retval;
    double loadFactor; 
    int newBuckets;
    int oldBuckets;
    ListElmt *element, *prev;
    int i;

    /* Do nothing if the data is already in the table. */
    temp = (void *) data;

    if (chtbl_lookup(*htbl, &temp) == 0){
        return 1;
    }
        
   
    /*Compute load factor in advance for new element to be inserted */
    loadFactor = (double)((*htbl)->size+1)/(double)(*htbl)->buckets;
    /*If load factor > maxLoadFactor, compute new bucket size, init new hash table
    and repopulate it*/
    if(loadFactor >= (*htbl)->maxLoadFactor){
        CHTbl* newHashTable;
    	oldBuckets = (*htbl)->buckets;
    	/*Create a new hashtable*/
		if((newHashTable = (CHTbl*) malloc(sizeof(CHTbl))) == NULL){
            printf("Malloc failed\n");
        }
        /*Compute new bucket size and initialize the new hashtable with updated bucket size*/
		newBuckets = oldBuckets * (*htbl)->resizeMultiplier;
		chtbl_init(newHashTable, newBuckets, (*htbl)->maxLoadFactor,(*htbl)->resizeMultiplier, (*htbl)->h,(*htbl)->match,(*htbl)->destroy);
		/*Loop through each bucket (i.e. each linked list) of old hash table*/
		for(i=0;i<oldBuckets;i++){
			prev = NULL;
			/*Retrieve all elements of a bucket, rehash it and place it in new hashtable*/
			for (element = list_head(&(*htbl)->table[i]); element != NULL; element= list_next(element)){
				 /* Extract data into temp and remove the element from the current linked list */
        		if (list_rem_next(&(*htbl)->table[i], prev, &temp) != 0) {
            		return -1;
        		}
	            prev = element;
	            /*insert the extracted element into new hash table. Since 
                it's an old element, we set the last parameter to zero*/
	            chtbl_insert(&newHashTable, temp,0);
			}
            /*destroy the old list*/
            list_destroy( &(*htbl)->table[i] );
		}
        /*Point to the new hashtable now*/
       *htbl = newHashTable;    
    }
     
    /*Hash the key using division method*/
    bucket = floor(fmod((*htbl)->h(data)*0.618,1.0) * (*htbl)->buckets);

    /* Insert the data into the bucket. */
    if ((retval = list_ins_next(&(*htbl)->table[bucket], NULL, data)) == 0){
    	 (*htbl)->size++;
         /*Compute actual load factor*/
         loadFactor = (double)((*htbl)->size)/(double)(*htbl)->buckets;
    	 if(newElementFlag){
            newElementFlag = 0;
    	 	printf("buckets %2d, elements %2d, lf %2g, max lf %2g, resize multiplier %2g\n",
			(*htbl)->buckets,(*htbl)->size,loadFactor,(*htbl)->maxLoadFactor,(*htbl)->resizeMultiplier);
    	 }
    }
    return retval;
}



int chtbl_remove(CHTbl *htbl, void **data) {

    ListElmt *element, *prev;
    int bucket;

    /*Hash the key using divison method */
    bucket = floor(fmod((htbl)->h(*data)*0.618,1.0) * (htbl)->buckets);

    /* Search for the data in the bucket. */
    prev = NULL;

    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {
        if (htbl->match(*data, list_data(element))) {
            /* Remove the data from the bucket. */
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            }
            else {
                return -1;
            }
        }
        prev = element;
    }

    /* Return that the data was not found. */
    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {

    ListElmt *element;
    int bucket;

    /*Hash the key using division method*/
    bucket = floor(fmod((htbl)->h(*data)*0.618,1.0) * (htbl)->buckets);

    /* Search for the data in the bucket. */
    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {
            /* Pass back the data from the table. */
            *data = list_data(element);
            return 0;
        }
    }
    /* Return that the data was not found. */
    return -1;
}