#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Declaring the functions used in this program
void importDetails();
void importTrans();
void createAccount();
void writer();
void intToStr(char*,int);
int strToInt(char*);
void withdrawl();
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

//Creating a structure of datatype 'transaction'
struct transaction
{
    int initalBalance;
    int creditAmount;
    int debitAmount;
    int finalBalance;
};

//Creating a structure of datatype 'data'
struct data
{
    int accountNumber;
    char firstName[20];
    char lastName[20];
    int pin;
    int balance;
};

//Initialising a global data variable to store all the accounts available
struct data acc[100];

//Initialising a global Integer variable to store the number of account records
int dataCount=0;

//Initialsing a global transaction variable to store all the transaction of an account
struct transaction trans[100];

//Initialsing a global Integer variable to store the number transactions of an account
int transCount=0;

//Initialsing a global Integer variable to store the index of given record in accDet.txt file
int userIndex;


void main()
{
    loginPage();
}

//Displays the login page 
void loginPage()
{
    importDetails();

    //Clears the previous terminal commands 
    system("clear");

    int ch,ch1,ch2;
    printf("+------------------------------------------+\n");
    printf("|\tWelcome to the Bank Of TINT        |\n");
    printf("+------------------------------------------+\n\n");

    //Prompts the user to enter a choice
    printf("1.Login\n2.Create Account\nEnter your Choice:");
    scanf("%d",&ch);
    system("clear");
    switch(ch)
    {
        case 1:

            //Prompts the user for login details
            if(login()==1)
            {
                //If login is successfull, the user is redirected to the Menu
                system("clear");
                menu();
            }
            else
            {
                //If login is unsuccessful, the user is given a choice to continue or exit
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

            //User is redirected to the create account section
            createAccount();


            //after successfully creating an account, the user is given a choice to continue or exit 
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

//Displays the homepage
void menu()
{

    // imports the data from accDet.txt and stores it in the structure variable acc
    importDetails();


    // user is given a choice to perform some actions on his account 
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

    // writes the changes made to the acc 
    writer();

    // user is given a choice to return to home or exit
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


//reads the data stored in accDet.txt and stores it in structure variable acc
void importDetails()
{
    FILE *fp;
    int i=0; 


    //the file addDet is open in read mode
    fp=fopen("accDet.txt","r");


    while(!feof(fp))
    {
        //reads the data recordwise and stores it in 'i'th index of acc
        fscanf(fp,"%d %s %s %d %d",&acc[i].accountNumber,acc[i].firstName,acc[i].lastName,&acc[i].pin,&acc[i].balance);
        i++;
    }
    //the final value of i gives us the number of records in accDet.txt
    dataCount=i;

    fclose(fp);
}


//reads the transactions of a given userIndex and stores it in structure variable trans
void importTrans()
{
    FILE* fp;
    int accNo,i=0;
    char fileName[30]="";

    //fetches the account number of the user currently logged in
    accNo = acc[userIndex].accountNumber;


    //gives us the required filename to access the transactions of a given account number
    getFileName(&fileName[0],accNo);


    //opens the requires file that contains the transaction details of the user
    fp=fopen(fileName,"r");


    while(!feof(fp))
    {
        //reads the file recorswise and stores the data in structure variable trans
        fscanf(fp,"%d %d %d %d",&trans[i].initalBalance,&trans[i].creditAmount,&trans[i].debitAmount,&trans[i].finalBalance);
        i++;
    }


    //the final value of i gives us the number of transaction records in the given file
    transCount=i;


    fclose(fp);
}


//adds user entered details to the structure acc
void createAccount()
{

    //imports the data from accDet.txt
    importDetails();


    FILE* fp;
    int accno,rpin,ch,rbal,ch1;
    char fileName[30] = "" , pin[10],bal[12] = "";

    
    //fetches a fresh account number for the new account being created
    accno = acc[dataCount-1].accountNumber+1;


    //adds values to the structure acc at last position i.e at dataCount
    acc[dataCount].accountNumber = accno;
    printf("Enter your First Name :");
    scanf("%s", acc[dataCount].firstName);
    printf("Enter your Last Name:");
    scanf("%s",acc[dataCount].lastName);
    printf("Enter Pin:");
    scanf("%s",pin);


    //converts the string pin entered by user into integer
    rpin = strToInt(&pin[0]);


    //if the pin entered is a number, we proceed
    if (rpin >= 0)
    {

        acc[dataCount].pin=rpin;
        printf("Enter the Opening Balance:");
        scanf("%s",bal);

        //converts the string balance entered by user into integer
        rbal=strToInt(&bal[0]);

        //if the balance entered is a number, we proceed
        if(rbal>=0)
        {
            acc[dataCount].balance = rbal;
            printf("Your account has been successfully created!!\n");
            printf("Your account number is %d\n",accno);


            // a file of filename <accno>.txt has to be created in the folder 'transaction'
            // to store the transactions made by the user. This function is used to generate
            // the appropriate filename with respect to the account number
            getFileName(&fileName[0],accno);


            //required file is opened in write mode
            fp=fopen(fileName,"w");

            //the opening balance is added to the transaction file
            fprintf(fp,"0\t%d\t0\t%d",acc[dataCount].balance,acc[dataCount].balance);

            //datacount is incremented cause we just added a new account
            dataCount++;

            fclose(fp);
        }

        //if the balance entered is not a number, user is given a choice to retry or exit
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
    //if the pin entered is not a number, user is given a choice to retry or exit
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
    
    //the changes are written to the accDet.txt file
    writer();
}


//Writes all the changes made to structure acc into the file accDet.txt
void writer()
{
    FILE *fp;
    int i;


    //the file accDet.txt is open in write mode
    fp=fopen("accDet.txt","w");

    
    for (i=0 ; i <dataCount ; i++)
    {
        //the data in structures is written into the file recordwise
        fprintf(fp,"%d\t%s\t%s\t%d\t%d",acc[i].accountNumber,acc[i].firstName,acc[i].lastName,acc[i].pin,acc[i].balance);

        //we avoid printing a blank line after the last record
        if(i < dataCount-1 )
        {
            fprintf(fp,"\n");
        }
    }

    fclose(fp);
}


//used to perform amount withdrawl from account
void withdrawl()
{

    FILE* fp;
    char fileName[30];
    int amt,bal,accNo;

    //promt user to enter values
    printf("Enter Amount to be withdrawn:");
    scanf("%d",&amt);

    //fetch account number of current user
    accNo = acc[userIndex].accountNumber;

    //fetch balance of current user
    bal = acc[userIndex].balance;

    //check whether user has sufficient amount to carrry out the transaction
    if (bal >= amt)
    {
        //reduces the balance of user
        acc[userIndex].balance -= amt;

        //displays current balance after withdrawl
        printf("Transaction Successful!!\nYour Account balance is %d\n",acc[userIndex].balance);

        //fetches the filename for the current account number
        getFileName(&fileName[0],accNo);

        //opens the required transaction file in append mode
        fp=fopen(fileName,"a");

        //adds the transaction made to the transaction history
        fprintf(fp,"\n%d\t0\t%d\t%d",bal,amt,acc[userIndex].balance);

        //close the current file
        fclose(fp);
    }

    //if the user has low balance, respective message is printed on the screen 
    else
    {
        printf("Insufficient Balance!!\n");
    }  
}


//checks whether given account number exists in structure acc
int search(int accNo)
{
    int x =- 1,i;

    //loop to traverse structure acc with 'dataCount' records
    for ( i=0 ; i<dataCount ; i++)
    {
        //if account is found, value of flag changes and loop breaks
        if (acc[i].accountNumber == accNo)
        {
            x=i;
            break;
        }
    }

    //the flag value is returned. negative return value indicates missing account 
    return(x);
}



//sandwiches the accNo with folder directory and file extension
void getFileName(char* fileName,int accNo)
{
    //create expty string accstr
    char accstr[10]="";

    //copy directory name to the string fileName
    strcpy(fileName,"./Transaction/");

    //convert integer accNo to string and store in accstr
    intToStr(&accstr[0],accNo);

    //copy accstr to the string fileName
    strcat(fileName,accstr);

    //copy extension to the string fileName
    strcat(fileName,".txt");
}



//used to print the transaction history of given account number
void transHistory()
{
    
    int i,j,k,accNo;

    //fetch the account number of current user
    accNo = acc[userIndex].accountNumber;

    //imports the transaction of given accountNumber and stores it in structure trans
    importTrans(accNo);

    //prints the page header    
    printf("+-------------------------------------------+\n");
    printf("|\t     Transaction History            |\n");
    printf("+-------------------------------------------+\n\n");

    //prnits the table header
    printf("  +---------------------------------------+\n");
    printf("  |Initial  | Credit  | Debit   |  Total  |\n");
    printf("  |Amount   | Amount  | Amount  | Balance |\n");
    printf("  +---------------------------------------+\n");


    for ( j=0 ; j<transCount ; j++)
    {
        char s1[10]="",s2[10]="",s3[10]="",s4[10]="";

        //generates adequate spaces after digits to maintain tabular structure
        spaceGen(&s1[0],trans[j].initalBalance);
        spaceGen(&s2[0],trans[j].creditAmount);
        spaceGen(&s3[0],trans[j].debitAmount);
        spaceGen(&s4[0],trans[j].finalBalance);

        //prints the transaction details recordwise
        printf("  |%d%s|%d%s|%d%s|%d%s|\n",trans[j].initalBalance,s1,trans[j].creditAmount,s2,trans[j].debitAmount,s3,trans[j].finalBalance,s4);
    }
     
    //prints the table footer
    printf("  +---------------------------------------+\n");
}



//prompt the user for login details
int login()
{
    int accNo,pin,i;

    //prints the page header
    printf("+------------------------------------------+\n");
    printf("|\t\t Login Page                |\n");
    printf("+------------------------------------------+\n\n");

    //ask the user for the account number
    printf("Account Number:");    
    scanf("%d",&accNo);

    //search for the account number in structure acc
    i=search(accNo);

    //if account is found in database, we proceed with login
    if(i>=0)
    {
        //ask the user for pin
        printf("PIN:");
        scanf("%d",&pin);

        //check whether the user entered pin matches the pin in structure acc
        if(pin==acc[i].pin)
        {   
            //if true, the index of account in structure acc is stored in userIndex
            userIndex=i;

            //the function returns 1 which indicates authentication successful
            return (1);
        }
        else
        {
            printf("Incorrect PIN!\n");

            //as the user entered pin doesnot match the actual pin,
            //the function returns 0 which indicate authentication failed
            return (0);
        }
    }

    //if the account is not found in the structure, error message is displayed
    else
    {
        printf("Account Doesnot Exist!\n");
        return 0;
    }
}



//used to perform amount withdrawl from account
void deposit()
{
    FILE* fp;
    int amt,bal,accNo;
    char fileName[30];

    printf("Deposit Amount:");
    scanf("%d",&amt);

    //fetch current account balance
    bal = acc[userIndex].balance;

    //fetch account number of current user
    accNo = acc[userIndex].accountNumber;

    //increase account balance by entered amount
    acc[userIndex].balance += amt;

    //fetch the required filename and store it in fileName
    getFileName(&fileName[0],accNo);

    //open required file in append mode
    fp=fopen(fileName,"a");

    //add the deposit made to transaction history
    fprintf(fp,"\n%d\t%d\t0\t%d",bal,amt,acc[userIndex].balance);

    //print account balance
    printf("Transaction Successful!!\nYour Account Balance is %d\n",acc[userIndex].balance);

    //close the file to save changes
    fclose(fp);
}



//used to transfer amount from current account to another account
void transferFund()
{
    FILE *fp;
    char fileName[30]="",recFileName[30]="";
    int recAccNo,recUserIndex=-1,i,tamt,bal,recBal;

    //fetch balance of sender's account 
    bal = acc[userIndex].balance;

    //prompt user to enter reciever's account number
    printf("Reciever's Account No:");
    scanf("%d",&recAccNo);

    //search for reciever's account number
    for(i=0;i<dataCount;i++)
    {
        if (acc[i].accountNumber == recAccNo)
        {
            //if account is found the index of record is stored in recUserIndex 
            recUserIndex=i;
            break;
        }
    }
    //if account is found, recUserIndex will have a non negative value 
    if (recUserIndex >= 0)
    {
        //fetch balance of reciever's account 
        recBal = acc[recUserIndex].balance;

        //prompt the user to enter transfer amount 
        printf("Trasfer Amount:");
        scanf("%d",&tamt);

        //reduce sender's balance 
        acc[userIndex].balance -= tamt;

        //add transaction to sender's transaction history
        getFileName(&fileName[0],acc[userIndex].accountNumber);
        fp=fopen(fileName,"a");
        fprintf(fp,"\n%d\t0\t%d\t%d",bal,tamt,acc[userIndex].balance);
        fclose(fp);

        //increase reciever's balance
        acc[recUserIndex].balance += tamt;

        //add transaction to sender's transaction history
        getFileName(&recFileName[0],acc[recUserIndex].accountNumber);
        fp=fopen(recFileName,"a");
        fprintf(fp,"\n%d\t%d\t0\t%d",recBal,tamt,acc[recUserIndex].balance);
        fclose(fp);

        //print success message
        printf("Trasfer Successfull!\nYour Account Balance is %d\n",acc[userIndex].balance);
    }
    //if account is not found, recUserIndex will have a negative value 
    else
    {
        printf("Invalid Account No!\n");
    }
}



//changes the pin of given user
void changePIN()
{
    int oPin,nPin1,nPin2;

    //prompt user to re-enter existing pin
    printf("Re-Enter your existing PIN:");
    scanf("%d",&oPin);

    //check whether the entered pin matches the original pin
    if(oPin==acc[userIndex].pin)
    {
        //prompt user to enter pin twice
        printf("Enter New PIN:");
        scanf("%d",&nPin1);
        printf("Re-Enter New PIN:");
        scanf("%d",&nPin2);

        
        if(nPin1==nPin2)
        {
            //if both the pin matches, we update the pin in the structure
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



//returns the number of digits in number sent as parameter
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


//generates spaces according to the number of digits
void spaceGen(char* st,int x)
{
    int k;
    for(k=0;k<9-digitCount(x);k++)
    {
        strcat(st," ");
    }
}


//converts a string to integer and returns it
int strToInt(char *st)
{
    int x=0,i=0,a;
    while(st[i]!='\0')
    {
        //gives the ascii value of respective character
        a=(int)st[i];

        //check whether the character is a number or not
        if(a>=48 && a<=57)
        {
            //convert the char into number
            x=(x*10)+(a-48);
            i++;
        }
        else
        {
            //if it gets a non numeric character, -1 is returned
            x=-1;
            break;
        }
    }
    return(x);
}

//converts a given integer to string and stores it in given address
void intToStr(char* st,int n)
{
    int arr[6],r,c=0,d=0,i;
    
    //extracting digits in reverse order
    while(n>0)
    {
        r=n%10;
        n=n/10;
        arr[c]=r;
        c++;
    }

    //storing digits in string format 
    for(i=c-1;i>=0;i--)
    {
        st[d]=(char)arr[i]+48;
        d++;
    }
}