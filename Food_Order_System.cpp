/*
CPT111 - Principles of Programming
Assignment 2 - Food Ordering System

Name: Ling Shao Doo
Matri no: 153152
Lecturer: Madam Maziani
*/

//hearder file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;

//self-defined function prototype
void showMenu(string[], float[], int[], int*);
float order(string[], float[], int[], string[], float[], int[], int*);
void calPrice(float);
int mainMenu();
void makePayment();
void aboutProgram();
void manager(string[], float[], int[], int*);
void updateMenu(string [], float[], int[], int*);

//main function
int main()
{
	//variables declaration
	string food[100];
	float price[100];
	int stock[100];	
	string cfood[100];
	float cprice[100];
	int cstock[100];	
	int choice, last = 1;
	float totalPrice;
		
	choice = mainMenu();
	
	system("cls");
	showMenu(food, price, stock, &last);
	
	if(choice == 1)
	{
		//customer part		
		totalPrice = order(food, price, stock, 
		cfood, cprice, cstock, &last);
		calPrice(totalPrice);
		makePayment();
		updateMenu(food, price, stock, &last);	
	}
	else if(choice == 2)
	{
		//manager part	
		cout << "*****************Latest Menu*****************" << endl
		<< endl;
		manager(food, price, stock, &last);		
	}
	else
	{
		//about this program
		system("cls");		
		aboutProgram();
	}
		
	return 0;
}

//list of user-defined functions
int mainMenu()
{
	//variable declaration
	int choice;
	
	//display the main menu
	cout << "WELCOME TO AHDOO'S RESTAURANT" << endl << endl;
	cout << "1. Customer section" << endl;
	cout << "2. Restaurant manager" << endl;
	cout << "3. About this program" << endl;
	
	cout << "\nEnter your choice (number): ";
	cin >> choice;
	
	//input validation
	while(choice < 1 || choice > 3)
	{
		cout << "Invalid input. Please try again ya." << endl;
		cout << "\nEnter your choice: ";
		cin >> choice;	
	}
	
	return choice;
}

void showMenu(string food[], float price[], int stock[], int *last)
{
	//open menu file in input mode
	ifstream menu;
	menu.open("menu.txt");	
	
	//variable declaration
	int count;
	
	cout << "No.\tPrice(RM)\tStock\tFood" << endl;
	
	//read data from menu file
	while(menu >> count)
	{	
		*last = count;
		getline(menu, food[count],'\t');
		menu >> price[count];
		menu >> stock[count];
		
		//display food menu			
		cout << showpoint << fixed << setprecision(2);
		cout << count << "\t" << price[count] << "\t\t" << stock[count] << "\t" << food[count] << endl;		
	}
	
	//close menu file
	menu.close();
}

