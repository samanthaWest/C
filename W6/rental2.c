/*
Name: Samantha West
Student number: 128111168
Email: swest9@myseneca.ca
Workshop: Functions
Section: M
Date: Febuary 28, 2017
*/

#include <stdio.h>

#define distRate1  0.69			// Rate per Kilometer from 0km to 100km (inclusive)
#define distRate2  0.49			// Rate per Kilometer above 100km 


// Structure Declaration for Vehicle Rentals
struct Rental
{
	int id;						// ID of the Rental Vehicle
	double baseDay;				// Daily Base Price 
	double earnings;			// Total earnings from this rental
};

/* prototype functions addPositive , taxCalc & subtractPositive*/
double addPositive(double amount, double newAmount);

double taxCalc(double price, double rate);

double subtractPositive(double amount, double newAmount);

double addPositive(double amount, double newAmount) {

	double result;

	if (newAmount > 0) {
		result = amount + newAmount;
	}
	else
		result = amount;

	return result;
}



double taxCalc(double price, double rate) {

	double result1;

	result1 = price * rate;

	return result1;
}


double subtractPositive(double amount, double newAmount) {

	double result2;

	if (newAmount > 0) {

		result2 = amount - newAmount;
	}
	else
		result2 = amount;

	return result2;
}

/* main program */
int main()
{
	const int noVehicles = 3;			// Number of Vehicles [ Changed to 3]
	int option;							// Variable to store the option selected
	int flag;							// Flag to support vehicle ID find
	int tempID;							// To hold user input for vehicle ID
	int i = 0;							// Variable for "for-loop" counters

										// Initialize the struct Vehicle Rental [ New addition for 3 Rentals]
	struct Rental vRent[] = { { 123, 9.95, 0 },{ 124, 19.95, 0 },{ 125, 29.95, 0 } };

	double taxRate = 14;				// Tax rate is 14%
	double discount = 5;    			// Discount amount for rentals (in CAD)

										/*Declare Your Variables Here*/

	int rentalDays;
	double basePrice;
	double kmDriven;
	double charge;
	char discountChoice;
	double taxes;
	int giftCard;


	printf("***** Rental Vehicle Management App *****\n\n");

	do
	{
		// Display the option list
		printf("1.) Rental Status\n");
		printf("2.) Apply Charges\n");
		printf("3.) Apply Taxes to All Rentals\n");
		printf("4.) Apply Gift Card\n");
		printf("0.) Log out\n\n");
		printf("Please enter an option to continue: ");

		scanf("%d", &option);

		switch (option)
		{
		case 0: // Exit the program
			break;

		case 1: // Rental Vehicle Status

			printf("\n-- Rental Vehicle Status --\n\n");
			printf("ID#      Earnings\n");
			printf("-------- ----------\n");

			for (i = 0; i < noVehicles; i++) {
				printf("%8d %10.2lf\n", vRent[i].id, vRent[i].earnings);
			}

			printf("\n");
			break;

		case 2: // Calculate Rental Charges

			flag = -1;
			printf("\n-- Rental Charges --\n\n");
			printf("Enter vehicle ID: ");
			scanf("%d", &tempID);

			// Finding the correct vehicle index
			for (i = 0; i < noVehicles && flag == -1; i++) {
				if (tempID == vRent[i].id) {
					flag = i;
				}
			}

			if (flag != -1) {

				i = flag;

				// Capture #days for the rental from user input
				printf("Enter Rental Period (in Days): ");
				scanf("%d", &rentalDays);

				// Calculate the base price (baseDay * Days)
				basePrice = rentalDays * vRent[i].baseDay;

				// Calculate cost for Kilometers driven using "distRate1 & 2 above"
				printf("Enter kilometers driven: ");
				scanf("%lf", &kmDriven);


				if (kmDriven > 100) {
					kmDriven = kmDriven - 100;
					kmDriven = kmDriven * distRate2 + (100 * distRate1);
				}
				else
					kmDriven = kmDriven * distRate1;

				// Add base Price and cost for kilometer driven in to a new variable 
				// "charge"

				charge = kmDriven + basePrice;

				/* Call addPositive function with current earnings for the rental and
				charge(calculated above) as arguments and assign the returned
				result back to earnings
				*/
				vRent[i].earnings = addPositive(vRent[i].earnings, charge);

				if (kmDriven < 0) {
					kmDriven = 0;
				}

				// Apply Discount with a prompt for Y or N
				// If the user input is skipped without being prompted, have one space infront 
				// of %c in the scanf statement => " %c" instead of "%c"

				printf("Apply Discount: ");
				scanf(" %c", &discountChoice);

				if (discountChoice == 'Y' || discountChoice == 'y') {

					vRent[i].earnings = subtractPositive(vRent[i].earnings, discount);
				}
				
				// Display Base Charge, cost for km and the Total 
				printf("\nBase   kmCost DiscStatus Total\n");
				printf("====== ====== ========== ======\n");
				// Use "%6.2lf %6.2lf %10c %6.2lf" formatting inside a printf statement
				printf("%6.2lf %6.2lf %10c %6.2lf", basePrice, kmDriven, discountChoice, vRent[i].earnings);
				printf("\n\n");

			}
			else {
				printf("ERROR: Vehicle ID does not exist.\n\n");
			}

			break;

		case 3: // Apply Taxes to all Earnings

			printf("\n-- Apply Taxes To all Accounts--\n\n");

			printf("ID#      Earnings   Taxes\n");
			printf("-------- ---------- ------\n");

			// Iterate over all Rentals. For each rental, calculate the taxes by calling taxCalc 
			// by passing current earnings and tax rate
			// Then call addPositive with current earnings and the taxes returned from taxCalc function
			// Then use "%8d %10.2lf %6.2lf" formatting to display ID, Earnings and taxes for each rental

			for (i = 0; i < noVehicles; i++) {

				taxes = (vRent[i].earnings * taxRate) / 100;
				vRent[i].earnings = addPositive(vRent[i].earnings, taxes);
				printf("%8d %10.2lf %6.2lf\n", vRent[i].id, vRent[i].earnings, taxes);
			}

			printf("\n");
			break;

		case 4: // Apply Gift Card

			flag = -1;
			printf("\n-- Apply Gift Card --\n\n");
			printf("Enter vehicle ID: ");
			scanf("%d", &tempID);


			// Finding the correct vehicle index
			for (i = 0; i < noVehicles && flag == -1; i++) {
				if (tempID == vRent[i].id) {
					flag = i;
				}
			}
			if (flag != -1) {

				i = flag; 
				// Capture Gift card amount

				printf("Enter Gift Card Amount: ");
				scanf("%d", &giftCard);

				/* call function subtractPositive with current earnings for the rental and Gift card
				amount as arguments and assign the returned result back to earnings
				*/

				vRent[i].earnings = subtractPositive(vRent[i].earnings, giftCard);
				printf("Discount Applied");
				printf("\n");
			}
			else {
				printf("ERROR: Vehicle ID does not exist.\n\n");
			}

			printf("\n");

			break;

		default:
			printf("Error: Please enter a valid option to continue\n\n");
			break;
		}


	} while (option != 0);


	return 0;
}
