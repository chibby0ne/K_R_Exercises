#include <stdio.h>

#define MAX 1000

int getlinee(char s[], int max);

int main(int argc, char *argv[])
{
    char line[MAX];
    int num;
    int spaces;
    int index;
    int i;
    int space_arg;
    int c;

/*decrement argc by one cause argc counts the pointer to NULL and we increment by one the pointer
to the pointer array (cause the first pointer of the array point to the name of the program called itself e.g: detab) */

    while(--argc >0 && (*++argv)[0]=='-')
            space_arg=atoi(++(argv[0]));    //here we increment the pointer that points to the - that way we get the number
                                            //eg: -10 we get the pointer to 10
                                            //and store it in space_arg

    while ((num=getlinee(line,MAX))>0)
    {
        spaces=space_arg;
        index=0;
        while (index<num)
        {
            for (i=0; line[index+i]!='\t' && line[index+i]!='\0' ;i++)
                putchar(line[index+i]);                     //print as long as it isn't NULL or tab

            if (line[index+i] == '\t')
            {
                index+=i+1;
                spaces-=i;
                while(spaces-- >0)
                    putchar(' ');
                spaces=space_arg;
            }
            else if (line[index+i]=='\0')
                index+=i;
        }
    }
    return 0;
}

int getlinee(char s[], int max)
{
    int i,c;
    for (i=0; i<(max-1) && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (c=='\n')
        s[i++]='\n';
    s[i]='\0';
    return i;
}