float order(string food[], float price[], int stock[], string cfood[], float cprice[], int cstock[], int *last)
{
	//open order file in output mode
	ofstream file;
	file.open("order.txt", ios::app);
	
	//open sale file in output mode
	ofstream outFile;
	outFile.open("sale.txt", ios::out|ios::app);
	
	//variables declaration
	int c, again, totalFood = 0, i = 1, totalItem = 0;
	float total, totalPrice = 0;
	
	//customer orders food
	cout << "\nEnter the No. of food that you wish to purchase:";
	cin >> c;
	
	//input validation
	while(c > *last || c <= 0)
	{
		cout << "Invalid input. Please try again ya." << endl;	
		cout << "\nEnter the No. of food that you wish to purchase:";
		cin >> c;
	}
	
	cfood[i] = food[c];
	cprice[i] = price[c];
	
	cout << "Enter the quantity: ";
	cin >> cstock[i];
	
	//not enough stock
	while (cstock[i] > stock[c])
	{
		cout << "We dont have enough stock right now Please select others food." << endl;
		cout << "\nEnter another No. of food that you wish to purchase:";
		cin >> c;
		
		//input validation
		while(c > *last || c <= 0)
		{
			cout << "Invalid input. Please try again ya." << endl;	
			cout << "\nEnter the No. of food that you wish to purchase:";
			cin >> c;
		}
	
		cfood[i] = food[c];
		cprice[i] = price[c];
	
		cout << "Enter the quantity: ";
		cin >> cstock[i];			
	}	
		totalFood += cstock[i];
		stock[c] -= cstock[i];
		totalPrice += (cstock[i]*cprice[i]);
		++i;	
	
	//ask user want to add more food or not
	cout << "\n\tPress 1 to continue order" << endl;
	cout << "\tPress 2 to check the total" << endl;
	cout << "\tEnter your choice: ";
	cin >> again;
	
	//input validation
	while(again != 1 && again != 2)
	{
		cout << "\n\tInvalid input. Please try again ya." << endl;
		cout << "\n\tPress 1 to continue order" << endl;
		cout << "\tPress 2 to check the total" << endl;
		cout << "\tEnter your choice: ";
		cin >> again;	
	}
	//if user want to add another food	
	while (again == 1)
	{
		cout << "\nEnter the No. of food that you wish to purchase:";
		cin >> c;
	
		while(c > *last || c <= 0)
		{
			cout << "Invalid input. Please try again ya." << endl;	
			cout << "Enter the No. of food that you wish to purchase:";
			cin >> c;
		}
	
		cfood[i] = food[c];
		cprice[i] = price[c];
		
		//ask user quantity of food	
		cout << "Enter the quantity: ";
		cin >> cstock[i];
	
		//not enough stock
		while (cstock[i] > stock[c])
		{
			cout << "\nWe dont have enough stock right now Please select others food." << endl;
			cout << "\nEnter another No. of food that you wish to purchase:";
			cin >> c;
		
			//input validation
			while(c > *last || c <= 0)
			{
				cout << "Invalid input. Please try again ya." << endl;	
				cout << "Enter the No. of food that you wish to purchase:";
				cin >> c;
			}
	
			cfood[i] = food[c];
			cprice[i] = price[c];
			
			//ask user quantity of food	
			cout << "Enter the quantity: ";
			cin >> cstock[i];			
		}	
			totalFood += cstock[i];
			stock[c] -= cstock[i];
			totalPrice += (cstock[i]*cprice[i]);
			++i;
	
		//ask user want to add more food or not
		cout << "\n\tPress 1 to continue order" << endl;
		cout << "\tPress 2 to check the total" << endl;
		cout << "\tEnter your choice: ";
		cin >> again;
	
		//input validation
		while(again != 1 && again != 2)
		{
			cout << "\n\tInvalid input. Please try again ya." << endl;
			cout << "\n\tPress 1 to continue order" << endl;
			cout << "\tPress 2 to check the total" << endl;
			cout << "\tEnter your choice: ";
			cin >> again;			
		}
	}
	
	//print data to detail file
	file << "\nNew Order " << endl;
	for (int a = 1; a < i; ++a)
	{
		file << cstock[a] << " x " << cfood[a] << endl;
	}
	
	//close detail file
	file.close();
	
	system("cls");
	for (int a = 1; a < i; ++a)
	{
		totalItem += cstock[a];
		cout << cstock[a] << " x " << cfood[a] << endl;
	}
	
	//print sale to sale file	
	outFile  << endl << totalItem << " food(s) " << "total: " << (totalPrice*1.06)+5;
	
	//close sale file
	outFile.close();
	
	return totalPrice;
}

void calPrice(float totalPrice)
{
	//formatting the output to become more readable
	cout << fixed << setprecision(2);
	cout << "\nSubtotal\t\t\tRM" << totalPrice << endl;
	cout << "Incl. Tax\t\t\tRM" << totalPrice*0.06 << endl;
	cout << "Delivery fee\t\t\tRM" << 5.00 << endl;
	cout << "Total(incl. tax)\t\tRM" << (totalPrice*1.06)+5 << endl;
}

