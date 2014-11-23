#include <stdio.h>
#define MAX 1000

static char daytab[2][13]= {{0,31,28,31,30,31,30,31,31,30,31,30,31},
                            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int getnumber();
int getlinee(char *s, int lim);
void atoi(char *s, int *num);


int main()
{
    char *monthss[]={"0", "January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"};
    int month, day;
    int y,m,d;

    //
    printf("Calculation of day of the year based on: year, month and day\n");
    printf("Enter year:\n");
    y=getnumber();
    printf("Enter month:\n");
    m=getnumber();
    printf("Enter day:\n");
    d=getnumber();
    printf("For the day %d of the month %s of the year %d, Day of the year is %d \n\n", d, monthss[m], y, day_of_year(y,m,d));

    printf("Calculation of day and month based on: day of the year and year\n");
    printf("Enter year:\n");
    y=getnumber();
    printf("Enter day of the year:\n");
    d=getnumber();
    month_day(y, d, &month, &day);
    printf("For the year: %d and day of the year:%d the month and the day is: %d %s" ,y, d, day,monthss[month]);
    getchar();
    return 0;
}



int getnumber()
{
    int num;
    char s[MAX];
    getlinee(s,MAX);
    atoi(s,&num);
    return num;
}


int getlinee(char *s, int lim)
{
    int i;
    for (i=(int)s; (((int)s-i)<(lim-1)) && (*s=getchar())!=EOF && *s!='\n'; s++)
        ;
    if (*s=='\n')
        s++;
    *s='\0';
    return (int)s-i;
}


void atoi(char *s, int *num)
{
    int sign,val;
    val=0;
    for (;*s=='\n' || *s==' ' || *s== '\t'; s++)
        ;
    sign=(*s=='-' ? -1 : 1);
    if (*s == '+' || *s == '-')
        s++;
    for(;*s >='0' && *s <='9'; s++)
        val=10*val+(*s-'0');
    *num = val*sign;
}

int day_of_year(int year, int month, int day)
{

    int i, leap;
    char *p;
    leap = ((year%4 == 0 && year%100 != 0 )|| (year%400==0));
    p= &daytab[leap][1];

    for (i=1; i<month; i++)
        day += *p++;
    return day;

}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    char *p;
    leap = ((year%4 == 0 && year%100!=0)|| (year%400==0));

    p= &daytab[leap][1];
    for (i=1; yearday> *p; i++)
        yearday -= *p++;
    *pmonth=i;
    *pday=yearday;
}
