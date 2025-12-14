#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    int acc_no;
    char name[60], address[60], acc_type[10];
    int age;
    float balance;
};

struct Node
{
    struct Account account;
    struct Node *next;
};

void menu();
void createAccount();
void viewAccounts();
void depositMoney();
void withdrawMoney();
void exitProgram();
void saveAccountsToFile();
void loadAccountsFromFile();
int login();

struct Node *head = NULL;

int main()
{
    if (!login()) return 0;
    printf("\n=====================================\n");
     printf("   Welcome to the NIGGA Banking System!  \n=====================================\n");
    loadAccountsFromFile();
    menu();
    return 0;
}

int login()
{
    char password[10];
    printf("\n=====================================\nLogin System\n=====================================\n");
    while (1)
    {
        printf("Enter system password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;
        if (strcmp(password, "2850") == 0) return 1;
        printf("\n=====================================\nWrong password\nPlease enter correct password\n=====================================\n");
    }
}

void menu()
{
    int choice;
    while (1)
    {
        printf("\n=====================================\nMain Menu\n=====================================\n");
        printf("1. Create a new account\n2. View all accounts\n3. Deposit money\n4. Withdraw money\n5. Exit\n=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: createAccount(); break;
        case 2: viewAccounts(); break;
        case 3: depositMoney(); break;
        case 4: withdrawMoney(); break;
        case 5: exitProgram(); return;
        default: printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void createAccount()
{
    struct Account newAccount;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (!newNode) { printf("\nMemory allocation failed!\n"); return; }

    printf("\n=====================================\nCreate New Account\n=====================================\n");
    printf("Enter account number: ");
    while (scanf("%d", &newAccount.acc_no) != 1) { printf("Invalid input. Enter integer: "); while (getchar() != '\n'); }

    struct Node *current = head;
    while (current)
    {
        if (current->account.acc_no == newAccount.acc_no) { printf("Account number already exists.\n"); return; }
        current = current->next;
    }

    printf("Enter name: ");
    while (getchar() != '\n');
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = 0;

    printf("Enter age: ");
    while (scanf("%d", &newAccount.age) != 1) { printf("Invalid input. Enter integer: "); while (getchar() != '\n'); }

    printf("Enter address: ");
    while (getchar() != '\n');
    fgets(newAccount.address, sizeof(newAccount.address), stdin);
    newAccount.address[strcspn(newAccount.address, "\n")] = 0;

    printf("Enter account type (Saving/Current): ");
    scanf("%s", newAccount.acc_type);

    printf("Enter initial deposit: ");
    while (scanf("%f", &newAccount.balance) != 1) { printf("Invalid input. Enter a valid amount: "); while (getchar() != '\n'); }

    newNode->account = newAccount;
    newNode->next = head;
    head = newNode;

    saveAccountsToFile();
    printf("\nAccount created successfully!\n");
}

void viewAccounts()
{
    struct Node *current = head;
    printf("\n=====================================\nAccount List\n=====================================\n");
    if (!current) { printf("No accounts found.\n"); return; }
    while (current)
    {
        printf("Account No: %d, Name: %s, Balance: $%.2f\n", current->account.acc_no, current->account.name, current->account.balance);
        current = current->next;
    }
}

void depositMoney()
{
    int acc_no;
    float amount;
    struct Node *current = head;
    printf("\n=====================================\nDeposit Money\n=====================================\n");
    printf("Enter account number: ");
    scanf("%d", &acc_no);
    while (current)
    {
        if (current->account.acc_no == acc_no)
        {
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            current->account.balance += amount;
            saveAccountsToFile();
            printf("\nDeposit successful! New balance: $%.2f\n", current->account.balance);
            return;
        }
        current = current->next;
    }
    printf("\nAccount not found!\n");
}

void withdrawMoney()
{
    int acc_no;
    float amount;
    struct Node *current = head;
    printf("\n=====================================\nWithdraw Money\n=====================================\n");
    printf("Enter account number: ");
    scanf("%d", &acc_no);
    while (current)
    {
        if (current->account.acc_no == acc_no)
        {
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);
            if (amount > current->account.balance) { printf("\nInsufficient balance!\n"); }
            else
            {
                current->account.balance -= amount;
                saveAccountsToFile();
                printf("\nWithdrawal successful! New balance: $%.2f\n", current->account.balance);
            }
            return;
        }
        current = current->next;
    }
    printf("\nAccount not found!\n");
}

void saveAccountsToFile()
{
    FILE *file = fopen("accounts.dat", "wb");
    if (!file) { printf("\nError saving accounts to file.\n"); return; }
    struct Node *current = head;
    while (current)
    {
        fwrite(&current->account, sizeof(struct Account), 1, file);
        current = current->next;
    }
    fclose(file);
}

void loadAccountsFromFile()
{
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) return;
    struct Account account;
    while (fread(&account, sizeof(struct Account), 1, file))
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (!newNode) { printf("\nMemory allocation failed!\n"); fclose(file); return; }
        newNode->account = account;
        newNode->next = head;
        head = newNode;
    }
    fclose(file);
}

void exitProgram()
{
    struct Node *current = head;
    struct Node *temp;
    printf("\n=====================================\nThank you for using our banking system!\n=====================================\n");
    while (current)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}