#include <stdio.h>
#include <string.h>
void menu(int *select);
void customer(char code[][3], char fname[][20], char lname[][20], int age[],int *cnt);
void printcustomer(char code[][3], char fname[][20], char lname[][20], int age[], int cnt);
void eggprice(float price[]);
void order(char fname[][20], char lname[][20], int age[], int pos, int piece[]);
int search(char code[][3], int cnt);
void calculate(int piece[], float price[], float toegg[], float *total);
char printorder(float toegg[], float total);
void ordertextfile(char code[][3], char fname[][20], char lname[][20], int age[], float price[], int piece[], float total, int pos, float toegg[]);

int main()
{
	int age[20], cnt=0, pos, select=1, piece[8];
	char code[20][3], fname[20][20], lname[20][20], exit='N', print; 
	float price[8], toegg[8], total;
	
	while (select != 0)
	{
		menu(&select);
		if (select == 1)
			customer(code, fname, lname, age, &cnt);
		else if (select == 2)		
			eggprice(price);					
		else if (select == 3)
		{
			pos = search(code, cnt);
			order(fname, lname, age, pos, piece);
			calculate(piece, price, toegg, &total);
			print = printorder(toegg, total);
			if (toupper(print) == 'Y')
				ordertextfile (code, fname, lname, age, price, piece, total, pos, toegg);	 
		}
		else if (select == 4)
			printcustomer(code, fname, lname, age, cnt);
		else if (select == 0)
			printf("Thank you, See you again.\n");
		else
			printf("Invalid code please try again.\n");	
	}
	return 0;
}

void menu(int *select)
{
	printf("---------------Menu---------------\n");
	printf("[1]Enter details of customer\n");
	printf("[2]Enter price of eggs\n");
	printf("[3]Enter your orders\n");
	printf("[4]Print details of customer to .txt file\n");
	printf("[0]Exit program\n");
	printf("----------------------------------\n");
	printf("Select menu : ");
	scanf("%d",&*select);	
}



void customer(char code[][3], char fname[][20], char lname[][20], int age[],int *cnt)
{
	int i;
	printf("---------------Input details of customer---------------\n");
	printf("Enter number of customer : ");
	scanf("%d",&*cnt);
	for(i=0; i<*cnt; i++)
	{
		printf("----------Customer #%d----------\n",i+1);
		printf("Enter code (00-20): ");
		scanf("%s",&code[i]);
		printf("Enter first name : ");
		scanf("%s",&fname[i]);
		printf("Enter last name : ");
		scanf("%s",&lname[i]);
		printf("Age : ");
		scanf("%d",&age[i]);	
	}
	
}

void printcustomer(char code[][3], char fname[][20], char lname[][20], int age[], int cnt)
{
	int i;
	FILE *out;
	out = fopen("customer.txt","w");
	for(i=0; i<cnt; i++)
	{				
		fprintf(out,"Code : %s Name : %-20s %-20s Age : %-2d\n",code[i], fname[i], lname[i], age[i]);
	}
	fprintf(out,"Total of customer = %d\n",cnt);
	printf("----------Print to .txt file----------\n");
	printf("Successful, please cheack your .txt file\n");
	fclose(out);
}

void eggprice(float price[])
{
	int i;
	printf("----------Eggs price----------\n");
	for(i=0; i<7; i++)
	{		
		printf("Enter price eggs number %d (x.xx): ",i);
		scanf("%f",&price[i]);		
	}
}

int search(char code[][3], int cnt)
{
	int i=0, found, pos;
	char target[3];
	found=0;
	printf("Code of customer (00-20) : ");
	scanf("%s",&target);
	while((i<cnt) && (!found))
 	{
	 
		if(strcmp(target,code[i]) == 0)
		{
			pos = i;
			found = 1;
		}
		i++;
	}
	return (pos);
}

void order(char fname[][20], char lname[][20], int age[], int pos, int piece[])
{
	int i;
	printf("Name : %s %s Age : %d\n",fname[pos], lname[pos], age[pos]);
	printf("----------Order----------\n");
	for(i=0; i<7; i++)
	{		
		printf("Enter eggs number %d : ",i);
		scanf("%d",&piece[i]);		
	}
}

void calculate(int piece[], float price[], float toegg[], float *total)
{
	int i;
	for(i=0; i<7; i++)
	{	
		toegg[i] = 	piece[i] * price[i];
		(*total) = (*total) + toegg[i];
	}	
}
char printorder(float toegg[], float total)
{
	int i;
	char print;
	printf("----------------------------\n");
	for(i=0; i<7; i++)
	{		
		printf("Eggs number %d : %.2f bath\n",i ,toegg[i]);		
	}
	printf("----------------------------\n");
	printf("Total price : %.2f bath\n",total);
	printf("----------------------------\n");
	printf("Do you want to print order to .txt file? [Y,N] : ");
	scanf(" %c",&print);
	return (print);
}

void ordertextfile(char code[][3], char fname[][20], char lname[][20], int age[], float price[], int piece[], float total, int pos, float toegg[])
{
	int i;
	FILE *out2;
	out2 = fopen("order.txt","w");
	fprintf(out2,"Code : %s Name : %s %s Age : %d\n",code[pos] ,fname[pos], lname[pos], age[pos]);
	fprintf(out2,"-----------------Your order---------------\n");
	for(i=0; i<7; i++)
	{		
		fprintf(out2,"Eggs number %d : %d x %.2f = %.2f bath\n",i ,piece[i] , price[i] ,toegg[i]);		
	}
	fprintf(out2,"----------------------------\n");
	fprintf(out2,"Total price : %.2f bath\n",total);
}




