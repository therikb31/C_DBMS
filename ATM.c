#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void importDetails();
void importTrans(int);
void createAccount();
void writer();
void intToStr(char*,int);
void withdrawl();
int auth(int,int);
int search(int);
void getFileName(char*,int);
void transHistory();
struct transaction
{
    int initalBalance;
    int creditAmount;
    int debitAmount;
    int finalBalance;
};
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
struct transaction trans[100];
int transCount=0;
void main()
{
    importDetails();
    transHistory();
    writer();
}
void importDetails()//Import data from Account Details
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
void importTrans(int accNo)
{
    FILE* fp;
    char fileName[30]="";
    getFileName(&fileName[0],accNo);
    fp=fopen(fileName,"r");
    int i=0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %d %d %d",&trans[i].initalBalance,&trans[i].creditAmount,&trans[i].debitAmount,&trans[i].finalBalance);
        i++;
    }
    transCount=i;
    fclose(fp);

}
void createAccount()//Create Account and Store it in structure acc 
{
    FILE* fp;
    int accno;
    char fileName[30]="";
    accno=acc[dataCount-1].accountNumber+1;
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
    getFileName(&fileName[0],accno);
    fp=fopen(fileName,"w");
    fprintf(fp,"0\t%d\t0\t%d\n",acc[dataCount].balance,acc[dataCount].balance);
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
    }
    for(i=c-1;i>=0;i--)
    {
        st[d]=(char)arr[i]+48;
        d++;
    }
}
void withdrawl()
{
    FILE* fp;
    char fileName[30];
    int accNo,pin,i,amt,bal;
    printf("Enter Acc No:");
    scanf("%d",&accNo);
    printf("Enter PIN:");
    scanf("%d",&pin);
    i=search(accNo);
    if(auth(acc[i].pin,pin)==1)
    {
        printf("Enter Amount to be withdrawn:");
        scanf("%d",&amt);
        bal=acc[i].balance;
        if(bal>=amt)
        {
            acc[i].balance-=amt;
        }
    }
    getFileName(&fileName[0],accNo);
    fp=fopen(fileName,"a");
    fprintf(fp,"%d\t0\t%d\t%d\n",bal,amt,acc[i].balance);
    fclose(fp);
}
int auth(int pin1,int pin2)
{
    if(pin1==pin2)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}
int search(int accNo)
{
    int i;
    for(i=0;i<dataCount;i++)
    {
        if(acc[i].accountNumber==accNo)
        {
            return(i);
            break;
        }
    }
}
void getFileName(char* fileName,int accNo)
{
    char accstr[10]="";
    strcpy(fileName,"./Transaction/");
    intToStr(&accstr[0],accNo);
    strcat(fileName,accstr);
    strcat(fileName,".txt");
}
void transHistory()
{
    int accNo,pin,i,j;
    printf("Enter Acc No:");
    scanf("%d",&accNo);
    printf("Enter PIN:");
    scanf("%d",&pin);
    i=search(accNo);
    if(auth(pin,acc[i].pin)==1)
    {
        importTrans(accNo);
        for(j=0;j<transCount;j++)
        {
            printf("%d\t%d\t%d\t%d\n",trans[j].initalBalance,trans[j].creditAmount,trans[j].debitAmount,trans[j].finalBalance);
        }
    }
}