// Lab 10
// Name: Samantha West
// Student Number: 128111168
// Email: swest9@myseneca.ca
// Section: M
// Date: April 6th, 2017
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int isJediMaster(const char name[]) {

	int isJedi = 0;
	// Jedi Master = 1, else remains 0
	char str1[17];
	

  FILE *fp = NULL;
  fp = fopen("jedi_master.txt", "r");
  if (fp != NULL) {

	  while (fscanf(fp, "%[^\n] ", str1) == 1) {

		  if (strcmp(name, str1) == 0) {

			  isJedi = 1;
		  }
	  }
	  fclose(fp);
  }
  return isJedi;

}

void formatJediPhoneRecord(char formattedRecord[], const char fullName[], const char npa[], const char co[], const char number[]) {

	int i;
	int flag;
	int strcount;
	char jedi[14] = " Jedi Master";
	char str1[3] = " (";
	char str2[3] = ") ";
	char str3[2] = "-";
	char str4[3] = "..";
	char str5[31] = "";
	char str6[2] = " ";


	if (strlen(fullName) > 16) {

		for (i = 0; i < 14; i++) {

			str5[i] = fullName[i];
		}

		strcat(str5, str4);

	}

	else {

		strcount = 16 - strlen(fullName);

		if (strcount < 16) {

			for (i = 0; i < 16; i++) {

				str5[i] = fullName[i];
			}

			for (i = 0; i < strcount; i++) {

				strcat(str5, str6);
			}	
		} 
	}

	strcpy(formattedRecord, str5);
	// copies string from fullName to formattedRecord to remove un wanted characters stored in formattedRecord

	// concatenates other string to formattedRecord in order want to be shown
	strcat(formattedRecord, str1);
	strcat(formattedRecord, npa);
	strcat(formattedRecord, str2);
	strcat(formattedRecord, co);
	strcat(formattedRecord, str3);
	strcat(formattedRecord, number);

	flag = isJediMaster(fullName);
	if (flag == 1) {

		strcat(formattedRecord, jedi);
	}	
}
