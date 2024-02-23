#include <stdio.h>
#include <stdlib.h>


struct customer{
    int id;
    char name[25];
    char surname[25];
    double balance;
};


FILE *fp;
FILE *backup;

struct customer customer;
struct customer emptyCustomer = {0, "", "", 0.0};


void print(){
    fp = fopen("atm.txt", "r+");
    if(fp == NULL){
        printf("File cannot be opened.");
    }
    printf("ID\tName\tSurname\tBalance\n");
    while(!feof(fp)){
        fread(&customer, sizeof(struct customer), 1, fp);
        printf("%d\t%s\t%s\t%.2lf\n", customer.id, customer.name, customer.surname, customer.balance);
    }
    fclose(fp);
}


void update(){
    fp = fopen("atm.txt", "r+");
    if(fp == NULL){
        printf("File cannot be opened.");
    }
    int customerID;
    printf("\nEnter customer ID to update:");
    scanf("%d", &customerID);
    fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
    fread(&customer, sizeof(struct customer), 1, fp);
    if(customer.id != 0){
        printf("\nCustomer exists, updating...");
        fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
        printf("\n****Customer Information to Update****\n");
        printf("ID:%d\n", customerID);
        printf("Name:%s\n", customer.name);
        printf("Surname:%s\n", customer.surname);
        printf("Balance:%.2lf\n", customer.balance);
        printf("***********************");
        printf("1-Increase Balance\n");
        printf("2-Decrease Balance\n");
        printf("Choice:");
        int choice;
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter amount:");
                double amount;
                scanf("%lf", &amount);
                customer.balance += amount;
                fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
                fwrite(&customer, sizeof(struct customer), 1, fp);
                printf("\nUpdate successful!");
                printf("\nUpdated balance:%.2lf", customer.balance);
                break;
            case 2:
                printf("Enter amount:");
                double negativeAmount;
                scanf("%lf", &negativeAmount);
                customer.balance -= negativeAmount;
                fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
                fwrite(&customer, sizeof(struct customer), 1, fp);
                printf("\nUpdate successful!");
                printf("\nUpdated balance:%.2lf", customer.balance);
                break;
            default:
                printf("Invalid choice, try again.");
                break;
        }
    }
    fclose(fp);
}
void backUp(){
    fp = fopen("atm.txt", "r+");
    backup = fopen("atmBackup.txt", "a");
    if(fp == NULL && backup == NULL){
        printf("File cannot be opened.");
    }
    while(!feof(fp)){
        fread(&customer, sizeof(struct customer), 1, fp);
        fprintf(backup, "%d %s %s %.2lf", customer.id, customer.name, customer.surname, customer.balance);
    }
    printf("\nBackup successful.");
    fclose(fp);
    fclose(backup);
}


void delete(){
    fp = fopen("atm.txt", "r+");
    if(fp == NULL){
        printf("File cannot be opened.");
    }
    int customerID;
    printf("\nEnter customer ID to delete:");
    scanf("%d", &customerID);
    fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
    fread(&customer, sizeof(struct customer), 1, fp);
    if(customer.id != 0){
        printf("\nDeleting customer from system.");
        fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
        fwrite(&emptyCustomer, sizeof(struct customer), 1, fp);
        printf("\nCustomer successfully deleted.");
    }
    else{
        printf("Customer does not exist in the system.");
    }
    fclose(fp);
}

void add(){
    fp = fopen("atm.txt", "r+");
    if(fp == NULL){
        printf("File cannot be opened.");
    }

    printf("\nEnter customer ID:");
    int customerID;
    scanf("%d", &customerID);
    fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
    fread(&customer, sizeof(struct customer), 1, fp);
    if(customer.id != 0){
        printf("Customer with this ID already exists.");
    }
    else{
        customer.id = customerID;
        printf("Customer name, surname:");
        scanf("%s %s", customer.name, customer.surname);
        printf("Balance:");
        scanf("%lf", &customer.balance);
        fseek(fp, (customerID - 1) * sizeof(customer), SEEK_SET);
        fwrite(&customer, sizeof(struct customer), 1, fp);
        printf("Customer with ID %d saved.", customerID);
    }
    fclose(fp);
}


void createList(){
    fp = fopen("atm.txt", "w");
    if(fp == NULL){
        printf("File cannot be opened.\n");
        exit(0);
    }
    for(int i = 0; i < 100; i++){
        fwrite(&emptyCustomer, sizeof(struct customer), 1, fp);
    }
    printf("Space allocated for 100 customers.");
    fclose(fp);
}


int main(){

while(1){

int choice;
printf("1-Add Customer\n");
printf("2-List Customers\n");
printf("3-Delete Customer\n");
printf("4-Backup Program\n");
printf("5-Update Customer\n");
printf("6-Create List (Reset)\n");
printf("0-Exit\n");
printf("Your choice:");
scanf("%d", &choice);
if(choice != 0){
    switch (choice){

    case 1:system("cls");
    add();
    break;
    case 2:system("cls");
    print();
    break;
    case 3:system("cls");
    delete();
    break;
    case 4:system("cls");
    backUp();
    break;
    case 5:system("cls");
    update();
    break;
    case 6:system("cls");
    createList();
    break;
    default:system("cls");
    printf("Invalid choice.");

}
}

}
return 0;
}
