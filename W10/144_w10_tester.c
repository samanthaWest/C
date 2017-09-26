#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void formatJediPhoneRecord(char formattedRecord[], const char fullName[], const char npa[], const char co[], const char number[]);

int main(void) {

  FILE* fptr = fopen("starwars_directory.csv", "r");

  char name[31];
  char npa[4];
  char co[4];
  char number[5];
  char formatted[46];
  
  if (fptr) {
    while (fscanf(fptr, "%[^,],%s%s%s\n", name, npa, co, number) == 4) {
      formatJediPhoneRecord(formatted, name, npa, co, number);      
	  printf("%s\n", formatted);
    }
    fclose(fptr);
  }
  else {
    printf("File not found!\n");
  }

  return 0;
}



