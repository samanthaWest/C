/*
Name: Samantha West
Student number:
Email: swest9@myseneca.ca
Workshop: 7 Functions with Pointers
Section: M
Date: March 9th, 2017
*/

#include <stdio.h>
#define SIZE 3

void decompose(long long phonenumber, int *areaCode, int *prefix, int *lineNum);

int isValid(long long const trueFALSE);

// Function seperates entered phone number, stores parts in corresponding array
void decompose(long long phonenumber, int *areaCode, int *prefix, int *lineNum) {

	*areaCode = phonenumber / 10000000;
	*prefix = phonenumber / 10000 % 1000;
	*lineNum = phonenumber % 10000;

}


/* main program */
int main(void) {

	int i;
	int flag;
	int count = 0;
	int option;

	long long phoneNumber[SIZE] = { 0 };

	int areaCode;
	int prefix;
	int lineNum;

	printf("---=== Phone Numbers ===---\n\n");

	do {
		// Display the Option List
		printf("1. Display Phone List\n");
		printf("2. Add a Number\n");
		printf("0. Exit\n\n");
		printf("Please select from the above options: ");
		scanf("%d", &option);
		printf("\n");

		switch (option) {
		case 0:	// Exit the program

			printf("Exiting Phone Number App. Good Bye!!!");
			printf("\n");
			break;

		case 1: // Display the Phone List

			printf("Phone Numbers\n");
			printf("==============\n");
			
			// Phone numbers by area code, prefix, line number
			for (i = 0; i < SIZE; i++) {
				if (phoneNumber[i] > 0) {
					decompose(phoneNumber[i], &areaCode, &prefix, &lineNum);
					printf("(%3d)-%3d-%4d\n", areaCode, prefix, lineNum);
				}
			}
			printf("\n");
			break;

		case 2:	// Add a Phone Number

			printf("Add a Number\n");
			printf("============\n");


			if (count < SIZE) {
				scanf(" %lld", &phoneNumber[count]);
				flag = isValid(phoneNumber[count]);
				if (flag == 1) {
					count++;
				}
				else
					printf("ERROR!!! Phone Number is not Valid\n");

			}
			else
				printf("ERROR!!! Phone Number List is Full\n");
			printf("\n");
			break;

		default:
			printf("ERROR!!!: Incorrect Option: Try Again\n\n");
			break;

		}

	} while (option != 0);

	return 0;
}

int isValid(long long const trueFALSE) {

	int flag;

	if (trueFALSE / 10000000 == 416 || trueFALSE / 10000000 == 905 || trueFALSE / 10000000 == 647) {

		if (trueFALSE / 10000 % 1000 >= 100 && trueFALSE / 10000 % 1000 <= 999) {

			flag = 1;
		}
	}
	else
		flag = 0;

	return flag;

}

