/*
Name: Samantha West
Student number: 128111168
Email: swest9@myseneca.ca
Workshop: 4
Section: M
Date: Febuary 8th, 2017
*/

#include <stdio.h>
#define MAXDAYS 10

int main() {

	int days;
	int i;
	int entry = 1;
	int sum = 0;
	int hightemp[MAXDAYS] = { 0 };
	int lowtemp[MAXDAYS] = { 0 };


	printf("---=== IPC Temperature Analyzer V2.0 ===---\n");
	printf("Please enter the number of days, between 3 and 10, inclusive: ");
	scanf("%d", &days);
	printf("\n");


	while (days < 3 || days > MAXDAYS) { // error prompt if number is not in correct range

		printf("Invalid entry, please enter a number between 3 and 10, inclusive: ");
		scanf("%d", &days);
		printf("\n");

	}

	for (i = 0; i < days; i++) { // prompt to enter recorded high & low tempatures

		printf("Day %d - High: ", i + 1);
		scanf("%d", &hightemp[i]);
		printf("Day %d - Low: ", i + 1);
		scanf("%d", &lowtemp[i]);
	}

	printf("\n");
	printf("Day  Hi  Low\n");

	for (i = 0; i < days; i++) {

		printf("%d    %d    %d\n", i + 1, hightemp[i], lowtemp[i]);

	}

	while (entry > 0) {

		printf("\nEnter a number between 1 and %d to see the average temperature for the entered number of days, enter a negative number to exit: ", days);
		scanf("%d", &entry);
		printf("\n");

		if (entry > days) {
			printf("Invalid entry, please enter a number between 1 and %d, inclusive: ", days);
			scanf("%d", &entry);
			printf("\n");

		}

		i = entry;
		for (i = 0; i < entry; i++) {

			sum += hightemp[i] + lowtemp[i];

		} if (i == entry) {
			printf("The average temperature up to day %d is: %.2lf", entry, (double)sum / (entry * 2));
			printf("\n");

			sum = 0;

		}

	}

	printf("Goodbye!");
	printf("\n");

	return 0;
}
