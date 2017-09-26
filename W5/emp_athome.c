/*
Name: Samantha West
Student number: 128111168
Email: swest9@myseneca.ca
Workshop: Structures ( Home )
Section: M
Date: Febuary 22, 2017
*/

#include <stdio.h>
#define SIZE 4

struct Employee {
	int employeeID;
	int age;
	double salary;
};

int main(void) {

	int option = 0;
	int i, empcount = 0;
	int entry;
	struct Employee emp[SIZE] = { { 0 } };

	printf("---=== EMPLOYEE DATA ===---\n\n");

	do {
		// Print the option list
		printf("1. Display Employee Information\n");
		printf("2. Add Employee\n");
		printf("3. Update Employee Salary\n");
		printf("4. Remove Employee\n");
		printf("0. Exit\n\n");
		printf("Please select from the above options: ");

		// Capture input to option variable
		scanf("%d", &option);
		printf("\n");

		switch (option) {
		case 0:	// Exit the program
			printf("Exiting Employee Data Program. Good Bye!!!\n");
			break;

		case 1: // Display Employee Data
			printf("EMP ID  EMP AGE EMP SALARY\n");
			printf("======  ======= ==========\n");

			for (i = 0; i < SIZE && i >= 0; i++) {
				if (emp[i].employeeID > 0)
					printf("%6d%9d%11.2lf\n", emp[i].employeeID, emp[i].age, emp[i].salary);
			}
			printf("\n");
			break;

		case 2:	// Adding Employee	
			printf("Adding Employee\n");
			printf("===============\n");

			i = empcount;
			if (i < SIZE) {
				printf("Enter Employee ID: ");
				scanf("%d", &emp[i].employeeID);
				printf("Enter Employee Age: ");
				scanf("%d", &emp[i].age);
				printf("Enter Employee Salary: ");
				scanf("%lf", &emp[i].salary);
				printf("\n");

				empcount++;
			}
			if (i >= SIZE) {
				printf("ERROR!!! Maximum Number of Employees Reached\n\n");
			}
			break;

		case 3: // Update Employee Salary
			printf("Update Employee Salary\n");
			printf("======================\n");
			do {
				printf("Enter Employee ID: ");
				scanf("%d", &entry);

			} while
				(entry != emp[0].employeeID &&
					entry != emp[1].employeeID &&
					entry != emp[2].employeeID &&
					entry != emp[3].employeeID);
			
			for (i = 0; entry != emp[i].employeeID; i++) {			
		
			}
			printf("The current salary is %.2lf\n", emp[i].salary);
			printf("Enter Employee New Salary: ");
			scanf("%lf", &emp[i].salary);
			
			printf("\n");

			break;
		case 4: // Remove Employee Data
			printf("Remove Employee\n");
			printf("===============\n");

			do {
				printf("Enter Employee ID: ");
				scanf("%d", &entry);

			} while
				(entry != emp[0].employeeID &&
					entry != emp[1].employeeID &&
					entry != emp[2].employeeID &&
					entry != emp[3].employeeID);


			for (i = 0; entry != emp[i].employeeID; i++) {

			}

			printf("Employee %d will be removed", emp[i].employeeID);
			emp[i].employeeID -= emp[i].employeeID;
			printf("\n\n");
			break;

		default:
			printf("ERROR: Incorrect Option: Try Again\n\n");
		}

	} while (option != 0);

	return 0;
}