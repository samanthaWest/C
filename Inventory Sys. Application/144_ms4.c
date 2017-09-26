// Final Project Milestone 4 (Final Submission)
// Name: Samantha West
// Student Number: 128111168
// Email: swest9@myseneca.ca
// Section: M
// Date: April 9th, 2017
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


// Define statements:

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define DATAFILE "items.txt"

// Constant TAX value:

const double tax = 0.13;

// Item structure:

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

// Function Prototypes Milestone 1:

void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);

// app interface
int yes(void);
void GroceryInventorySystem(void);
int menu(void);

// Function Prototypes Milesone 2:

double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

// Function Prototypes Milestone 3: 

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);

// Function Prototype Milestone 4: 

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);


// Extra Functions

// void lowInventoryReport(struct Item item[], int NoOfRecs);
// void SeniorsDiscount(struct Item item[]);

int main(void) {

	GroceryInventorySystem();

	return 0;
}

// Function Implementations Milestone 1:

void welcome(void) {

	printf("---=== Grocery Inventory System ===---\n\n");
}

void printTitle(void) {

	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void printFooter(double gTotal) {

	printf("--------------------------------------------------------+----------------\n");

	if (gTotal > 0) {

		printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
}

void flushKeyboard(void) {

	while (getchar() != '\n');
}

void pause(void) {

	printf("Press <ENTER> to continue...");
	flushKeyboard();
}

int getInt(void) {

	int value;
	char NL = 'x';

	do {
		scanf("%d%c", &value, &NL);
		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid integer, please try again: ");
		}
	} while (NL != '\n');

	return value;
}

int getIntLimited(int lowerLimit, int upperLimit) {

	int value;

	do {
		value = getInt();
		if (value < lowerLimit || value > upperLimit) {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		}
	} while (value < lowerLimit || value > upperLimit);

	return value;
}

double getDouble(void) {

	double value;
	char NL = 'x';

	do {
		scanf("%lf%c", &value, &NL);
		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid number, please try again: ");
		}
	} while (NL != '\n');

	return value;
}

double getDoubleLimited(double lowerLimit, double upperLimit) {

	double value;

	do {
		value = getDouble();
		if (value < lowerLimit || value > upperLimit) {
			printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);
		}
	} while (value < lowerLimit || value > upperLimit);

	return value;
}

int yes(void) {

	char value;
	int flag = 0;

	scanf(" %c", &value);
	flushKeyboard();

	while (value != 'Y' && value != 'y' && value != 'N' && value != 'n') {

		scanf(" %c", &value);
		flushKeyboard();

		if (value != 'Y' && value != 'y' && value != 'N' && value != 'n') {
			printf("Only (Y)es or (N)o are acceptable: ");
		}
	}

	if (value == 'y' || value == 'Y') {
		flag = 1;
	}
	return flag;
}
int menu(void) {

	int option;

	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	// printf("8- Low Inventory Report\n");
	// printf("9- Senior Discount\n");
	printf("0- Exit program\n");
	printf("> ");

	option = getIntLimited(0, 7);

	return option;
}
void GroceryInventorySystem(void) {

	int option;
	int flag = 0;
	int fail;
	int recordsread = 0;
	struct Item items[MAX_ITEM_NO];

	loadItems(items, "item.txt", &recordsread);

	welcome();
	
		do {
			option = menu();
			switch (option) {
			case 0:
				printf("Exit the program? (Y)es/(N)o: ");
				flag = yes();
				break;
			case 1:
				listItems(items, recordsread);
				pause();
				break;
			case 2:
				search(items, recordsread);
				pause();
				break;
			case 3:
				adjustQuantity(items, recordsread, CHECKOUT);

				fail = saveItems(items, DATAFILE, recordsread);

				if (fail == 0) {

					printf("could not update file %s\n", DATAFILE);
				}
				pause();
				break;
			case 4:
				adjustQuantity(items, recordsread, STOCK);

				fail = saveItems(items, DATAFILE, recordsread);

				if (fail == 0) {

					printf("could not update file %s\n", DATAFILE);
				}

				pause();
				break;
			case 5:
				addOrUpdateItem(items, &recordsread);
				fail = saveItems(items, DATAFILE, recordsread);
				
				if (fail == 0) {

					printf("could not update file %s\n", DATAFILE);
				}				
				pause();
				break;
			case 6:
				printf("Not implemented!\n");
				pause();
				break;
			case 7:
				printf("Not implemented!\n");
				pause();
				break;
				// case 8:
				// lowInventoryReport(item, NoOfRecs);
				// break;
				// case 9:
				// SeniorsDiscount(item);
			default:
				break;
			}
		} while (flag == 0);
}

