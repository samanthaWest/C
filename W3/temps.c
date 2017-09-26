/*
Name: Samantha West
Student number: 128111168
Email: swest9@myseneca.ca
Workshop: 3
Section: M
Date: Febuary 3st, 2017
*/

#include <stdio.h>
#define NUMS 4

int main() {

	int i = 0;   // counter
	int ii;     // counter for high temp
	int iii;   // counter for low temp
	int hightemp;
	int lowtemp;
	int highest = 0;
	int lowest = 0; 
	double total = 0;

	printf("---=== IPC Temperature Analyzer ===---\n");

	for (i = 0; i < NUMS; i++) { 

		printf("Enter the high value for day %d: ", i + 1);
		scanf("%d", &hightemp);
		printf("\n");
		printf("Enter the low value for day %d: ", i + 1);
		scanf("%d", &lowtemp);
		printf("\n"); 
		
		while (hightemp > 40 || hightemp < -40 || lowtemp > 40 || lowtemp < -40 || hightemp < lowtemp) { // setting conditions between -41 & 41 
			printf("Incorrect values, temperatures must be in the range -40 to 40, high must be greater than low.\n\n");
			printf("Enter the high value for day %d: ", i + 1);
			scanf("%d", &hightemp);
			printf("\n");
			printf("Enter the low value for day %d: ", i + 1);
			scanf("%d", &lowtemp);
			printf("\n");
		
		}
	
		total = total + hightemp + lowtemp; // calculating average of correct variables
	
		if (hightemp > highest) { // if tempature entered greater then previously entered tempature, it is the new highest tempature
			highest = hightemp;
			ii = i + 1;

		} else if (hightemp < highest) { //if tempature entered is less then previously entered tempature, remains the same
			highest = highest;
			ii = ii; 

		}	if (lowtemp < lowest) { // if tempature entered less then previously entered tempature, it is the new lowest tempature
			lowest = lowtemp;
			iii = i + 1; 

		} else if (lowtemp > lowest) { //if tempature entered is greater then previously entered tempature, remains the same
			lowest = lowest;
			iii = iii; 
		}
	}

		printf("The average (mean) temperature was: %.2lf\n", total / (NUMS * 2)); // mean calculation 
		printf("The highest temperature was %d, on day %d\n", highest, ii);        //highest tempature 
		printf("The lowest temperature was %d, on day %d\n", lowest, iii);         //lowest tempature

	return 0;

}
