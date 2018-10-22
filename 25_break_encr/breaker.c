#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 5

int break_it(FILE* fptr);
int index_of_max(int values[], int nvalues);

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("Failed to open the input file!");
    return EXIT_FAILURE;
  }

  int key = break_it(fptr);

  if(!feof(fptr)) {
    printf("Didn't reach end of file\n");
    return EXIT_FAILURE;
  } else if(ferror(fptr)) {
    printf("Error reading input\n");
    return EXIT_FAILURE;
  }
  if (fclose(fptr) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  printf("%d\n", key);
  return EXIT_SUCCESS;
}

int index_of_max(int values[], int nvalues) {
  int index_of_max = 0;
  int max = 0;
  for(int i=0; i<nvalues; i++) {
    if (values[i] > max) {
      max = values[i];
      index_of_max = i;
    }
  }
  return index_of_max;
}

int break_it(FILE* fptr) {
  int c;
  int frequencies[26] = {0};
  while ( (c=fgetc(fptr)) != EOF ) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      frequencies[c] += 1;
    }
  }
  return index_of_max(frequencies, 26);
}
