#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();
void displayAccount(struct Account acc);

int main() {
    int choice;

    do {
        printf("\n========================================");
        printf("\n       BANK ACCOUNT MANAGEMENT SYSTEM");
        printf("\n========================================");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\n========================================");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                printf("\nThank you for using our banking system!");
                break;

            default:
                printf("\nInvalid choice! Please try again.");
        }

    } while (choice != 5);

    return 0;
}


void createAccount() {

    struct Account acc;
    FILE *fp;

    printf("\n----------- CREATE ACCOUNT -----------");

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 0) {
        printf("\nInitial balance cannot be negative.");
        return;
    }

    fp = fopen("accounts.dat", "ab");

    if (fp == NULL) {
        printf("\nUnable to open file.");
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!");
}
void deposit() {

    struct Account acc;
    FILE *fp;
    int accountNo;
    float amount;
    int found = 0;

    printf("\n----------- DEPOSIT MONEY -----------");

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL) {
        printf("\nNo account records found.");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            printf("Account Holder: %s", acc.name);

            printf("\nEnter Amount to Deposit: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("\nInvalid amount.");
                fclose(fp);
                return;
            }

            acc.balance = acc.balance + amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nDeposit successful!");
            printf("\nUpdated Balance: %.2f", acc.balance);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nAccount not found.");
    }
}

void withdraw() {

    struct Account acc;
    FILE *fp;
    int accountNo;
    float amount;
    int found = 0;

    printf("\n----------- WITHDRAW MONEY -----------");

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL) {
        printf("\nNo account records found.");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {

            printf("Account Holder: %s", acc.name);

            printf("\nCurrent Balance: %.2f", acc.balance);

            printf("\nEnter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("\nInvalid amount.");
                fclose(fp);
                return;
            }

            if (amount > acc.balance) {
                printf("\nInsufficient balance!");
                fclose(fp);
                return;
            }

            acc.balance = acc.balance - amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nWithdrawal successful!");
            printf("\nRemaining Balance: %.2f", acc.balance);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nAccount not found.");
    }
}
void balanceEnquiry() {

    struct Account acc;
    FILE *fp;
    int accountNo;
    int found = 0;

    printf("\n----------- BALANCE ENQUIRY -----------");

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNo);

    fp = fopen("accounts.dat", "rb");

    if (fp == NULL) {
        printf("\nNo account records found.");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {

        if (acc.accountNo == accountNo) {
            displayAccount(acc);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nAccount not found.");
    }
}
void displayAccount(struct Account acc) {

    printf("\n--------------------------------------");
    printf("\n          ACCOUNT DETAILS");
    printf("\n--------------------------------------");
    printf("\nAccount Number : %d", acc.accountNo);
    printf("\nAccount Holder : %s", acc.name);
    printf("\nBalance        : %.2f", acc.balance);
    printf("\n--------------------------------------");
}
