#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void importDetails();
void importTrans();
void createAccount();
void writer();
void intToStr(char*,int);
void withdrawl();
int auth(int,int);
int search(int);
void getFileName(char*,int);
void transHistory();
int login();
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
int userIndex;
void main()
{
    importDetails();
    int ch,ch1;
    printf("Welcome to the Bank Of TINT\n1.Login\n2.Create Account\nEnter your Choice:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
        if(login()==1)
        {
            printf("1.Withdrawl\n2.Transaction History\nEnter your choice:");
            scanf("%d",&ch1);
            switch (ch1)
            {
                case 1:
                    withdrawl();
                    break;
                case 2:
                    transHistory();
                    break;
                default:
                    printf("Wrong Choice!");
                    break;
            }

        }
        else
        {
            printf("Login Unsuccessful!\n");
        }
        break;
        case 2:
            createAccount();
            break;
        default:
            printf("Wrong Choice!");
            break;
    }
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
void importTrans()
{
    FILE* fp;
    int accNo;
    accNo = acc[userIndex].accountNumber;
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
    char fileName[30] = "";
    accno = acc[dataCount-1].accountNumber+1;//acc=100006
    acc[dataCount].accountNumber = accno;
    printf("Enter your First Name :");
    scanf("%s", acc[dataCount].firstName);
    printf("Enter your Last Name:");
    scanf("%s",acc[dataCount].lastName);
    printf("Enter Pin:");
    scanf("%d",&acc[dataCount].pin);
    printf("Enter the Opening Balance:");
    scanf("%d",&acc[dataCount].balance);
    printf("Your account number is %d\n",accno);
    getFileName(&fileName[0],accno);// ./Transaction/100006.txt
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
    int amt,bal,accNo;  
    printf("Enter Amount to be withdrawn:");
    scanf("%d",&amt);
    accNo=acc[userIndex].accountNumber;
    bal=acc[userIndex].balance;
    if(bal>=amt)
    {
        acc[userIndex].balance-=amt;
        printf("Transaction Successful!!\nYour Account balance is %d\n",acc[userIndex].balance);
        getFileName(&fileName[0],accNo);
        fp=fopen(fileName,"a");
        fprintf(fp,"\n%d\t0\t%d\t%d\n",bal,amt,acc[userIndex].balance);
        fclose(fp);
    } 
    else
    {
        printf("Insufficient Balance!!\n");

    }  
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
    int x=-1,i;
    for(i=0;i<dataCount;i++)
    {
        if(acc[i].accountNumber==accNo)
        {
            x=i;
            break;
        }
    }
    return(x);
}
void getFileName(char* fileName,int accNo)//100006
{
    char accstr[10]="";//   ./Transaction/100006.txt
    strcpy(fileName,"./Transaction/");
    intToStr(&accstr[0],accNo);
    strcat(fileName,accstr);
    strcat(fileName,".txt");
}
void transHistory()
{
    int i,j,accNo;
    accNo=acc[userIndex].accountNumber;
    importTrans(accNo);
    for(j=0;j<transCount;j++)
    {
        printf("%d\t%d\t%d\t%d\n",trans[j].initalBalance,trans[j].creditAmount,trans[j].debitAmount,trans[j].finalBalance);
    }
}
int login()
{
    int accNo,pin,i;
    printf("Account Number:");
    scanf("%d",&accNo);
    printf("PIN:");
    scanf("%d",&pin);
    i=search(accNo);
    if(i>=0)
    {
        if(pin==acc[i].pin)
        {
            userIndex=i;
            return (1);
        }
        else
        {
            printf("Incorrect PIN!\n%d %d",pin,acc[i].pin);
            return (0);
        }
    }
    else
    {
        printf("Account Doesnot Exist!\n");
        return 0;
    }

}