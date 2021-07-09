#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void import();
void createAccount();
void writer();
void intToStr(char*,int);
struct data
{
    int accountNumber;
    char firstName[20];
    char lastName[20];
    int pin;
    int balance;
};
struct data acc[100];
int dataCount=0;
void main()
{
    import();
    createAccount();
    writer();
}
void import()//Import data from Account Details
{
    FILE *fp;
    fp=fopen("accDet.txt","r");
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %s %d %d",&acc[i].accountNumber,acc[i].firstName,acc[i].lastName,&acc[i].pin,&acc[i].balance);
        i++;
    }
    dataCount=i;
    fclose(fp);
}
void createAccount()//Create Account and Store it in structure acc 
{
    FILE* fp;
    int accno;
    char accstr[10]="",fileName[30]="./Transaction/";
    accno=acc[dataCount-1].accountNumber+1;//100009+1=100010
    acc[dataCount].accountNumber=accno;
    printf("Enter your First Name :");
    scanf("%s", acc[dataCount].firstName);
    printf("Enter your Last Name:");
    scanf("%s",acc[dataCount].lastName);
    printf("Enter Pin:");
    scanf("%d",&acc[dataCount].pin);
    printf("Enter the Opening Balance:");
    scanf("%d",&acc[dataCount].balance);
    printf("Your account number is %d\n",accno);
    intToStr(&accstr[0],accno);
    strcat(fileName,accstr);
    strcat(fileName,".txt");
    fp=fopen(fileName,"w");
    fprintf(fp,"0\t+%d\t%d\n",acc[dataCount].balance,acc[dataCount].balance);
    dataCount++;
    fclose(fp);
    
}
void writer()//Writes all the changes made to Acount Details
{
    FILE *fp;
    fp=fopen("accDet.txt","w");
    int i;
    for(i=0;i<dataCount;i++)
    {
        fprintf(fp,"%d\t%s\t%s\t%d\t%d",acc[i].accountNumber,acc[i].firstName,acc[i].lastName,acc[i].pin,acc[i].balance);
        if(i<dataCount-1)
        {
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
}
void intToStr(char* st,int n)
{
    int arr[6],r,c=0,d=0,i;
    while(n>0)
    {
        r=n%10;
        n=n/10;
        arr[c]=r;
        c++;
    }//arr=6,5,4,3,2,1
    for(i=c-1;i>=0;i--)//i=5
    {//0 -> 48 to 57
        st[d]=(char)arr[i]+48;
        d++;
    }
}