void makePayment()
{
	cout << "\nPress any key to make payment";	
	if(getch())
	{
		system("cls");	
		int payment;
	
		cout << "1. Credit/Debit Card" << endl;
		cout << "2. Online Banking" << endl;
		cout << "3. Cash on Deliver" << endl <<endl;
	
		cout << "Enter one payment method: ";
		cin >> payment;
	
		//input validation
		while(payment > 3 || payment < 0)
		{
			cout << "Invalid input. Please try again ya." << endl;
			cout << "\nEnter one payment method: ";
			cin >> payment;		
		}
	
		if(payment == 1)
		{
			//variables declaration
			unsigned long long int card;
			int cvv, date, otp;
		
			system("cls");	
			cout << "Card Number: ";
			cin >> card;
			
			//input validation
			while(card > 9999999999999999 || card < 100000000000000)
			{
				cout << "Invalid input. Please try again." << endl;
				cout << "Card Number: ";
				cin >> card;
			}
			cout << "CVV: ";
			cin >> cvv;	
			
			//input validation
			while (cvv > 999 || cvv < 100)
			{
				cout << "Invalid input. Please try again." << endl;
				cout << "CVV: ";
				cin >> cvv;		
			}					
			cout << "\nWe have send a OTP to your phone number 012-XXXX XXXX." << endl;
			cout << "OTP: ";
			cin >> otp;
			while(otp < 0 || otp > 999999)
			{
				cout << "Invalid input. Please try again" << endl;
				cout << "OTP: ";
				cin >> otp;
			}		
		
			system("cls");
			cout << "Congratulation!We have received your payment "
			<< "and the chef will preparing your meal(s)." << endl;
	}
	
	else if(payment == 2)
	{
		system("cls");
		
		//variable declaration
		int bank, acc;
		string password, username;
		char YN;
		
		//display choice of banks		
		cout << "No\tBank" << endl;
		cout << "1	ABC Bank" << endl;
		cout << "2	USM Bank" << endl;	
		cout << "3	TYW Bank" << endl;
		cout << "4	LSD Bank" << endl;
		
		cout << "\nEnter the No of Bank: ";
		cin >> bank;
		
		//input validation
		while(bank < 1 || bank > 4)
		{
			cout << "Invalid input. Please try again ya." << endl;
			cout << "\nEnter the No of Bank: ";
			cin >> bank;			
		}		
		
		//clear the input buffer
		cin.ignore();
		
		system("cls");
		
		cout << "**************Welcome to XXX Bank**************" << endl;
		cout << "Username: ";
		getline(cin,username);
		cout << "Password: ";
		getline(cin, password);
		
		system("cls");
		
		cout << "1. Saving Account" <<endl;
		cout << "2. Current Account" << endl << endl;
		cout << "Enter your no. for type of account: ";
		cin >> acc;
		
		//input validation
		while(acc != 1 && acc != 2)		
		{
			cout << "\nInvalid input. Please try again." << endl;
			cout << "Enter your no of account: ";
			cin >> acc;	
		}
		
		system("cls");
	
		cout << "Are you agree to deduct money from your account "
		<< "for AHDOO restaurant food order(Y/N): ";
		cin >> YN;
		
		//input validation
		while(YN != 'Y' && YN != 'y' && YN != 'N' && YN != 'n')
		{
			cout << "Invalid input. Please try again ya." << endl;
			cout << "Are you agree to deduct money from your account "
			<< "for AHDOO restaurant food order(Y/N): ";
			cin >> YN;	
		}
		
		//if user input 'Y' or 'y'
		if(YN == 'Y' || YN == 'y')
		{
			system("cls");
			cout << "Congratulation!We have received your payment "
			<< "and the chef will preparing your meal(s)." << endl;	
		}
		
		//if user input 'N' or 'n'
		else if(YN == 'N' || YN == 'n')
		{	
			system("cls");
			cout << "Sorry. We unable to process your order. "
			<< "Please try again later ya." << endl;
		}		
	}
	
	else if(payment == 3)
	{
		system("cls");
		cout << "Congratulation!Ours chef will preparing your meal(s)." << endl; 
		cout << "Please prepare a sufficient amount of money to our rider." << endl;
		cout << "Thank you" << endl;		
	}
	}
}

void updateMenu(string food[], float price[], int stock[], int *last)
{
	//open menu file in output mode
	ofstream menu;
	menu.open("menu.txt");
	
	//update menu
	for(int i = 1; i <= *last; ++i)
	{
		menu << i << food[i] << "\t" << price[i] << "\t" << stock[i] << endl;
	}
	
	menu.close();
}

void aboutProgram()
{
	cout << "Hello, I am Ling Shao Doo, the programmer of this program." << endl;
	cout << "First at all, I want to thanks Madam Maziani for "
	<< "helping me in this program." << endl;
	cout << "I designed the program in order to help " 
	<< "the customer and restaurant manager in Food Order System." << endl;
	cout << "I hope you enjoy using my Food Order System." << endl;
	cout << "If you have any problems, please feel free to contact me. "<< "Thank you." << endl;		
}

