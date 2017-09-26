/*
Name: Samantha West
Student number:12811168
Email: swest9@myseneca.ca
Workshop: 8
Section:
Date: March 27th 2017
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_BOOKS 10
#define MAX_TITLE_SIZE 21

struct Book {

	int _isbn; // International Standard Book Number
	float price; // Book Price
	int _year; // Publication Year
	char _title[MAX_TITLE_SIZE]; // Book Title
	int _qty; // Book Quantity
};

void display(void);
void displayMenu(void);
void displayInventory(const struct Book book[], const int size);
int searchInventory(const struct Book book[], const int isbn, const int size);
void addBook(struct Book book[], int *size);
void checkPrice(const struct Book book[], const int size);
void flushKeyboard(void);


int main(void)
{
	int option;
	int bookCounter = 0;
	struct Book book[MAX_BOOKS] = { { 0 } };

	display();

	do {
		displayMenu();
		printf("\nSelect: ");
		scanf("%d", &option);

		switch (option) {
		case 0:
			printf("Goodbye!\n");
			break;
		case 1:
			displayInventory(book, bookCounter);
			break;
		case 2:
			addBook(book, &bookCounter);
			break;
		case 3:
			checkPrice(book, MAX_BOOKS);
			break;

		default:
			printf("Invalid input, try again:\n");
		}
	} while (option != 0);

	return 0;
}

void flushKeyboard(void) {

	while (getchar() != '\n');
}

void display(void) {

	printf("Welcome to the Book Store\n");
	printf("=========================\n");

}

void displayMenu(void) {

	printf("Please select from the following options:\n");
	printf("1) Display the inventory.\n");
	printf("2) Add a book to the inventory.\n");
	printf("3) Check price.\n");
	printf("0) Exit.\n");

}

void displayInventory(const struct Book book[], const int size) {

	int i = 0;

	if (i < size) {
		printf("\n\n");
		printf("Inventory\n");
		printf("===================================================\n");
		printf("ISBN      Title               Year Price  Quantity\n");
		printf("---------+-------------------+----+-------+--------\n");

		for (i = 0; i < size; i++) {

				printf("%-10.0d%-20s%-5d$%-8.2f%-8d\n", book[i]._isbn, book[i]._title, book[i]._year, book[i].price, book[i]._qty);
		}
	}
	else
		printf("The inventory is empty!\n");
	printf("===================================================\n\n");
}

void addBook(struct Book book[], int *size) {

	int i;
	// stores index number if book found

	printf("ISBN:");
	scanf("%d", &book[*size]._isbn);
	flushKeyboard();

	printf("Quantity:");
	scanf("%d", &book[*size]._qty);
	flushKeyboard();

	if ((i = searchInventory(book, book[*size]._isbn, *size)) != -1) {

		book[i]._qty += book[*size]._qty;
		printf("The book exists in the repository, quantity is updated.\n\n");
	}

	else {

		if (*size == MAX_BOOKS) {

			printf("The inventory is full\n");
		}

		else {

			printf("Title:");
			scanf("%20[^\n]", book[*size]._title);
			flushKeyboard();

			printf("Year:");
			scanf("%d", &book[*size]._year);

			printf("Price:");
			scanf("%f", &book[*size].price);

			printf("The book is successfully added to the inventory.\n\n");

			*size = *size + 1;
		}
	}

}

int searchInventory(const struct Book book[], const int isbn, const int size) {

	int i;
	int flag = -1;
	// flag variable will be -1 till correct book found

	for (i = 0; i < size && flag == -1; i++) {

		if (book[i]._isbn == isbn) {

			flag = i;
		}
	}
	return flag;
}

void checkPrice(const struct Book book[], const int size) {

	int i;
	int ISBN;

	printf("Please input the ISBN number of the book:\n\n");
	scanf("%d", &ISBN);

	i = searchInventory(book, ISBN, size);

	if (i == -1) {
		printf("Book does not exist in the bookstore! Please try again.\n\n");
	}
	else {
		printf("Book %d costs $%.2lf\n\n", ISBN, book[i].price);
	}
}