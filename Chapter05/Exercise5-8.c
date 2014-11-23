#include <stdio.h>
#define MAX 1000

static char daytab[2][13]= {{0,31,28,31,30,31,30,31,31,30,31,30,31},
                            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
void months(int month);

int getnumber();
int getline(char *s, int lim);
void atoi(char *s, int *num);

char jan[]="JAN";
char feb[]="FEB";
char mar[]="MAR";
char apr[]="APR";
char may[]="MAY";
char jun[]="JUN";
char jul[]="JUL";
char aug[]="AUG";
char sep[]="SEP";
char oct[]="OCT";
char nov[]="NOV";
char dec[]="DEC";



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
    //months(month);
    getchar();
    return 0;
}



int getnumber()
{
    int num;
    char s[MAX];
    getline(s,MAX);
    atoi(s,&num);
    return num;
}


int getline(char *s, int lim)
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


void months(int month)
{
    switch (month)
    {
        case 0:
            printf("Error");
            break;
        case 1:
            printf("%s", jan);
            break;
        case 2:
            printf("%s", feb);
            break;
        case 3:
            printf("%s", mar);
            break;
        case 4:
            printf("%s", apr);
            break;
        case 5:
            printf("%s", may);
            break;
        case 6:
            printf("%s", jun);
            break;
        case 7:
            printf("%s", jul);
            break;
        case 8:
            printf("%s", aug);
            break;
        case 9:
            printf("%s", sep);
            break;
        case 10:
            printf("%s", oct);
            break;
        case 11:
            printf("%s", nov);
            break;
        case 12:
            printf("%s", dec);
            break;
        default:
            printf("Error");
            break;
    }
}

int day_of_year(int year, int month, int day)
{

    int i, leap;
    if (year<0 || year==0 && (day==0||month==0) || day<=0 || month<=0 || month>12 || day>31)
        return -1;
    leap = ((year%4 == 0 && year%100 != 0 )|| (year%400==0));
    for (i=1; i<month;i++)
        day+=daytab[leap][i];
    return day;

}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = ((year%4 == 0 && year%100!=0)|| (year%400==0));

    if (year<0 || year==0 && yearday==0 || yearday<=0 || yearday>366)
    {
        *pmonth=0;
        *pday=-1;
    }
    else
    {
        for (i=1; yearday>daytab[leap][i]; i++)
            yearday -= daytab[leap][i];
        *pmonth=i;
        *pday=yearday;
    }
}
