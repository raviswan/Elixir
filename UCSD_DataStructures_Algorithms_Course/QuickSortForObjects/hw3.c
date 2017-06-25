#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512
typedef struct Car_ {
 char make[MAX_STRING_LENGTH];
 char model[MAX_STRING_LENGTH];
 int mpg; /* Miles per gallon */
} Car;


int compareCarsByMakeThenModel(const void *key1, const void *key2){
	Car *c1 = (Car*)key1;
	Car *c2 = (Car*)key2;
	int strcmpResult = strcmp(c1->make,c2->make);
	/*Sort by alphabetical car make*/
	if (strcmpResult > 0)
		return 1;
	else if (strcmpResult < 0)
		return -1;
	/*if the car make is identical, sort by alphabetical car model*/
	else{
		strcmpResult = strcmp(c1->model,c2->model);
		if (strcmpResult > 0)
			return 1;
		else if (strcmpResult < 0)
			return -1;
		else
			return 0;
	}
}

int compareCarsByDescendingMPG(const void *key1,const void *key2){
	Car *c1 = (Car*)key1;
	Car *c2 = (Car*)key2;
	/*sort by descending mpg*/
	if (c1->mpg > c2->mpg)
		return -1;
	else if (c1->mpg < c2->mpg)
		return 1;
	else
		return 0;

}

int compareCarsByMakeThenDescendingMPG(const void *key1, const void *key2){
	Car *c1 = (Car*)key1;
	Car *c2 = (Car*)key2;
	int strcmpResult = strcmp(c1->make,c2->make);
	/*Sort by alphabetical car make*/
	if (strcmpResult > 0)
		return 1;
	else if (strcmpResult < 0)
		return -1;
	else{
		/*if the car make is identical, sort by descending mpg*/
		if (c1->mpg > c2->mpg)
			return -1;
		else if (c1->mpg < c2->mpg)
			return 1;
		else
			return 0;
	}
	
}

void displayCars(Car *c,int length){
	printf("%9.9s 		%9.9s 	%5.5s\n","MAKE","MODEL","MPG");
	printf("---------------------------------------------------\n");
	for (int i=0 ; i< length ; i++)
		//printf("%.*s 		%.*s 	%5d\n",(int)strlen(c[i].make),c[i].make,(int)strlen(c[i].model),c[i].model,c[i].mpg); 
		printf("%10.10s 		%10.10s 	%5d\n",c[i].make,c[i].model,c[i].mpg); 
	return;

}
int main()
{
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
	int start_index = 0;
	int length = sizeof(cars)/sizeof(Car);

	printf("\n--------UNSORTED CAR LIST----------------------\n");
	displayCars(cars,length);

	printf("\n------CARS IN ALPHABETICAL ORDER---------------\n");
	qksort(cars, sizeof(cars), sizeof(Car),start_index, length-1, compareCarsByMakeThenModel);
	displayCars(cars,length);

	printf("\n--------BEST MPG CARS----------------------------\n");
	qksort(cars, sizeof(cars), sizeof(Car),start_index, length-1, compareCarsByDescendingMPG);
	displayCars(cars,length);
	
	printf("\n------BEST MPG CARS IN ALPHABETICAL ORDER------\n");
	qksort(cars, sizeof(cars), sizeof(Car),start_index, length-1, compareCarsByMakeThenDescendingMPG);
	displayCars(cars,length);
	return 0;
}