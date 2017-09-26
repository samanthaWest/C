//  -------------------------------------------------
//  Name:       Samantha West
//  Email:      swest9@myseneca.ca
//  Workshop:   WS9_@_HOME
//  Date:       2017-03-29
//  Section:    XX
//  -------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_TITLE_SIZE 21

//Type the struct here
struct Book {
	int _isbn;
	float price;
	int _year;
	int _qty;
	char _title[MAX_TITLE_SIZE];
};

//Type the function prototypes here
void display(void);
void menu(void);
void footer(void);
void flushKeyboard(void);
void displayInventory(const char filename[]);
void addBook(const char filename[], struct Book *b2Add);
void checkPrice(const char filename[], const int isbn2find);
int searchInventory(FILE *fp, const int isbn2find);
float calculateCapital(const char filename[]);
int readRecord(FILE *fp, struct Book *b2read);

int main()

{
	//Type your code here:
	int option;
	struct Book mybook;
	char filename[] = "inventory.txt";

	display();

	do {
		menu();
		printf("\nSelect: ");
		scanf("%d", &option);

		switch (option) {
		case 0:
			printf("Goodbye!\n");
			break;
		case 1:
			displayInventory(filename);
			break;
		case 2:
			printf("ISBN:");
			scanf("%d", &mybook._isbn);
			flushKeyboard();

			printf("Title:");
			scanf("%21[^\n]", mybook._title);
			flushKeyboard();

			printf("Year:");
			scanf("%d", &mybook._year);
			flushKeyboard();

			printf("Price:");
			scanf("%f", &mybook.price);
			flushKeyboard();

			printf("Quantity:");
			scanf("%d", &mybook._qty);
			flushKeyboard();

			addBook(filename, &mybook);
			break;
		case 3:
			printf("Please input the ISBN number of the book:\n\n");
			scanf("%d", &mybook._isbn);
			flushKeyboard();
			checkPrice(filename, mybook._isbn);
			break;
		case 4:
			calculateCapital(filename);
			break;
		default:
			printf("Invalid input, try again:\n");
		}
	} while (option != 0);

	return 0;
}

void display(void) {

	printf("Welcome to the Book Store\n");
	printf("=========================\n");

}

void menu(void)
{
	printf("Please select from the following options:\n");
	printf("1) Display the inventory.\n");
	printf("2) Add a book to the inventory.\n");
	printf("3) Check price.\n");
	printf("4) Calculate total capital of the store.\n");
	printf("0) Exit.\n");

}

void footer(void) {

	printf("===================================================\n");
}

void displayInventory(const char filename[])
{
	struct Book mybook;

	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if (fp != NULL) {

		printf("\n\nInventory\n");
		printf("===================================================\n");
		printf("ISBN      Title               Year Price  Quantity\n");
		printf("---------+-------------------+----+-------+--------\n");

		while (readRecord(fp, &mybook) == 5) {
			printf("%-10.0d%-20s%-5d$%-8.2f%-8d\n", mybook._isbn, mybook._title, mybook._year, mybook.price, mybook._qty);
		}
		fclose(fp);
		footer();
	}
	printf("\n");
}

void addBook(const char filename[], struct Book *b2Add)
{
	FILE *fp = NULL;
	int flag;
	int i;
	fp = fopen(filename, "a+");

	flag = searchInventory(fp, b2Add->_isbn);

	if (flag >= 0) {

		printf("The book exists in the repository!\n\n");
	} 
	else {
		
		i = flag + 1;

		fprintf(fp, "\n%d;%.2lf;%d;%d;%s", b2Add[i]._isbn, b2Add[i].price, b2Add[i]._year, b2Add[i]._qty, b2Add[i]._title);

		printf("The book is successfully added to the inventory.\n\n");
		fclose(fp);
	}	
}

void checkPrice(const char filename[], const int isbn2find)
{
	int flag;
	struct Book mybook;
	FILE *fp = NULL;

	fp = fopen(filename, "r");
	flag = searchInventory(fp, isbn2find);
	if (flag == -1) {

		printf("Book not found in repository!\n");
		fclose(fp);
	}
	else {

		fp = fopen(filename, "r");
		if (fp != NULL) {

			while (readRecord(fp, &mybook) == 5) {

				if (isbn2find == mybook._isbn) {
					printf("Book %d costs $%.2f\n", mybook._isbn, mybook.price);
					fclose(fp);
				}
			}
		}
	}
	printf("\n");

}

int searchInventory(FILE *fp, const int isbn2find)
{
	struct Book mybook;
	int i = 0;
	int flag = -1;

	if (fp != NULL) {
		while (readRecord(fp, &mybook) == 5) {

			if (mybook._isbn == isbn2find) {

				flag = i;
			}
			i++; 
		}
	}
	return flag;
}

float calculateCapital(const char filename[])
{
	struct Book mybook;
	float total_capital = 0.00f;

	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if (fp != NULL) {

		while (readRecord(fp, &mybook) == 5) {
			total_capital = total_capital + (mybook.price * mybook._qty);
			
		}
	}
	printf("The total capital is: $%.2f.", total_capital);
	printf("\n");

	return total_capital;
	fclose(fp);
}

int readRecord(FILE *fp, struct Book *b2read) {

	int rv = 0;

	if (fp != NULL) {

		rv = fscanf(fp, "%d;%f;%d;%d;%20[^\n]", &b2read->_isbn, &b2read->price, &b2read->_year, &b2read->_qty, b2read->_title);

	}
	return rv;
}

void flushKeyboard(void) {

	while (getchar() != '\n');
}