void manager(string food[], float price[], int stock[], int *last)
{
	//variables declaration
	int choice;
	float total;

	//display the manager selections
	cout << "1. Update menu" << endl;
	cout << "2. Accept order" << endl;
	cout << "3. Total payment per order" << endl;
	cout << "4. Estimated delivery time" << endl;
	cout << "5. Total sale for today" << endl;
	
	cout << "\nEnter your choice: ";
	cin >> choice;
	
	//input validation
	while(choice > 5 || choice <= 0)
	{
		cout << "Invalid input. Please try again ya." << endl;
		cout << "\nEnter your choice: ";
		cin >> choice;	
	}
	
	//open sale file in input mode
	ifstream file;
	file.open("sale.txt");
	
	//variables declaration
	string s;
	float sale[100];
	int count = 1;
	int totalItem[100];
	
	//read data from sale file
	while(!file.eof())
	{
		file >> totalItem[count];
		getline(file,s,':');
		file >> sale[count];
		++count;	
	}	
	
	//update menu
	if (choice == 1)
	{
		system("cls");
		
		int choice;		
		
		cout << "1. Add New Food" << endl;
		cout << "2. Modify Previous Food Menu" << endl << endl;
		
		cout << "Enter your choice: ";
		cin >> choice;
		
		system("cls");
		
		//input validation
		while(choice > 2 || choice < 1)
		{
			cout << "Invalid input. Please try again." << endl;
			cout << "Enter your choice: ";
			cin >> choice;		
		}
		
		//add new food
		if(choice == 1)
		{
			cout << "New Food: ";
			cin.ignore();
			getline(cin, food[*last + 1]);			
			cout << "Price(RM): ";
			cin >> price[*last + 1];
			cout << "Stock: ";
			cin >> stock[*last + 1];
			
			//update menu
			ofstream menu;
			menu.open("menu.txt",ios::app);
			
			menu << endl << *last + 1 << food[*last + 1] << "\t" << price[*last + 1] << "\t" << stock[*last + 1];
			
			menu.close();
		}
		//modified previous food menu				
		else
		{		
			//variable declaration 
			int a;
			
			cout << "Enter the No of food: ";
			cin >> a;
			
			cout << "Price(RM): ";
			cin >> price[a];
			
			cout << "Stock: ";
			cin >> stock[a];
			
			//update menu
			ofstream menu;
			menu.open("menu.txt");
			
			//
			for(int i = 1; i <= *last; ++i)
			{
				menu << i << food[i] << "\t" << price[i] << "\t" << stock[i] << endl;
			}
			
			//close menu file
			menu.close();			
		}
		
		cout << endl << "loading......" << endl;
		cout << "Success!";			
	}
	
	//accept order
	else if (choice == 2)
	{
		//print all orders
		system("cls");		
		//open order file in input mode
		ifstream file;
		file.open("order.txt");
		
		while(file)
		{
			string s;
			getline(file, s);
			cout << s << endl;
		}				
		//close order file
		file.close();
	}
	
	//Total payment per order
	else if (choice == 3)
	{
		system("cls");
		cout << "Total Payment per Order\n" << endl;
		for(int i = 1; i < count; ++i)
		{
			cout << "Order #" << i << " RM" << sale[i] << endl;	
		}	
	}
	
	//Estimated delivery time
	else if (choice == 4)
	{
		system("cls");
		for (int i = 1; i < count; ++i)
		{
			if((totalItem[i]*5) > 60)
				cout << "order#" << i << " has too many items. It will take longer time." << endl;
			else	
				cout << "order#" << i << " still have " << totalItem[i]*20 << " min(s)" << endl;
		}
			
	}
	
	//Total sale for today
	else
	{
		system("cls");
		cout << "Today has " << count - 1 << " order(s)" << endl << endl;
		for (int i = 1; i < count; ++i)
		{
			cout << "order#" << i << " RM" << sale[i] << endl;
			total += sale[i];				
		}
		cout << "\nTotal sale for today is RM" << total << endl;	
	}
}
//End of program