// Function Implementations Milestone 2:

double totalAfterTax(struct Item item) {

	double total;
	total = item.price * item.quantity;

	//an integer Flag, if true (non - zero), the tax is applied in price calculations.
	//The value of Tax is kept in the global constant double TAX variable.

	if (item.isTaxed != 0) {

		total = total + (total * tax);
	}
	return total;
}


int isLowQuantity(struct Item item) {

	int flag;

	if (item.quantity < item.minQuantity) {
		flag = 1;
	}
	else
		flag = 0;

	return flag;
}


struct Item itemEntry(int sku) {

	struct Item items;
	items.sku = sku;

	printf("        SKU: %d\n", sku);

	printf("       Name: ");
	scanf("%20[^\n]", items.name);
	flushKeyboard();

	printf("      Price: ");
	items.price = getDouble();

	printf("   Quantity: ");
	items.quantity = getInt();

	printf("Minimum Qty: ");
	items.minQuantity = getInt();

	printf("   Is Taxed: ");
	items.isTaxed = yes();

	return items;
}


void displayItem(struct Item item, int linear) {

	// linear format
	if (linear == 1) {

		printf("|%3d|%-20s|%8.2lf|", item.sku, item.name, item.price);

		if (item.isTaxed != 0) {
			printf("  Yes");
		}
		else
			printf("   No");

		printf("|%4d |%4d |%12.2lf|", item.quantity, item.minQuantity, totalAfterTax(item));

		if (item.quantity <= item.minQuantity) {
			printf("***");
		}

		printf("\n");
	}

	// form format
	else {

		printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		printf("   Is Taxed: ");

		if (item.isTaxed != 0) {
			printf("Yes\n");
		}
		else
			printf("No\n");

		if (item.quantity <= item.minQuantity) {
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}

void listItems(const struct Item item[], int NoOfItems) {

	int i;
	double grandTotal = 0;

	printTitle();

	for (i = 0; i < NoOfItems; i++) {

		printf("%-4d", i + 1);
		displayItem(item[i], LINEAR);

		grandTotal = grandTotal + totalAfterTax(item[i]);
	}

	printFooter(grandTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {

	int i;
	int flag = 0;
	// flag initialized and will return 0 until item located where flag will equal and return 1
	// 1 : Sku has been found
	// 0 : Sku has not been found

	for (i = 0; i < NoOfRecs; i++) {

		if (item[i].sku == sku) {
			*index = i;
			flag = 1;
		}
	}
	return flag;
}

// Function Implementations Milestone 3:

void search(const struct Item item[], int NoOfRecs) {

	int sku;
	int found;
	int index;

	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN, SKU_MAX);
	found = locateItem(item, NoOfRecs, sku, &index);

	if (found != 0) {

		displayItem(item[index], FORM);
	}
	else
		printf("Item not found!\n");
}

void updateItem(struct Item* itemptr) {

	int flag;
	struct Item items;

	printf("Enter new data:\n");
	items = itemEntry(itemptr->sku);

	printf("Overwrite old data? (Y)es/(N)o: ");
	flag = yes();

	if (flag != 0) {

		printf("--== Updated! ==--\n");
		*itemptr = items;
	}
	else
		printf("--== Aborted! ==--\n");
}

void addItem(struct Item item[], int *NoOfRecs, int sku) {

	int flag;
	// flag: Yes = 1 & No = 0
	struct Item items;

	if (*NoOfRecs == MAX_ITEM_NO) {
		printf("Can not add new item; Storage Full!\n");

	}
	else {
		items = itemEntry(sku);

		printf("Add Item? (Y)es/(N)o: ");
		flag = yes();

		if (flag == 1) {

			item[*NoOfRecs] = items;
			*NoOfRecs += 1;
			printf("--== Added! ==--\n");
		}
		else
			printf("--== Aborted! ==--\n");
	}
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {

	int i;
	int sku;
	int flag;
	// flag: Yes = 1 & No = 0
	int option;
	// option stores return value of yes() function.. (Y)es = 1 & (N)o = 0 

	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN, SKU_MAX);

	flag = locateItem(item, *NoOfRecs, sku, &i);

	if (flag == 1) {

		displayItem(item[i], FORM);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		option = yes();

		if (option == 1) {
			updateItem(&item[i]);
		}
		else
			printf("--== Aborted! ==--\n");
	}
	if (flag == 0) {
		addItem(item, NoOfRecs, sku);
	}
}

void adjustQuantity(struct Item item[], int NoOfRecs, int stock) {

	int i;
	int sku;
	int flag;
	int stockadj;
	// variable to determine whether to stock or checkout, used to adjust stock quantities of items
	char *stocked;
	int locatesku;

	if (stock == STOCK) {
		stocked = "to stock";
		// add stock %s
	}

	if (stock == CHECKOUT) {
		stocked = "to checkout";
		// checkout stock %s
	}

	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN, SKU_MAX);
	locatesku = locateItem(item, NoOfRecs, sku, &i);

	if (locatesku == 0) {

		printf("SKU not found in storage!\n");
	}

	else {

		displayItem(item[i], FORM);
		printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", stocked, (MAX_QTY - item[i].quantity));
		stockadj = getIntLimited(0, (MAX_QTY - item[i].quantity));

		if (stock == STOCK && stockadj != 0) {

			printf("--== Stocked! ==--\n");
			item[i].quantity += stockadj;

		}

		if (stock == CHECKOUT && stockadj != 0) {

			printf("--== Checked out! ==--\n");
			item[i].quantity -= stockadj;
			flag = isLowQuantity(item[i]);

			if (flag == 1) {

				printf("Quantity is low, please reorder ASAP!!!\n");
			}

		}

		if (stockadj == 0) {
			printf("--== Aborted! ==--\n");
		}
	}
}

// Function Implementations Milestone 4 

void saveItem(struct Item item, FILE* dataFile) {

	fprintf(dataFile, "%d,%d,%d,%.2f,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);

}

int loadItem(struct Item* item, FILE* dataFile) {

	int df = 0;

	df = fscanf(dataFile, "%d,%d,%d,%lf,%d,%20[^\n]", &item->sku, &item->quantity, &item->minQuantity, &item->price, &item->isTaxed, item->name);

	return df;
}

int saveItems(const struct Item item[], char fileName[], int NoOfRecs) {

	int i;
	int flag;
	FILE *fp = NULL;
	fp = fopen(fileName, "w");

	if (fp != NULL) {

		for (i = 0; i < NoOfRecs; i++) {

			saveItem(item[i], fp);
			flag = 1;
			fclose(fp);
		}
	}
	else {

		flag = 0;
	}
	return flag;
}

int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr) {

	int i = 0;
	int flag;
	FILE *fp = NULL;
	fp = fopen(fileName, "r");

	if (fp != NULL) {

		while (loadItem(&item[i], fp) == 6) {
			i++;
			flag = 1;
			fclose(fp);
		}
	}
	else {

		flag = 0;
	}
	*NoOfRecsPtr = i;
	return flag;
}

// Extra Functions 

//void lowInventoryReport(struct Item item[], int NoOfRecs) {
//
//	int i;
//	int flag;
//	int option;
//
//	for (i = 0; i <= NoOfRecs; i++) {
//
//		flag = isLowQuantity(item[i]);
//
//		if (flag == 1) {
//
//			displayItem(item[i], LINEAR);
//		}
//	}
//
//	printf("\n");
//	printf("Would you like to re-order stock? (Y)es or (N)o: ");
//	option = yes();
//
//	if (option == 1) {
//
//		adjustQuantity(item, NoOfRecs, STOCK);
//	}
//	
//}
//
//void SeniorsDiscount(struct Item item[]) {
//
//	int i;
//	int sku;
//	int flag;
//	int locatesku;
//	double discount = 0.20;
//
//	printf("--== Seniors Discount ==--");
//	printf("\n\n");
//	printf("Please ask costumer for indentification...");
//	printf("Is the costumer over the age of 60?: ");
//	flag = yes();
//
//	if (flag == 1) {
//
//		printf("Please enter sku of item to apply discount: ");
//		locatesku = locateItem(item, MAX_ITEM_NO, sku, &i);
//
//		if (locatesku == 0) {
//
//			printf("SKU not found in storage!\n");
//		}
//		else
//
//			printf("%s : %.2lf with discount comes too... %.2lf", item[i].name, item[i].price, item[i].price - (item[i].price * (double) discount));
//			item[i].quantity -= 1;
//
//	}
//	else
//		printf("Sorry! You aren't eligable for the Seniors Discount.\n");
//
//}