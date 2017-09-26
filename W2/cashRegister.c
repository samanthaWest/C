/*	Name	:	Samantha West
	ID		:	128111168
	Section	:	IPC144 | MM  */


#include <stdio.h>

int main()
{
	double amount;
	double gst; 
	int remaining;
	int loonies;
	int quarters;
	int dimes;
	int nickels;
	int pennies; 	

	printf("Please enter the amount to be paid: $"); // entering amount to be paid
	scanf("%lf", &amount);

	gst = amount * .13 + .005; // calculating GST
	printf("GST: %.2lf\n", gst);
	printf("Balance owing: $%.2lf\n", amount + gst); // amount + GST

	remaining= (amount+gst) * 100; // loonies
	loonies = remaining / 100;
	remaining = remaining % 100;
	printf("Loonies required: %d, balance owing $%.2lf\n", loonies, (double)remaining / 100);

	quarters = remaining / 25; // quarters
	remaining = remaining % 25; 
	printf("Quarters required: %d, balance owing $%.2lf\n", quarters, (double)remaining / 100);

	dimes = remaining / 10; // dimes
	remaining = remaining % 10;
	printf("Dimes required: %d, balance owing $%.2lf\n", dimes, (double)remaining / 100);

	nickels = remaining / 5; // nickels
	remaining = remaining % 5;
	printf("Nickels required: %d, balance owing $%.2lf\n", nickels, (double)remaining / 100); 

	pennies = remaining / 1; // pennies 
	remaining = remaining % 1;
	printf("Pennies required: %d, balance owing $%.2lf\n", pennies, (double)remaining / 100); 


	return(0);
}











