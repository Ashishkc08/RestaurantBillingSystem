#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[30];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t  Restaurant Billing System");
    printf("\n\t    -----------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("--------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[50], int qty, float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty * price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total - dis;
    float cgst = 0.09*netTotal, grandTotal = netTotal + 2*cgst;
    printf("--------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10&s\t\t\t%.2f", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST\t\t\t%.2f", cgst);
    printf("\nSGST\t\t\t%.2f", cgst);
    printf("\n--------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------------\n");
}

int main(){

    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y';
    char contFlag = 'y';
    char name[50];
    FILE *fp;

    while (contFlag =='y'){
    
    float total=0;
    int invoiceFound = 0;

    printf("\t============Billing System============");
    printf("\n\nPlease select your prefered operation:\t");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");
    printf("\n\nYour choice:\t");
    scanf("%d",&opt);

    fgetc(stdin);
    switch (opt)
    {
    case 1:
        system("cls");
        printf("\nPlease enter a name of a customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0; // To remove new line at end of string
        strcpy(ord.date,__DATE__);
        printf("\nEnter number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;

        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter item %d\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
            printf("Please enter the quatity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }
        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice[y/n]:\t");
        scanf("%s",&saveBill);
    
        if(saveBill=='y'){
        fp = fopen("RestaurantBill.txt","a+");
        fwrite(&ord,sizeof(struct orders),1,fp);

        if(fwrite!=0)
        printf("\nSuccessfully Saved");
        else
        printf("\nError in Saving");
        fclose(fp);
    }
    break;

    case 2:
        system("cls");
        fp = fopen("RestaurantBill.txt","r");
        printf("\n  *******Your previous invoices*******\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i=0; i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;
        
    case 3:
        
        printf("\nEnter the name of customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;
        system("cls");
        fp = fopen("RestaurantBill.txt","r");
        printf("\n  *******Invoice of %s*******\n",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
                generateBillHeader(order.customer,order.date);
                for(int i=0; i<order.numOfItems;i++){
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
                invoiceFound = 1;
            }
            if(!invoiceFound){
                printf("Sorry Invoice for customer %s doesnot exist",name);
            }
        }
        fclose(fp);
        break;

        case 4:
            printf("\n\t\tThank You :)");
            exit(0);
            break;

        default:
            printf("Invalid Option");
            break;


    }
    printf("\nDo you want to perform another operation[y/n]?");
    scanf("%s",&contFlag);
    }
    
    
}