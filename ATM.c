#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void importDetails();
void importTrans();
void createAccount();
void writer();
void intToStr(char*,int);
int strToInt(char*);
void withdrawl();
int auth(int,int);
int search(int);
void getFileName(char*,int);
void transHistory();
int login();
void deposit();
void transferFund();
void changePIN();
void menu();
void loginPage();
int  digitCount(int);
void spaceGen(char*,int);
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
    loginPage();
}
void loginPage()
{
    importDetails();
    system("clear");
    int ch,ch1,ch2;
    printf("+------------------------------------------+\n");
    printf("|\tWelcome to the Bank Of TINT        |\n");
    printf("+------------------------------------------+\n\n");
    printf("1.Login\n2.Create Account\nEnter your Choice:");
    scanf("%d",&ch);
    system("clear");
    switch(ch)
    {
        case 1:
            if(login()==1)
            {
                system("clear");
                menu();
            }
            else
            {
                printf("Login Unsuccessful!\n");
                printf("\n\n1.Return to Login Page\n0.Exit\nEnter your choice:");
                scanf("%d",&ch2);
                switch (ch2)
                {
                case 1:
                    loginPage();
                    break;
                case 0:
                    printf("Thank you for Banking with us!\n");
                    break;
                default:
                    printf("Wrong Choice!");
                    break;
                }
            }
            break;
        case 2:
            createAccount();
            writer();
            printf("\n\n1.Return to Login Page\n0.Exit\nEnter your choice:");
            scanf("%d",&ch1);
            switch (ch1)
            {
            case 1:
                loginPage();
                break;
            case 0:
                printf("Thank you for Banking with us!\n");
                break;
            default:
                printf("Wrong Choice!");
                break;
            }
            break;
        default:
            printf("Wrong Choice!");
            break;
    }
}
void menu()
{
    importDetails();
    int ch,ch1;
    printf("+------------------------------------------+\n");
    printf("|\t\t    HOME                   |\n");
    printf("+------------------------------------------+\n\n");
    printf("1.Withdrawl\n2.Deposit\n3.Transfer Fund\n4.Transaction History\n5.Change PIN\nEnter your choice:");
    scanf("%d",&ch1);
    switch (ch1)
    {
        case 1:
            system("clear");
            withdrawl();
            break;
        case 2:
            system("clear");
            deposit();
            break;
        case 3:
            system("clear");
            transferFund();
            break;
        case 4:
            system("clear");
            transHistory();
            break;
        case 5:
            system("clear");
            changePIN();
            break;
        default:
            system("clear");
            printf("Wrong Choice!\n");
            break;
    }
    writer();
    printf("\n\n1.Return to Home\n0.Exit\nEnter Your choice:");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            system("clear");
            menu();
            break;
        case 0:
            printf("Thank you for Banking with us!\n");
            break;
        default:
            printf("Wrong Choice!");
            break;
    }
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
    importDetails();
    FILE* fp;
    int accno,rpin,ch,rbal,ch1;
    char fileName[30] = "",pin[10],bal[12]="";
    accno = acc[dataCount-1].accountNumber+1;//acc=100006
    acc[dataCount].accountNumber = accno;
    printf("Enter your First Name :");
    scanf("%s", acc[dataCount].firstName);
    printf("Enter your Last Name:");
    scanf("%s",acc[dataCount].lastName);
    printf("Enter Pin:");
    scanf("%s",pin);
    rpin=strToInt(&pin[0]);
    if(rpin>=0)
    {
        acc[dataCount].pin=rpin;
        printf("Enter the Opening Balance:");
        scanf("%s",bal);
        rbal=strToInt(&bal[0]);
        if(rbal>=0)
        {
            acc[dataCount].balance=rbal;
            printf("Your account has been successfully created!!\n");
            printf("Your account number is %d\n",accno);
            getFileName(&fileName[0],accno);// ./Transaction/100006.txt
            fp=fopen(fileName,"w");
            fprintf(fp,"0\t%d\t0\t%d",acc[dataCount].balance,acc[dataCount].balance);
            dataCount++;
            fclose(fp);
        }
        else
        {
            printf("Please enter a numeric balance!\n");
            printf("\n\n1.Retry Creating Account\n0.Exit\nEnter Your Choice:");
            scanf("%d",&ch1);
            switch (ch1)
            {
                case 1:
                    system("clear");
                    createAccount();
                    break;
                case 0:
                    printf("Thank you for Visiting Us!\n");
                    break;
                default:
                    printf("Wrong Choice!\n");
                    break;
            }
        }
         
    }
    else
    {
        printf("Please enter a numeric pin!\n");
        printf("\n\n1.Retry Creating Account\n0.Exit\nEnter Your Choice:");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1:
                system("clear");
                createAccount();
                break;
            case 0:
                printf("Thank you for Visiting Us!\n");
                break;
            default:
                printf("Wrong Choice!\n");
                break;
        }
    }
    
    writer();
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
        fprintf(fp,"\n%d\t0\t%d\t%d",bal,amt,acc[userIndex].balance);
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
    
    int i,j,k,accNo;
    accNo=acc[userIndex].accountNumber;
    importTrans(accNo);
    if (transCount>0)
    {
        printf("+-------------------------------------------+\n");
            printf("|\t     Transaction History            |\n");
            printf("+-------------------------------------------+\n\n");
        printf("  +---------------------------------------+\n");
        printf("  |Initial  | Credit  | Debit   |  Total  |\n");
        printf("  |Amount   | Amount  | Amount  | Balance |\n");
        printf("  +---------------------------------------+\n");
    }
    for(j=0;j<transCount;j++)
    {
        char s1[10]="",s2[10]="",s3[10]="",s4[10]="";
        spaceGen(&s1[0],trans[j].initalBalance);
        spaceGen(&s2[0],trans[j].creditAmount);
        spaceGen(&s3[0],trans[j].debitAmount);
        spaceGen(&s4[0],trans[j].finalBalance);
        printf("  |%d%s|%d%s|%d%s|%d%s|\n",trans[j].initalBalance,s1,trans[j].creditAmount,s2,trans[j].debitAmount,s3,trans[j].finalBalance,s4);
    }
    printf("  +---------------------------------------+\n");
}
int login()
{
    int accNo,pin,i;
    printf("+------------------------------------------+\n");
    printf("|\t\t Login Page                |\n");
    printf("+------------------------------------------+\n\n");
    printf("Account Number:");
    scanf("%d",&accNo);
    i=search(accNo);
    if(i>=0)
    {
        printf("PIN:");
        scanf("%d",&pin);
        if(pin==acc[i].pin)
        {
            userIndex=i;
            return (1);
        }
        else
        {
            printf("Incorrect PIN!\n");
            return (0);
        }
    }
    else
    {
        printf("Account Doesnot Exist!\n");
        return 0;
    }
}
void deposit()
{
    FILE* fp;
    int amt,bal,accNo;
    char fileName[30];// ./Transaction/100003.txt
    printf("Deposit Amount:");
    scanf("%d",&amt);
    bal=acc[userIndex].balance;
    acc[userIndex].balance+=amt;
    accNo=acc[userIndex].accountNumber;
    getFileName(&fileName[0],accNo);
    fp=fopen(fileName,"a");
    fprintf(fp,"\n%d\t%d\t0\t%d",bal,amt,acc[userIndex].balance);
    printf("Transaction Successful!!\nYour Account Balance is %d\n",acc[userIndex].balance);
    fclose(fp);
}
void transferFund()
{
    FILE *fp;
    char fileName[30]="",recFileName[30]="";
    int recAccNo,recUserIndex=-1,i,tamt,bal,recBal;
    bal=acc[userIndex].balance;
    printf("Reciever's Account No:");
    scanf("%d",&recAccNo);
    for(i=0;i<dataCount;i++)
    {
        if(acc[i].accountNumber==recAccNo)
        {
            recUserIndex=i;
            break;
        }
    }
    recBal=acc[recUserIndex].balance;
    if(recUserIndex>=0)
    {
        printf("Trasfer Amount:");
        scanf("%d",&tamt);
        acc[userIndex].balance-=tamt;
        getFileName(&fileName[0],acc[userIndex].accountNumber);
        fp=fopen(fileName,"a");
        fprintf(fp,"\n%d\t0\t%d\t%d",bal,tamt,acc[userIndex].balance);
        fclose(fp);
        acc[recUserIndex].balance+=tamt;
        getFileName(&recFileName[0],acc[recUserIndex].accountNumber);
        fp=fopen(recFileName,"a");
        fprintf(fp,"\n%d\t%d\t0\t%d",recBal,tamt,acc[recUserIndex].balance);
        fclose(fp);
        printf("Trasfer Successfull!\nYour Account Balance is %d\n",acc[userIndex].balance);
    }
    else
    {
        printf("Invalid Account No!\n");
    }
}
void changePIN()
{
    int oPin,nPin1,nPin2;
    printf("Re-Enter your existing PIN:");
    scanf("%d",&oPin);
    if(oPin==acc[userIndex].pin)
    {
        printf("Enter New PIN:");
        scanf("%d",&nPin1);
        printf("Re-Enter New PIN:");
        scanf("%d",&nPin2);
        if(nPin1==nPin2)
        {
            acc[userIndex].pin=nPin2;
            printf("PIN Change Successful!");
        }
        else
        {
            printf("PIN Mismatch!\n");
        }
    }
    else
    {
        printf("Incorrect PIN!\n");
    }
}
int digitCount(int n)
{
    if(n==0)
    {
        return(1);
    }
    else
    {
        int c=0;
        while(n>0)
        {
            c++;
            n=n/10;
        }
        return(c);
    }
}
void spaceGen(char* st,int x)
{
    int k;
    for(k=0;k<9-digitCount(x);k++)
    {
        strcat(st," ");
    }
}
int strToInt(char *st)
{
    int x=0,i=0,a;
    while(st[i]!='\0')
    {
        a=(int)st[i];
        if(a>=48 && a<=57)
        {
            x=(x*10)+(a-48);
            i++;
        }
        else
        {
            x=-1;
            break;
        }
    }
    return(x);
}