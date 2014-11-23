/*Extend entab and detab to accept the shorthand
  entab -m +n
 to mean tab stops every n columns starting from column m. Choose convenient default behavior*/

#define MAX 100

#include <stdio.h>
#include <stdlib.h>

int getline(char *line, int max);


int main(int argc, char *argv[])
{
	int start_column;
	int every_columns;
	int i;
	char line[MAX];
	int total;
	int index;

	// handle the arguments

	if (argc > 3)
	{
		printf("More arguments than required\n");
		printf("Format is of type: entab -m +n\n");
		return 0;
	}
	else if (argc==3)
	{
		if (*argv[1]=='-')
			start_column=atoi((argv[1])+1);
		else
		{
			printf("It needs to start with '-'\n");
			printf("Setting start at 5th column\n");
			start_column=5;
		}

		if (*argv[2]=='+')
			every_columns=atoi(argv[2]+1);
		else
		{
			printf("It needs to start with '+'\n");
			printf("Setting every tab every 7 columns\n");
			every_columns=7;
		}
	}
	else if (argc==2)
	{

		if (*argv[1]=='-')
		{
			start_column=atoi(argv[1]+1);
			every_columns=7;
		}
		else if (*argv[1]=='+')
		{
			every_columns=atoi(argv[1]+1);
			start_column=5;
		}
		else
		{
			printf("It needs to start with - or +\n");
			printf("Setting defaults start=5, every=7\n");
			start_column=5;
			every_columns=7;
		}
	}
	else
	{
		start_column=5;
		every_columns=7;
	}
