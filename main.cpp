#include<iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using namespace std;

// Color codes for console text
enum COLOR {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// Function to set text color
void setColor(int textColor, int bgColor = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// Function to create a fancy box
void drawBox(int width, int height, int x, int y) {
    COORD coord;
    for (int i = 0; i < width; i++) {
        coord.X = x + i;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "═";
        coord.Y = y + height - 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "═";
    }
    
    for (int i = 0; i < height; i++) {
        coord.X = x;
        coord.Y = y + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "║";
        coord.X = x + width - 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "║";
    }
    
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╔";
    
    coord.X = x + width - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╗";
    
    coord.X = x;
    coord.Y = y + height - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╚";
    
    coord.X = x + width - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╝";
}

// Function to center text
void centerText(string text, int y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    int x = (screenWidth - text.length()) / 2;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << text;
}

// Function to display message with animation
void animateText(string text, int color = LIGHTCYAN) {
    setColor(color);
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        Sleep(20); // Adjust speed as needed
    }
    setColor(WHITE);
    cout << endl;
}

// Function to create a loading animation
void loadingAnimation() {
    centerText("Loading", 12);
    for (int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(200);
    }
    cout << endl;
}

struct customerdata
{
	string nm;
	string no;
	int id;
	string pass;
	string add;
};
struct carsdata
{
	string name;
	string model;
	int cost;
	string numplate;
};
int iid;
void menu();
void adminM();
void about();
void adminidpassc();
void admin();
void customer();
void allcars();
void addcars();
void removecus();
void customerM();
void rentcar();
void creports();
void returncar();
void allreports();
void updatecdata();
void removecar();
void allcustomers();
void ranidpass(int& ranid, string& ranpass);
void addcus();
int main();
void addcars()
{
	carsdata* car = new carsdata;
	fstream addcar("cardata.txt", ios::app);
	system("CLS");
	cin.ignore();

	cout << endl;
	cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tAdding Car\n";
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;
	cout << "Enter the Name of the Car.\n";
	getline(cin, car->name);
	cout << "Enter the Model of the Car.\n";
	getline(cin, car->model);
	cout << "Enter the Plate Number of the Car.\n";
	cin >> car->numplate;
	cin.ignore();
	cout << "Enter the Cost(per hour) of the Car.\n";
	cin >> car->cost;

	addcar << left << setw(10) << car->name << "\t\t\t";
	addcar << left << setw(10) << car->model << "\t\t\t";
	addcar << left << setw(10) << car->numplate << "\t\t";
	addcar << left << setw(10) << car->cost << "\n";
	addcar.close();
	cout << "\n";
	cout << "Your Car has been added successfully.\n";
	delete car;
	Sleep(1500);
	adminM();
}
void allcars()
{
	system("CLS");

	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;
	cout << left << setw(10) << "| Name |\t\t\t";
	cout << left << setw(10) << "| Model |\t\t\t";
	cout << left << setw(10) << "| Plate Number |\t";
	cout << left << setw(10) << "| Cost / hour |";
	cout << endl;
	cout << endl;
	ifstream cardata("cardata.txt");
	carsdata car;

	while (cardata >> car.name >> car.model >> car.numplate >> car.cost)
	{
		cout << left << setw(10) << car.name << "\t\t\t";
		cout << left << setw(10) << car.model << "\t\t\t";
		cout << left << setw(10) << car.numplate << "\t\t";
		cout << left << setw(10) << car.cost << "\n";

	}
	cardata.close();
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;
}
void removecar()
{
	int count = 0;
	do
	{

		string rem;
		system("CLS");

		cout << endl;
		cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tRemoving Cars\n";
		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
		cout << "|Name|\t\t\t|Model|\t\t\t|Plate Number|\t\t\t|Cost/hour|\n";
		cout << endl;
		ifstream remcar("cardata.txt");
		carsdata car;

		while (remcar >> car.name >> car.model >> car.numplate >> car.cost)
		{
			cout << car.name << "\t\t\t";
			cout << car.model << "\t\t\t";
			cout << car.numplate << "\t\t\t";
			cout << car.cost << "\n";
		}
		remcar.close();
		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;

		cout << "Enter the Name of the Car you want to remove:\n";
		cin.ignore();
		getline(cin, rem);

		ifstream org("cardata.txt");
		ofstream temp("tempfile.txt");

		bool found = false;
		while (org >> car.name >> car.model >> car.numplate >> car.cost)
		{
			if (car.name != rem)
			{
				temp << car.name << "\t\t";
				temp << car.model << "\t\t";
				temp << car.numplate << "\t\t";
				temp << car.cost << "\n";

			}
			else
			{
				found = true;
			}
		}

		org.close();
		temp.close();

		remove("cardata.txt");
		rename("tempfile.txt", "cardata.txt");

		if (found)
		{
			cout << "\n";
			cout << "Your Car has been removed successfully.\n";
			Sleep(1500);
			int count1 = 1;
			do
			{
				system("CLS");
				int choice;
				cout << "\n";
				cout << "[1] Remove more Cars\n";
				cout << "[2] Back to Admin Menu\n";
				cout << "\n";
				cout << "Enter your Choice: ";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					count = 1;
					break;
				}
				case 2:
				{
					adminM();
					break;
				}
				default:
				{
					cout << "\n";
					cout << "Invalid Input!\n";
					cout << "Try Again";
					Sleep(2000);
					count1 = 0;
				}
				}
			} while (count1 == 0);

		}
		else
		{
			cout << "\n";
			cout << "Car not found!\n";
			Sleep(1500);
			adminM();
		}



	}while (count == 1);
}
void allcustomers()
{

	system("CLS");
	cout << endl;
	cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tViewing Customer\n";
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;
	cout << "|Name|\t\t\t";
	cout << "|Address|\t\t\t";
	cout << "|Phone Number|\t\t\t";
	cout << "|ID|\t\t\t";
	cout << "|Password|\n";
	/*cout << endl;*/

	cout << endl;
	ifstream allcus("customerdata.txt");
	customerdata customer;

	while (allcus >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass)
	{
		cout << endl;
		cout << customer.nm << "\t\t\t";
		cout << customer.add << "\t\t\t";
		cout << customer.no << "\t\t\t";
		cout << customer.id << "\t\t\t";
		cout << customer.pass << "\n";



	}
	allcus.close();
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;


}
void removecus()
{
	int count = 0;
	do
	{
		system("CLS");

		cout << endl;
		cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tRemoving Customer\n";
		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
		cout << left << setw(10) << "| Name |\t\t\t";
		cout << left << setw(10) << "| Address |\t\t\t";
		cout << left << setw(10) << "| Phone Number |\t\t";
		cout << left << setw(10) << "| ID |\t\t";
		cout << left << setw(10) << "| Password |";
		cout << endl;

		ifstream cdata("customerdata.txt");
		customerdata customer;

		while (cdata >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass)
		{
			cout << left << setw(10) << customer.nm << "\t\t\t";
			cout << left << setw(10) << customer.add << "\t\t\t";
			cout << left << setw(10) << customer.no << "\t\t\t";
			cout << left << setw(10) << customer.id << "\t\t";
			cout << left << setw(10) << customer.pass << "\n";
			cout << "\n";
		}

		cdata.close();

		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
		int rem;
		cout << "Enter the ID of the customer you want to remove: ";
		cin.ignore();
		cin >> rem;

		ifstream org("customerdata.txt");
		ofstream temp("tempfile.txt");

		bool found = false;
		while (org >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass)
		{
			if (customer.id != rem)
			{
				temp << left << setw(10) << customer.nm << "\t\t\t";
				temp << left << setw(10) << customer.add << "\t\t\t";
				temp << left << setw(10) << customer.no << "\t\t\t";
				temp << left << setw(10) << customer.id << "\t\t";
				temp << left << setw(10) << customer.pass << "\n";

			}
			else
			{
				found = true;
			}
		}

		org.close();
		temp.close();

		remove("customerdata.txt");
		rename("tempfile.txt", "customerdata.txt");

		if (found)
		{
			cout << "\n";
			cout << "Your customer has been removed successfully.\n";
			Sleep(1500);
			int count1 = 1;
			do
			{
				system("CLS");
				int choice;
				cout << "\n";
				cout << "[1] Remove more Customer\n";
				cout << "[2] Back to Admin Menu\n";
				cout << "\n";
				cout << "Enter your Choice: ";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					count = 1;
					break;
				}
				case 2:
				{
					adminM();
					break;
				}
				default:
				{
					cout << "\n";
					cout << "Invalid Input!\n";
					cout << "Try Again";
					Sleep(2000);
					count1 = 0;
				}
				}
			} while (count1 == 0);


		}
		else
		{
			cout << "\n";
			cout << "Customer not found!\n";
			Sleep(1500);
			count = 1;

		}



	} while (count == 1);

}
void updatecdata()
{
	int count3 = 0;
	do
	{

		system("CLS");

		cout << endl;
		cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tUpdating Customer Data\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
		allcustomers();

		int id;
		cout << "Enter the ID of the customer whose data you want to update: ";
		cin >> id;

		ifstream cus("customerdata.txt");
		ofstream temp("tempfile.txt");

		customerdata customer;
		bool found = false;

		while (cus >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass) {
			if (customer.id == id)
			{
				found = true;
				int count1 = 1;
				do
				{
					system("CLS");
					int choice;
					cout << "\n";
					cout << "Which you want to Update\n";
					cout << "[1] Address\n";
					cout << "[2] Phone Number\n";
					cout << "Enter your choice: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						cout << "Enter updated address: ";
						cin.ignore();
						getline(cin, customer.add);
						break;
					}
					case 2:
					{
						cout << "Enter updated phone number: ";
						cin.ignore();
						getline(cin, customer.no);
						break;
					}
					default:
					{
						cout << "\n";
						cout << "Invalid Input!\n";
						cout << "Try Again";
						Sleep(2000);
						count1 = 0;
					}
					}

				} while (count1 == 0);

			}

			temp << left << setw(10) << customer.nm << "\t\t\t";
			temp << left << setw(10) << customer.add << "\t\t\t";
			temp << left << setw(10) << customer.no << "\t\t\t";
			temp << left << setw(10) << customer.id << "\t\t";
			temp << left << setw(10) << customer.pass << "\n";
		}

		cus.close();
		temp.close();

		if (!found)
		{
			cout << "Customer not found!\n";
			Sleep(1500);

			return;
		}

		remove("customerdata.txt");
		rename("tempfile.txt", "customerdata.txt");

		cout << "\n";
		cout << "Customer data has been updated successfully.\n";
		Sleep(1500);
		system("CLS");
		int ch;
		cout << "\n";
		cout << "[1] Update more Customer's Data\n";
		cout << "[2] Back to Admin Menu \n";
		cout << "Enter your choice: ";
		cin >> ch;
		int count2 = 1;
		do
		{
			switch (ch)
			{
			case 1:
			{
				count3 = 1;
				break;
			}
			case 2:
			{
				adminM();
				break;
			}
			default:
			{
				cout << "Invalid Input!\n";
				cout << "Try Again";
				Sleep(2000);
				count2 = 0;
			}
			}

		} while (count2 == 0);

	} while (count3 == 1);
}
void rentcar()
{
	int count = 0;
	do
	{


		system("CLS");
		cout << endl;
		cout << "CRMS\t>\tCustomer\t>\tRent a Car\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;

		allcars();

		
		

		ifstream cus("customerdata.txt");
		customerdata customer;
		bool found = false;

		while (cus >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass) {
			if (customer.id == iid)
			{
				found = true;
				break;
			}
		}

		cus.close();

		if (!found)
		{
			cout << "Customer not found!\n";

			Sleep(1500);
			count = 1;
			return;
		}



		cout << "Enter the Name of the Car you want to rent: ";
		string name;
		cin.ignore();
		getline(cin, name);

		ifstream cardata("cardata.txt");
		carsdata car;
		bool carFound = false;


		while (cardata >> car.name >> car.model >> car.numplate >> car.cost)
		{
			if (car.name == name)
			{
				carFound = true;
				break;
			}
		}

		cardata.close();

		if (!carFound)
		{
			cout << "Car not found!\n";
			Sleep(1500);
			count = 1;
			return;
		}
		int hr;
		cout << "For how many hours you want to rent: ";
		cin >> hr;

		int rcost = car.cost * hr;
		cout << endl;
		cout << "*********************************************\n";
		cout << "\n";
		cout << "Rental Details:\n";
		cout << endl;
		cout << "Customer ID: " << iid << "\n";
		cout << "Customer Name: " << customer.nm << "\n";
		cout << "Car Name: " << car.name << "\n";
		cout << "Rent per Hour: " << car.cost << "\n";
		cout << "Total Rent for " << hr << " hours is: " << rcost << "\n";
		cout << endl;
		cout << "*********************************************\n";



		ofstream report("customer_reports.txt", ios::app);
		if (report.is_open())
		{
			report << iid << "\t" << customer.nm << "\t\t\t" << car.name << "\t\t\t" << car.cost << "\t" << hr << "\t"<<rcost<<"\t"<<endl;
			/*report << "Customer ID: " << id << "\n";
			report << "Customer Name: " << customer.nm << "\n";
			report << "Car Name: " << car.name << "\n";
			report << "Rent per Hour: " << car.cost << "\n";
			report << "Total Rent for " << hr << "hours is: " << rcost << "\n";
			report << "-----------------------------\n";*/
			report.close();
		}
		else
		{
			cout << "Error writing to rental reports file!\n";
			count = 1;
		}
		int ch;

		cout << "\n";
		cout << "Car rented successfully!\n";
		cout << endl;
		cout << endl;

		cout << "Press 1 to Go Back\n";
		cin >> ch;
		if (ch == 1)
		{
			customerM();
		}
		else
		{
			cout << "Invalid Input!\n";
			Sleep(2000);
			count = 1;


		}
	} while (count == 1);


}
void creports()
{
	int count = 0;
	do
	{
		
		system("CLS");
		cout << endl;
		cout << "CRMS\t>\tCustomer\t>\tView Rental Reports\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;


		ifstream report("customer_reports.txt");
		string line;

		cout << "Rental Reports:\n";
		cout << "-----------------------------------------\n";
		
		cout <<"ID\t" << "Name\t\t\t" << "Car Name\t\t\t" <<"Rent/Hour \t" << "Hours\t" <<"Total Rent\t"<<"Return(Y/N)"<< endl;
		cout << endl;
		while (getline(report, line))
		{
			if (line.find( to_string(iid)) != string::npos)
			{
				cout << line<<endl;
				cout << endl;
			
			}
			
		}

		report.close();
		

		int choice;
		cout << "\nPress 1 to Go Back\n";
		cout << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		if (choice == 1)
		{
			customerM();
		}
		else
		{
			count = 1;
		}

	} while (count == 1);
}
void ranidpass(int& ranid, string& ranpass)
{
	ranid = 1000 + rand() % 9000;
	const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const int passlength = 8;
	ranpass = "";

	for (int i = 0; i < passlength; i++)
	{
		char randomChar = chars[rand() % chars.size()];
		ranpass += randomChar;
	}
}
void addcus()
{
	int choice = 0;
	int count = 1;
	fstream cdata("customerdata.txt", ios::app);
	do
	{
		customerdata* addcus = new customerdata;

		system("CLS");
		cin.ignore();

		cout << endl;
		cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tAdding Customer\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;

		cout << "Enter the Name of the customer.\n";
		getline(cin, addcus->nm);
		cout << "Enter the address of the customer.\n";
		getline(cin, addcus->add);
		cout << "Enter the Phone Number of the customer.\n";
		getline(cin, addcus->no);



		int ranid;
		string ranpass;

		do
		{
			ranidpass(ranid, ranpass);
			ifstream cid("customerdata.txt");
			customerdata excustomer;
			bool idexist = false;

			while (cid >> excustomer.nm >> excustomer.add >> excustomer.no >> excustomer.id >> excustomer.pass)
			{
				if (ranid == excustomer.id)
				{
					idexist = true;
					break;
				}
			}

			cid.close();

			if (!idexist)
			{
				break;
			}

		} while (true);

		addcus->id = ranid;
		addcus->pass = ranpass;

		cout << endl;
		cout << "**********************************************\n";
		cout << "Customer's ID is: " << ranid << endl;
		cout << "Password is: " << ranpass << endl;
		cout << "**********************************************\n";

		cdata << addcus->nm << "\t\t\t";
		cdata << addcus->add << "\t\t\t";
		cdata << addcus->no << "\t\t\t";
		cdata << addcus->id << "\t\t\t";
		cdata << addcus->pass << "\n";

		cdata.close();

		cout << "\n";
		cout << "Your customer has been added successfully.\n";
		cout.flush();
		delete addcus;


		int count1 = 0;
		do
		{

			int ch;
			cout << "\n";
			cout << "[1] Add more Customers\n";
			cout << "[2] Back to Admin Menu\n";
			cout << "Enter your Choice: ";
			cin >> ch;
			switch (ch)
			{
			case 1:
			{

				count = 0;
				count1++;
				break;
			}
			case 2:
			{
				adminM();
				count1++;
				break;
			}
			default:
			{
				cout << "Invalid Input!\n";
				cout << "Try Again";
				Sleep(2000);
				system("CLS");
			}
			}
		} while (count1 == 0);
	} while (count == 0);
}
void allreports()
{
	system("CLS");
	cout << endl;
	cout << "CRMS\t>\tAdmin\t>\tView All Rental Reports\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;
	ifstream report("customer_reports.txt");
	string line;
	cout << "All Rental Reports:\n";
	cout << "****************************************\n";
	cout << "ID\tName\t\t\tCar Name\t\t\tRent/Hour\tHours\trcost\tReturn(Y/N)\n";
	while (getline(report, line))
	{
		cout << line << "\n";
	}

	report.close();

	int choice;
	cout << "\nPress 1 to Go Back\n";
	cout << endl;
	cout << "Enter your Choice: ";
	cin >> choice;
	if (choice == 1)
	{
		adminM();
	}
	else
	{
		cout << "Invalid Input.Try Again!\n";
		Sleep(1500);
	}

}
void returncar()
{
	system("CLS");
	cout << endl;
	cout << "CRMS\t>\tCustomer\t>\tReturn a Car\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;

	allcars();
	

	ifstream cus("customerdata.txt");
	customerdata customer;
	bool found = false;

	while (cus >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass)
	{
		if (customer.id == iid)
		{
			found = true;
			break;
		}
	}

	cus.close();

	if (!found)
	{
		cout << "Customer not found!\n";
		Sleep(1500);
		return;
	}

	string name;
	cout << "Enter the Name of the Car you are returning: ";
	cin.ignore();
	getline(cin, name);

	fstream report("customer_reports.txt",ios::app);
	string line;
	bool found1 = false;
	while (getline(report, line))
	{
		if (line.find(to_string(iid)) != string::npos && line.find(name) != string::npos )
		{
			
			cout << line << "Yes"<< endl;
			report << line << "Yes" << endl;
			found1 = true;
		}

	}
	
	if (found1)
	{
		cout << "\nCar returned successfully!\n";
	}
	int choice;
	cout << "\nCar returned successfully!\n";
	cout << "Press 1 to Go Back\n";
	cin >> choice;
	if (choice == 1)
	{
		customerM();
	}
	else
	{
		cout << "Invalid Input!\n";
		Sleep(2000);
	}
}
void adminM()
{
	int count = 0;

	do
	{
		int choice;
		system("CLS");
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw main menu box
		drawBox(70, 18, (consoleWidth - 70) / 2, 3);
		
		// Title with colors
		setColor(LIGHTCYAN);
		centerText("╔════════════════════════════════════════╗", 1);
		centerText("║          ADMINISTRATOR PANEL           ║", 2);
		centerText("╚════════════════════════════════════════╝", 3);
		setColor(WHITE);
		
		// Greeting
		setColor(YELLOW);
		centerText("Welcome to Admin Dashboard", 5);
		setColor(WHITE);
		
		// Menu options
		setColor(LIGHTGREEN);
		centerText("[ ACCOUNT MANAGEMENT ]", 7);
		setColor(WHITE);
		centerText("[1] Change Password", 8);
		
		setColor(LIGHTGREEN);
		centerText("[ CUSTOMER MANAGEMENT ]", 10);
		setColor(WHITE);
		centerText("[2] Add a Customer", 11);
		centerText("[3] Remove a Customer", 12);
		centerText("[4] Update Customer Data", 13);
		centerText("[5] View current Customers", 14);
		
		setColor(LIGHTGREEN);
		centerText("[ CAR MANAGEMENT ]", 16);
		setColor(WHITE);
		centerText("[6] Add Car", 17);
		centerText("[7] Remove Car", 18);
		centerText("[8] View Available Cars", 19);
		
		setColor(LIGHTGREEN);
		centerText("[ REPORTS ]", 21);
		setColor(WHITE);
		centerText("[9] View all Rental Reports", 22);
		
		centerText("-----------------------------------", 24);
		centerText("[10] Back to Login page", 25);
		centerText("[11] Back to Main Menu", 26);
		
		// Input prompt
		setColor(LIGHTCYAN);
		centerText("Please enter your choice: ", 28);
		setColor(WHITE);
		
		// Position cursor for input
		COORD pos;
		pos.X = (consoleWidth / 2) + 13;
		pos.Y = 28;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			loadingAnimation();
			adminidpassc();
			admin();
			count++;
			break;
		}

		case 2:
		{
			loadingAnimation();
			addcus();
			count++;
			break;
		}

		case 3:
		{
			loadingAnimation();
			removecus();
			count++;
			break;
		}

		case 4:
		{
			loadingAnimation();
			updatecdata();
			count++;
			break;
		}

		case 5:
		{
			loadingAnimation();
			int cnt = 0;
			do
			{
				string ch;
				allcustomers();
				setColor(LIGHTGREEN);
				cout << "press 1 to go back to Menu Page\n";
				setColor(WHITE);
				cout << endl;
				cout << "Please enter your choice: ";
				cin >> ch;
				if (ch != "1")
				{
					setColor(LIGHTRED);
					cout << "Invalid input, try again!\n";
					setColor(WHITE);
					Sleep(1000);
					cnt = 1;
				}
				else
				{
					adminM();
				}
			} while (cnt == 1);
			count++;
			break;
		}

		case 6:
		{
			loadingAnimation();
			addcars();
			count++;
			break;
		}

		case 7:
		{
			loadingAnimation();
			removecar();
			count++;
			break;
		}

		case 8:
		{
			loadingAnimation();
			int cnt = 0;
			do
			{
				system("CLS");
				string choice;
				cout << endl;
				setColor(LIGHTCYAN);
				cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tViewing Car\n";
				setColor(WHITE);
				allcars();
				setColor(LIGHTGREEN);
				cout << "press 1 to go back to Menu Page\n";
				setColor(WHITE);
				cout << endl;
				cout << "Please enter your choice: ";
				cin >> choice;
				if (choice != "1")
				{
					setColor(LIGHTRED);
					cout << "Invalid input, try again!\n";
					setColor(WHITE);
					Sleep(1000);
				}
				else
				{
					adminM();
					cnt++;
				}
			} while (cnt == 0);
			count++;
			break;
		}

		case 9:
		{
			loadingAnimation();
			allreports();
			count++;
			break;
		}

		case 10:
		{
			loadingAnimation();
			admin();
			count++;
			break;
		}

		case 11:
		{
			loadingAnimation();
			main();
			count++;
			break;
		}

		default:
		{
			setColor(LIGHTRED);
			centerText("Invalid choice, try again!", 30);
			setColor(WHITE);
			Sleep(1500);
		}
		}
	} while (count == 0);
}
void adminidpassc()
{
	system("CLS");
	cout << endl;
	cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tChange ID or Password\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;

	int count = 0;
	do
	{
		int choice;
		cout << "Which you want to Change\n";
		cout << "[1] AdminID\n";
		cout << "[2] Admin Password\n";
		cout << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("CLS");
			fstream newid("adminid.txt", ios::out | ios::trunc);
			int id;

			cout << endl;
			cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tChange AdminID\n";
			cout << "-----------------------------------------------------------------------------------------------------------------------\n";
			cout << endl;
			cout << "New AdminID: ";
			cin >> id;
			newid << id;
			newid.close();
			cout << endl;
			cout << "Your AdminID has been successfully changed.\n";
			Sleep(1500);
			admin();
			break;
		}
		case 2:
		{
			system("CLS");
			fstream pass("adminpass.txt", ios::out | ios::trunc);
			string pwd;

			cout << endl;
			cout << "CRMS\t>\tAdmin\t>\tMenu\t>\tChange Password\n";
			cout << "-----------------------------------------------------------------------------------------------------------------------\n";
			cout << endl;
			cout << "New Password: ";
			cin >> pwd;
			pass << pwd;
			pass.close();
			cout << endl;
			cout << "Your Password has been successfully changed.\n";
			Sleep(1500);
			admin();
			break;
		}
		default:
		{
			cout << "\n";
			cout << "Invalid Input!\n";
			cout << "Try Again";
			Sleep(2000);
			system("CLS");
			count = 1;
		}
		}
	} while (count == 1);




}
void admin()
{
	int count = 0;
	do
	{
		system("CLS");
		string adminid;
		string adminpass;
		string tempid;
		string temppass;
		fstream id("adminid.txt");
		fstream pass("adminpass.txt");

		id >> adminid;
		id.close();
		pass >> adminpass;
		pass.close();
		
		system("CLS");
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw login box
		drawBox(50, 10, (consoleWidth - 50) / 2, 5);
		
		// Title
		setColor(LIGHTCYAN);
		centerText("╔══════════════════════════════╗", 2);
		centerText("║       ADMINISTRATOR LOGIN    ║", 3);
		centerText("╚══════════════════════════════╝", 4);
		setColor(WHITE);
		
		// Input fields with positioning
		centerText("Please enter your credentials", 7);
		
		// ID field
		setColor(LIGHTGREEN);
		centerText("ID: ", 9);
		
		// Position cursor for ID input
		COORD pos;
		pos.X = (consoleWidth / 2) + 2;
		pos.Y = 9;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setColor(WHITE);
		cin >> tempid;
		
		// Password field
		setColor(LIGHTGREEN);
		centerText("Password: ", 11);
		
		// Position cursor for password input
		pos.X = (consoleWidth / 2) + 5;
		pos.Y = 11;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setColor(WHITE);
		cin >> temppass;

		if (tempid == adminid && temppass == adminpass)
		{
			setColor(LIGHTGREEN);
			centerText("Login successful!", 14);
			setColor(WHITE);
			Sleep(1000);
			adminM();
		}
		else
		{
			setColor(LIGHTRED);
			centerText("Invalid ID or Password!", 14);
			setColor(WHITE);
			Sleep(1000);
			
			// Login retry options
			drawBox(40, 5, (consoleWidth - 40) / 2, 16);
			centerText("[1] Try again", 18);
			centerText("[2] Go Back to Main Menu", 19);
			
			setColor(LIGHTCYAN);
			centerText("Enter your choice: ", 21);
			setColor(WHITE);
			
			// Position cursor for choice input
			pos.X = (consoleWidth / 2) + 9;
			pos.Y = 21;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			
			int choice;
			cin >> choice;
			if (choice == 1)
			{
				count = 1;
			}
			else
			{
				main();
			}
		}
	} while (count == 1);
}
void customer()
{
	system("CLS");
	int count = 0;

	do
	{
		system("CLS");
		int tempid;
		string temppass;
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw login box
		drawBox(50, 10, (consoleWidth - 50) / 2, 5);
		
		// Title
		setColor(YELLOW);
		centerText("╔═════════════════════════╗", 2);
		centerText("║     CUSTOMER LOGIN      ║", 3);
		centerText("╚═════════════════════════╝", 4);
		setColor(WHITE);
		
		// Input fields with positioning
		centerText("Please enter your credentials", 7);
		
		// ID field
		setColor(LIGHTGREEN);
		centerText("ID: ", 9);
		
		// Position cursor for ID input
		COORD pos;
		pos.X = (consoleWidth / 2) + 2;
		pos.Y = 9;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setColor(WHITE);
		cin >> tempid;
		
		// Password field
		setColor(LIGHTGREEN);
		centerText("Password: ", 11);
		
		// Position cursor for password input
		pos.X = (consoleWidth / 2) + 5;
		pos.Y = 11;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		setColor(WHITE);
		cin >> temppass;

		ifstream customerFile("customerdata.txt");
		customerdata customer;

		bool found = false;

		while (customerFile >> customer.nm >> customer.add >> customer.no >> customer.id >> customer.pass)
		{
			if ( tempid == (customer.id) && temppass == customer.pass)
			{
				found = true;
				break;
			}
		}

		customerFile.close();

		if (found)
		{
			iid = tempid;
			setColor(LIGHTGREEN);
			centerText("Login successful!", 14);
			setColor(WHITE);
			Sleep(1000);
			customerM();
		}
		else
		{
			setColor(LIGHTRED);
			centerText("Invalid ID or Password!", 14);
			setColor(WHITE);
			Sleep(1000);
			
			// Login retry options
			drawBox(40, 5, (consoleWidth - 40) / 2, 16);
			centerText("[1] Try again", 18);
			centerText("[2] Go Back to Main Menu", 19);
			
			setColor(LIGHTCYAN);
			centerText("Enter your choice: ", 21);
			setColor(WHITE);
			
			// Position cursor for choice input
			pos.X = (consoleWidth / 2) + 9;
			pos.Y = 21;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			
			int choice;
			cin >> choice;
			if (choice == 1)
			{
				count = 1;
			}
			else
			{
				main();
			}
		}
	} while (count == 1);
}
void customerM()
{
	int choice;
	int count = 0;

	do
	{
		system("CLS");
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw box for menu
		drawBox(60, 15, (consoleWidth - 60) / 2, 4);
		
		// Title with colors
		setColor(YELLOW);
		centerText("╔═════════════════════════════════╗", 2);
		centerText("║       CUSTOMER DASHBOARD        ║", 3);
		centerText("╚═════════════════════════════════╝", 4);
		setColor(WHITE);
		
		// Greeting
		ifstream customerFile("customerdata.txt");
		customerdata customerData;
		string customerName = "Valued Customer";
		
		while (customerFile >> customerData.nm >> customerData.add >> customerData.no >> customerData.id >> customerData.pass) {
			if (customerData.id == iid) {
				customerName = customerData.nm;
				break;
			}
		}
		customerFile.close();
		
		setColor(LIGHTGREEN);
		centerText("Welcome, " + customerName, 7);
		setColor(WHITE);
		
		// Menu options
		centerText("Available Options", 9);
		
		centerText("[1] View Available Cars", 11);
		centerText("[2] Rent a Car", 12);
		centerText("[3] Return a Car", 13);
		centerText("[4] View Rental Reports", 14);
		centerText("--------------------------", 15);
		centerText("[10] Back to Login Page", 16);
		centerText("[11] Back to Main Menu", 17);
		
		// Input prompt
		setColor(LIGHTCYAN);
		centerText("Please enter your choice: ", 19);
		setColor(WHITE);
		
		// Position cursor for input
		COORD pos;
		pos.X = (consoleWidth / 2) + 13;
		pos.Y = 19;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			loadingAnimation();
			int cnt = 0;
			do
			{
				system("CLS");
				string ch;
				cout << endl;
				setColor(YELLOW);
				cout << "CRMS\t>\tCustomer\t>\tMenu\t>\tViewing Car\n";
				setColor(WHITE);
				allcars();
				setColor(LIGHTGREEN);
				cout << "press 1 to go back to Menu Page\n";
				setColor(WHITE);
				cout << endl;
				cout << "Please enter your choice: ";
				cin >> ch;
				if (ch == "1")
				{
					customerM();
				}
				else
				{
					setColor(LIGHTRED);
					cout << "Invalid input, try again!\n";
					setColor(WHITE);
					Sleep(1000);
					cnt = 1;
				}
			} while (cnt == 1);
			count++;
			break;
		}

		case 2:
		{
			loadingAnimation();
			rentcar();
			count++;
			break;
		}

		case 3:
		{
			loadingAnimation();
			returncar();
			count++;
			break;
		}

		case 4:
		{
			loadingAnimation();
			creports();
			count++;
			break;
		}

		case 10:
		{
			loadingAnimation();
			::customer();
			count++;
			break;
		}

		case 11:
		{
			loadingAnimation();
			main();
			count++;
			break;
		}

		default:
		{
			setColor(LIGHTRED);
			centerText("Invalid choice! Please try again...", 21);
			setColor(WHITE);
			Sleep(1500);
		}
		}
	} while (count == 0);
}
void menu()
{
	cout << "[1] Admin\n";
	cout << "[2] Customer\n";
	cout << "[3] About\n";
	cout << "[0] Exit\n";
}
void about()
{
	int count = 0;
	do
	{
		system("CLS");
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw about box
		drawBox(70, 15, (consoleWidth - 70) / 2, 5);
		
		// Title
		setColor(LIGHTCYAN);
		centerText("╔═══════════════════════════════════════╗", 3);
		centerText("║      CAR RENTAL MANAGEMENT SYSTEM     ║", 4);
		centerText("╚═══════════════════════════════════════╝", 5);
		setColor(WHITE);
		
		// About content with animation
		setColor(YELLOW);
		centerText("✧ DEVELOPER INFORMATION ✧", 8);
		setColor(WHITE);
		
		setColor(LIGHTGREEN);
		centerText("Created By: Muhammad Sami", 10);
		centerText("Roll No: 2023-CS-656", 11);
		centerText("Session: 2023", 12);
		centerText("Section: B", 13);
		centerText("Contact: 03066536700", 14);
		setColor(WHITE);
		
		// Date
		SYSTEMTIME st;
		GetLocalTime(&st);
		string date = "Current Date: " + to_string(st.wDay) + "/" + to_string(st.wMonth) + "/" + to_string(st.wYear);
		centerText(date, 16);
		
		// Return option
		setColor(LIGHTCYAN);
		centerText("┌─────────────────────────┐", 19);
		centerText("│  Press 1 to Go Back     │", 20);
		centerText("└─────────────────────────┘", 21);
		setColor(WHITE);
		
		// Position cursor for input
		COORD pos;
		pos.X = (consoleWidth / 2) + 2;
		pos.Y = 23;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
		int choice;
		cin >> choice;
		
		if (choice == 1)
		{
			main();
		}
		else
		{
			setColor(LIGHTRED);
			centerText("Invalid Input! Try Again...", 23);
			setColor(WHITE);
			Sleep(1500);
			count = 1;
		}
	} while (count == 1);
}
int main()
{
	int count = 0;
	
	// Set console title with explicit A version for ANSI strings
	SetConsoleTitleA("Car Rental Management System - PF Project");
	
	do
	{
		system("CLS");
		
		// Configure console window
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		
		// Draw decorative box
		drawBox(80, 15, (consoleWidth - 80) / 2, 2);
		
		// Title with animation and color
		centerText("", 4);
		setColor(LIGHTCYAN, BLUE);
		centerText("█▀▀ █▀█ █▀█   █▀█ █▀▀ █▄░█ ▀█▀ █▀█ █░░   █▀ █▄█ █▀ ▀█▀ █▀▀ █▀▄▀█", 5);
		centerText("█▄▄ █▀█ █▀▄   █▀▄ ██▄ █░▀█ ░█░ █▀█ █▄▄   ▄█ ░█░ ▄█ ░█░ ██▄ █░▀░█", 6);
		setColor(WHITE);
		
		// Welcome message with animation
		setColor(YELLOW);
		centerText("Welcome to Car Rental Management System", 8);
		setColor(WHITE);
		
		// Current date
		SYSTEMTIME st;
		GetLocalTime(&st);
		string date = "Date: " + to_string(st.wDay) + "/" + to_string(st.wMonth) + "/" + to_string(st.wYear);
		centerText(date, 10);
		
		// Menu options with highlighting
		centerText("╔════════════════════════════╗", 12);
		setColor(LIGHTGREEN);
		centerText("║       MAIN MENU           ║", 13);
		setColor(WHITE);
		centerText("╚════════════════════════════╝", 14);
		
		centerText("[1] Admin Login", 16);
		centerText("[2] Customer Login", 17);
		centerText("[3] About System", 18);
		centerText("[0] Exit System", 19);
		
		// Input with highlighting
		setColor(LIGHTCYAN);
		centerText("Please enter your choice: ", 21);
		setColor(WHITE);
		
		// Position cursor for input
		COORD pos;
		pos.X = (consoleWidth / 2) + 10;
		pos.Y = 21;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
		int choice;
		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			// Show loading animation
			loadingAnimation();
			admin();
			count++;
			break;
		}
		case 2:
		{
			loadingAnimation();
			customer();
			count++;
			break;
		}
		case 3:
		{
			loadingAnimation();
			about();
			count++;
			break;
		}
		case 0:
		{
			system("CLS");
			drawBox(60, 6, (consoleWidth - 60) / 2, 10);
			setColor(YELLOW);
			animateText("Thank you for using Car Rental Management System!", YELLOW);
			centerText("Goodbye! Have a nice day!", 13);
			setColor(WHITE);
			Sleep(2000);
			count++;
			break;
		}
		default:
		{
			setColor(LIGHTRED);
			centerText("Invalid input! Please try again...", 23);
			setColor(WHITE);
			Sleep(1500);
		}
		}
	} while (count == 0);

	return 0;
}
