/*Extend entab and detab to accept the shorthand
  entab -m +n
 to mean tab stops every n columns starting from column m. Choose convenient default behavior*/

#define MAX 100
#define TAB 8
#include <stdio.h>
#include <stdlib.h>

int getline(char *line, int max);
int strcmp(char *a, char *b);
void printspaces(int spaces);


int main(int argc, char *argv[])
{
	int start_column;
	int every_columns;
	int i;
	char line[MAX];
	int total;
	int index;
	int detab;
	int spaces;

	// handle the arguments
	switch(argc){
	    case 1:
            start_column=5;
            every_columns=7;
            detab=0;
            break;
        case 2:
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
            detab=0;
            break;

        case 3:
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
            detab=0;
            break;

        case 4:
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

            if (strcmp(argv[3], "-d"))
                detab=1;
            else
                detab=0;
            break;

        default:
            printf("More arguments than required\n");
            printf("Format is of type: entab -m +n\n");
            return 0;

	}

	//test
//	printf("a\tz\n");
//	printf("ab\ta\n");
//	printf("abc\ta\n");
//	printf("abcd\ta\n");
//	printf("abcde\ta\n");
//	printf("abcdef\ta\n");
//	printf("abcdefg\ta\n");
//	printf("abcdefgh\ta\n");

   /* printf("%d\n", argc);
	printf("%d\n", start_column);
	printf("%d\n", every_columns);*/
    if (detab)
    {
        while ((total=getline(line,MAX)) > 0)
        {
            spaces=0;
            index=0;
            for (i = 0; i < start_column-1; ++i)
                putchar(line[i]);
            index=i;

            if (start_column>TAB)
                spaces=TAB-((start_column-1)%TAB);
            else
                spaces=TAB-(start_column-1);
            printspaces(spaces);
            while (index < total)
            {
                for (i = 0; line[index+i] != '\0' && i < every_columns-1; ++i)
                    putchar(line[index+i]);
                if (line[index+i] == '\0')
                    break;

                if (every_columns > TAB)
                    spaces=TAB-((every_columns-1)%TAB);
                else
                    spaces=TAB-(every_columns-1);
                printspaces(spaces);

                index+=i;
            }
        }

    }
    else
    {
        while ((total=getline(line,MAX)) > 0)
        {
            index=0;
            for (i = 0; i < start_column-1; ++i)
                putchar(line[i]);
            index=i;
            putchar('\t');
            while (index < total)
            {
                for (i = 0; line[index+i] != '\0' && i < every_columns-1; ++i)
                    putchar(line[index+i]);
                if (line[index+i] == '\0')
                    break;
                putchar('\t');
                index+=i;
            }
        }

    }
	return 0;
}

void printspaces(int spaces)
{
    while (spaces--)
        putchar(' ');
}

int strcmp(char *a, char *b)
{
    while (*a++ == *b++)
        if (*a == '\0')
            return 1;
    return 0;
}

int getline(char lol[], int max)
{
	int i;
	char c;
	for (i=0; i<max-1 && (c=getchar())!=EOF && c!='\n'; i++)
		lol[i]=c;
	if (c == '\n')
		lol[i++]='\n';
	lol[i]='\0';
	return i;
}



