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
void main()
{
    myimport();
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
    fclose(fp);
}