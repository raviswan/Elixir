#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 128
typedef struct Car_ {
 char make[MAX_STRING_LENGTH];
 char model[MAX_STRING_LENGTH];
 int mpg; /* Miles per gallon */
} Car; 




int compareCarsByMakeThenModel(Car *c1, Car *c2){
	int strcmpResult = strcmp(c1->make,c2->make);
	if (strcmpResult > 0)
		return 1;
	else if (strcmpResult < 0)
		return -1;
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

int compareCarsByDescendingMPG(Car *c1, Car *c2){
	int mpgDiff = c1->mpg - c2->mpg;
	if (mpgDiff < 0)
		return 1;
	else if (mpgDiff > 0)
		return -1;
	else
		return 0;

}
int compareCarsByMakeThenDescendingMPG(Car *c1, Car *c2){
	int strcmpResult = strcmp(c1->make,c2->make);
	if (strcmpResult > 0)
		return 1;
	else if (strcmpResult < 0)
		return -1;
	else{
		int mpgDiff = c1->mpg - c2->mpg;
		if (mpgDiff < 0)
			return 1;
		else if (mpgDiff > 0)
			return -1;
		else
			return 0;
	}
	
}

void displayCars(Car *c,int length){
	printf("MAKE 		MODEL 	 	MPG\n\n");
	for (int i=0 ; i< length ; i++)
		printf("%.*s 		%.*s 	%5d\n",(int)strlen(c[i].make),c[i].make,(int)strlen(c[i].model),c[i].model,c[i].mpg); 
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

	displayCars(cars,9);
	qksort(cars, sizeof(cars), sizeof(Car),0, 9, compareCarsByMakeThenModel);
	displayCars(cars,9);
	return 0;
}