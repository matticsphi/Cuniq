/*
 * uniq.c
 *
 *  Created on: Apr 12, 2011
 *      Author: Mattics Phi
 */

#include "header.h"

/* Initial size for array */
#define BUFFERSIZE 5

char *read_long_line(FILE *file);

/* Main function */
int main(int argc, char *argv[])
{
	FILE *fp;
	/* Declarations */
	char *oldLine, *newLine;

	/* If redirecting a file, scan in name */
	if (argc == 2)
		fp = fopen(argv[1], "r");

	/* Else, just take from standard input */
	else
		fp = stdin;

	/* Assigns old line a line */
	oldLine = read_long_line(fp);

	/* Prints out the old line because it's the first line */
	printf("%s", oldLine);

	/* Loops by scanning in a line until it doesn't exist,
	 * puts the line in newline
	 */
	while ((newLine = read_long_line(fp)) != NULL) {

		/* Compares the new line and old line, prints out if
		 * the new line doesn't equal the old one
		 */
		if (strcmp(oldLine, newLine) != 0)
			printf("%s", newLine);

		/* Reassign newline into oldline to reuse for checking
		 * in next repetition
		 */
		oldLine = newLine;
	}

	return 0;
}

/* Function to read in a line from the file */
char *read_long_line(FILE *file)
{
	char *sentence = malloc(sizeof(char));
	char *check;

	/* If can't allocate memory for sentence, then exit function */
	if (fgets(sentence, BUFFERSIZE, file) == NULL)
			return NULL;

	/* If allocated, scan in a new line */
	else {

		/* Gets the end of the scanned in line */
		check = sentence + strlen(sentence);

		/* If check ends in a new line or EOF, exit, else, loop until it happens */
		while (((*(check - 1) != '\n') && (*(check - 1) != EOF))) {

			/* Reallocates memory to increase space for line */
			sentence = realloc(sentence, (BUFFERSIZE * 2 * strlen(sentence)));
			check = sentence + strlen(sentence);

			if (fgets(check, BUFFERSIZE, file) == NULL)
				break;

			check = sentence + strlen(sentence);
		}
	}

	return sentence;
}
