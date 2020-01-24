/*Name: Joshua Marsh (006689196)
 *Date: 1/14/2020
 Assignment: Checking Account Lab
 Compiler: Microsoft Visual Studios
 OS: Windows 10 pro 64 bit*/

/* $3.00 per month to maintain account
0.06 for each check cashed
0.03 for each deposit made
5.00 overdraft whenever a checked cashed leaves balance below zero.*/


#include <stdio.h>
#include <stdlib.h>

void outputHeaders(void);
void initialBalance(double amount, double* balance, double* service, double* openBalance);
void deposit(double amount, double* balance, double* service, int* numDeposit, double* amtDeposit);
void check(double amount, double* balance, double* service, int* numCheck, double* amtCheck);
void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance);

FILE *fpIn, *fpOut;

/*Main function provided*/
int main(void) {
    char code;
    double amount, service, balance;
    double amtCheck, amtDeposit, openBalance, closeBalance;
    int numCheck, numDeposit;

    fopen_s(&fpIn, "account.txt", "r");
    if (fpIn == NULL) {
        printf("account.txt could not be opened for input.");
        exit(1);
    }
    fopen_s(&fpOut, "csis.txt", "w");
    if (fpOut == NULL) {
        printf("csis.text could not be opened for output");
        exit(1);
    }

    amount = 0.0;
    service = 0.0;
    balance = 0.0;
    amtCheck = 0.0;
    amtDeposit = 0.0;
    openBalance = 0.0;
    closeBalance = 0.0;
    numCheck = 0;
    numDeposit = 0;

    outputHeaders();

    while (!feof(fpIn)) {
        fscanf_s(fpIn, "%c %lf\n", &code, 1, &amount);
        if (code == 'I') {
            initialBalance(amount, &balance, &service, &openBalance);
        }
        else if (code == 'D') {
            deposit(amount, &balance, &service, &numDeposit, &amtDeposit);
        }
        else {
            check(amount, &balance, &service, &numCheck, &amtCheck);
        }
    }

    closeBalance = balance - service;

    outputSummary(numDeposit, amtDeposit, numCheck, amtCheck, openBalance, service, closeBalance);

    fclose(fpIn);
    fclose(fpOut);
    return 0;
}

void outputHeaders(void) {
    /*Writes header and dashes to begin monthly bank statement.*/
    int i;

    printf("%s%16s%12s%14s\n", "Transaction", "Deposit", "Check", "Balance");
    fprintf(fpOut, "%s%16s%12s%14s\n", "Transaction", "Deposit", "Check", "Balance");

    for (i = 1; i <= 11; i++) {
        printf("%c", '-');
        fprintf(fpOut, "%c", '-');
    }
    for (i = 12; i <= 20; i++) {
        printf(" ");
        fprintf(fpOut, " ");
    }
    for (i = 21; i <= 27; i++) {
        printf("%c", '-');
        fprintf(fpOut, "%c", '-');
    }
    for (i = 29; i <= 35; i++) {
        printf(" ");
        fprintf(fpOut, " ");
    }
    for (i = 36; i <= 40; i++) {
        printf("%c", '-');
        fprintf(fpOut, "%c", '-');
    }
    for (i = 42; i <= 48; i++) {
        printf(" ");
        fprintf(fpOut, " ");
    }
    for (i = 49; i <= 55; i++) {
        printf("%c", '-');
        fprintf(fpOut, "%c", '-');
    }
    printf("\n");
    fprintf(fpOut, "\n");
}

void initialBalance(double amount, double* balance, double* service, double* openBalance) {    
    /*Setup initial balance in bank statement per month and charges maintainence fee.*/
    *balance = amount;
    *openBalance = amount;    
    *service += 3;    
    printf("Initial Balance                                %.2lf\n", *balance);
    fprintf(fpOut, "Initial Balance                                %.2lf\n", *balance);
}

void deposit(double amount, double* balance, double* service, int* numDeposit, double* amtDeposit) {
    /*Keeps track of balance before and after deposit, assesses service fee per deposit
    and keeps track of the number of checks and ammount deposited to account.*/
    *balance = *balance + amount;
    *service += 0.03;
    *amtDeposit += amount;
    *numDeposit = *numDeposit + 1;
    printf("%s%20.2lf%26.2lf\n", "Deposit", amount, *balance);
    fprintf(fpOut, "%s%20.2lf%26.2lf\n", "Deposit", amount, *balance);
}

void check(double amount, double* balance, double* service, int* numCheck, double* amtCheck) {
    /*Processes check, deducts money from account, keep tracks of # of checks and issues service fees*/
    if ((*balance - amount) >= 0) {
        *balance = *balance - amount;
        
    }
    else if ((*balance - amount) < 0) {
        *balance = *balance - amount;
        *service += 5.00; /*Overdraft fee*/       
    }
    ; /*Service charge for cashing check*/
    *service += 0.06;
    *amtCheck += amount;
    *numCheck = *numCheck + 1;
    printf("%s%34.2lf%14.2lf\n", "Check", amount, *balance);
    fprintf(fpOut, "%s%34.2lf%14.2lf\n", "Check", amount, *balance);
}

void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance) {
    /*Prints account summary*/

    printf("%25s %d\n", "\n\nTotal number of deposits:", numDeposit);
    printf("%25s %.2lf\n\n", "Total amount deposited:", amtDeposit);
    printf("%25s %d\n", "Total number of checks:", numCheck);
    printf("%25s %.2lf\n\n", "Total amount checks:", amtCheck);
    printf("%25s %.2lf\n\n", "Total service charge:", service);
    printf("%25s %.2lf\n", "Opening balance:", openBalance);
    printf("%25s %.2lf\n", "Closing balance:", closeBalance);

    fprintf(fpOut, "%25s %d\n", "\n\nTotal number of deposits:", numDeposit);
    fprintf(fpOut, "%25s %.2lf\n\n", "Total amount deposited:", amtDeposit);
    fprintf(fpOut, "%25s %d\n", "Total number of checks:", numCheck);
    fprintf(fpOut, "%25s %.2lf\n\n", "Total amount checks:", amtCheck);
    fprintf(fpOut, "%25s %.2lf\n\n", "Total service charge:", service);
    fprintf(fpOut, "%25s %.2lf\n", "Opening balance:", openBalance);
    fprintf(fpOut, "%25s %.2lf\n", "Closing balance:", closeBalance);

}
