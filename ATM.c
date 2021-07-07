#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void myimport();
void createAccount();
struct data
{
    char accountNumber[10];
    char firstName[20];
    char lastName[20];
    int pin;
    int balance;
};
struct data acc[100];
int dataCount=0;
void main()
{
    myimport();
    createAccount();
}
void myimport()//Import data from Account Details
{
    FILE *fp;
    fp=fopen("accDet.txt","r");
    int i=0,j;
    while(!feof(fp))
    {
        fscanf(fp,"%s %s %s %d %d",acc[i].accountNumber,acc[i].firstName,acc[i].lastName,&acc[i].pin,&acc[i].balance);
        i++;
    }
    dataCount=i;
    fclose(fp);
}
void createAccount()
{
    printf("Enter your First Name :");
    scanf("%s", acc[dataCount].firstName);
    printf("Enter your Last Name:");
    scanf("%s",acc[dataCount].lastName);
    printf("Enter Pin:");
    scanf("%d",&acc[dataCount].pin);
    printf("Enter the Opening Balance:");
    scanf("%d",&acc[dataCount].balance);
}