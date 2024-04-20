/*--- Author
		Hasheem Ahmed ----*/

// Iostream for cout cin
#include <iostream>

// Iomanip for setw setfill
#include <iomanip>

// Ctime for time() function to get the current time
#include <ctime>

// String for getline() function to get string input
#include <string>

// Conio.h for the _getch() function to stay on screen until key is pressed
#include <conio.h>

// For std::
using namespace std;

// To get the Current Time
time_t now = time(0);

// Used to remove the warning for localtime function
#pragma warning(suppress : 4996)
tm* ltm = localtime(&now);

// Storing the Current Date in variables
int cday = ltm->tm_mday;
int cmonth = 1+ ltm->tm_mon;
int cyear = 1900 + ltm->tm_year;


// Calendar Class for Getting the the Months And Years
class calender
{

	// Variables
	int day;
	int month;
	int year;
	int weekday;

public:

	//Constructor
	calender()
	{
		day = month = year = weekday = 0;
	}

	//Function used to check the leap year by passing the year as argument
	bool checkLeapYear(int year)
	{
		if (year % 400 == 0)
			return true;
		else if (year % 100 == 0)
			return false;
		else if (year % 4 == 0)
			return true;
		else
			return false;
	}

	// Function Used to print month on the Screen of desired input
	void showMonth(int month, int year)
	{
		if (month <= 12 || year >= 1900)
		{
			int days = 1;
			this->line();
			cout <<"|" <<setw(18) << this->monthname(month) << "    " << year  << "    | \n";
			this->line();
			cout << "|   M   T   W   T   F   S   S  |\n" ;
			this->line();
			cout << " ";

			for (int i = 1; days <= this->calculatingmonth(month, year); i++)
			{
				if (i < this->calculatingday(month, year, this->calculatingWeekDay(year)) + 1)
				{
					cout << setw(4) << " ";
				}
				else
				{
					cout << setw(4) << days;
					if (days == cday && year == cyear && month == cmonth)
						cout << "*";
					days++;
				}
				if (i % 7 == 0)
					cout << " " << endl << " ";
			}
			cout << endl << "\b";
			this->line();
		}
		else
			cout << "Invalid Month or Year.\n";
	}


	// Function used to print line for designing
	void line()
	{
		cout << "--------------------------------\n";
	}


	// Used to get the day of week like mon tue etc
	int calculatingday(int month,int year, int weekday)
	{
		int temp = weekday;
		for (int i = 1; i < month; i++)
		{
			temp += this->calculatingmonth(i, year);
		}
		return temp % 7;
	}


	// Function used to check the days in month
	int calculatingmonth(int month,int year)
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;
		else if (month == 2)
		{
			if (checkLeapYear(year))
				return 29;
			else
				return 28;
		}
		return month;
	}

	//Used to get calculate the day of the week
	int calculatingWeekDay(int year)
	{
		int diff = 0,defaultday = 1900;
		weekday = 0;
		diff = year - 1900;

		for (int i = 0; i < diff; i++)
		{
			if (checkLeapYear(defaultday))
				weekday += 366;
			else if (!checkLeapYear(defaultday))
				weekday += 365;

			defaultday++;
		}

		return weekday % 7;
	}


	// used to get the month name
	string monthname(int month)
	{
		if (month == 1)
			return "January";
		else if (month == 2)
			return "Feburary";
		else if (month == 3)
			return "March";
		else if (month == 4)
			return "April";
		else if (month == 5)
			return "May";
		else if (month == 6)
			return "June";
		else if (month == 7)
			return "July";
		else if (month == 8)
			return "August";
		else if (month == 9)
			return "September";
		else if (month == 10)
			return "October";
		else if (month == 11)
			return "November";
		else if (month == 12)
			return "December";	
	}

	//Used to Print te leap years
	void printLeapYears(int from,int to)
	{
		
		for (int i = from; i <= to; i++)
		{
			if (checkLeapYear(i))
				cout << i << "	";
			if (i % 20 == 0)
				cout << endl;
		}
	}

};


// Event Node to get the evrnt details
class Event
{
	// Variables
	string title;
	string description;
	int day, month, year;
	string location;

	// Pointers to store node on in tree data structure
	Event* left, * right,*parent;
public:

	// Constructor
	Event() : title(""), description(""), location(""), day(0), month(0), year(0),left(NULL), right(NULL), parent(NULL) {};
	
	// Friend Functions to access the privates variable of the Event node
	friend Event* newEvent(string title, string description, int day, int month, int year, string location);
	friend Event* binarySearchTree(Event* root, Event* newNode);
	friend void inorderTraversal(Event* root);
	friend void pushingElemetsInQueue(Event* root);
	friend void showSchedule(Event* root);
	friend void showDetails(Event* det);
	friend Event* deleteEvent(Event* root, int day, int month, int year);
	friend Event* minValueNode(Event* root);
	friend void UpdateAnEvent(Event* root);
	friend void EditDetails(Event* root);

	/* if you dont want to make friend functions you can simply 
		put variables in the public section */
};


// Function to set the values in the node and get that node address
Event* newEvent(string title,string description,int day,int month,int year,string location)
{
	Event* newNode = new Event();
	newNode->title = title;
	newNode->description = description;
	newNode->location = location;
	newNode->day = day;
	newNode->month = month;
	newNode->year = year;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

// Function to Take input of the event
Event* eventData()
{
	string title, description, location;
	int day, month=0, year=0;

	cout << "Enter the Title : ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter the Description : ";
	cin >> ws;
	getline(cin, description);
	cout << "Enter the location : ";
	cin >> ws;
	getline(cin, location);
	cout << "Enter the day : ";
	cin >> day;
	cout << "Enter the month : ";
	cin >> month;
	cout << "Enter the year : ";
	cin >> year;

	// to set values of the event
	return newEvent(title, description, day, month, year, location);
}


// Putting the nodes in the tree data Structure
Event* binarySearchTree(Event* root,Event *newNode)
{
	if (root == NULL)
	{
		return newNode;
	}
	else if (root->year >= newNode->year)
	{
		/* Dont Worry After Seeing this 
			These are used to set the smallest year 
			then smallest month and then smallest day at the left */

		// Condition to Take years to left
		if (root->year == newNode->year)
		{
			// Condition to Take months to left
			if (root->month >= newNode->month)
			{
				//Condition to Take days to left
				if(root->day > newNode->day)
					root->left = binarySearchTree(root->left, newNode);
				else
					root->right = binarySearchTree(root->right, newNode);
			}
			else
			{
				root->right = binarySearchTree(root->right, newNode);
			}
		}
		else
			root->left = binarySearchTree(root->left, newNode);
	}
	else 
	{
		root->right = binarySearchTree(root->right, newNode);
	}
	
		return root;

}

// Function to get the Sorted event from the past date to future date
void inorderTraversal(Event* root)
{
	if (root == NULL)
		return;

	inorderTraversal(root->left);
	cout << root->day << endl;
	inorderTraversal(root->right);

}


// Quenode class to manage the Events using Queues

class QueNode
{
public:
	// Stores address of event
	Event* address;
	// Stores address of the node in the queue
	QueNode* next;

	// Constructor 
	QueNode() 
	{
		address  = NULL;
		next = NULL;
	}
};


// Queuw Class to make Queues of the QueNodes
class Queue
{
	// Pointers to stores address
	QueNode* front, * rear;
public:
	// Constructor
	Queue()
	{
		front = rear = NULL;
	}


	// To add items in the Queue
	void enQueue(Event* obj)
	{
		QueNode *que = new QueNode;
		que->address = obj;
		que->next = NULL;

		if (front == NULL)
			front = que;
		else
			rear->next = que;

		rear = que;
	}

	// To remove items from the queue
	Event* deQueue()
	{
		Event* temp = NULL;
		if(front != NULL)
		{
			temp = front->address;
			front = front->next;
		}
		return temp;
	}


	// Friend Function to accesss the private variables 
	friend void showEvent(int num);
	friend void UpdateAnEvent(Event* root);
};


// Function to make tilte -- Just for designing
void title(string titlename)
{
	cout << "**************************************************\n";
	cout << "|" << setw(30) << titlename << setw(20) << "  |\n";
	cout << "**************************************************\n\n";
}

// Creating Global Queue object to Access by other Functions
// You can also do it by passing obj to the functions
Queue obj;


// Function to put all the Events in the queue by passing tree head
void pushingElemetsInQueue(Event * root)
{
	if (root == NULL)
		return;

	pushingElemetsInQueue(root->left);
	obj.enQueue(root);
	pushingElemetsInQueue(root->right);
	
}


// Function to print the event details
void showDetails(Event* det)
{
	system("cls");
	title(det->title + "Details");
	cout << endl;
	cout << "Date : " << det->day << " - " << det->month << " - " << det->year << endl;
	cout << "Title : " << det->title << endl;
	cout << "Location : " << det->location << endl;
	cout << "Description : " << det->description << endl;

	cout << "\nPress any key to exit : ";

	// Used to stay on console until key is pressed
	char ch = _getch();
}

// Function to show all the Event nodes in the Queue
void showEvent(int num)
{
	// to get the Queue head
	QueNode* temp = obj.front;

	// For Printing details
	if (num == 1)
	{
		showDetails(temp->address);
	}
	else
	{
		for (int i = 1; i < num && temp != NULL; i++)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Invalid Entry.\n";
		}
		else
		{
			showDetails(temp->address);
		}
	}

	Event* temporary = obj.deQueue();

	while (temporary != NULL)
	{
		temporary = obj.deQueue();
	}

}


// Functions to show only the All Events Date and time and title
void showSchedule(Event * root)
{
	calender caobj;
	system("cls");
	title("Show Events");
	
	//Pusing Elements in Queue 
	pushingElemetsInQueue(root);
	Event* temp = obj.deQueue();
	int i = 1;
	while(temp != NULL)
	{ 
		cout << endl;
		cout << i << " . \n";
		cout << "Date : " << caobj.monthname(temp->month) << " " << temp->day << ", " << temp->year << endl;
		cout << "Title : " << temp->title << endl;
		i++;
		temp = obj.deQueue();
	}

	// These are used to show the event details by selecting the Selective number 
	int num = 0;
	cout << "\nEnter the number to see event details : ";
	cin >> num;
	pushingElemetsInQueue(root);
	showEvent(num);
}

// Same like _getch() function
void exit()
{
	char ch;
	cout << "Enter any key to exit : ";
	cin >> ch;
}

// Function to get the selective month
void CurrentDate(calender obj)
{
	system("cls");
	title("Current Date");
	cout << "Date : " << obj.monthname(cmonth) << "  " << cday << ", " <<  cyear << endl << endl;

	obj.showMonth(cmonth, cyear);
	cout << "Press any key to exit : ";
	char ch = _getch();
}

// Function to show the selective year
void ShowMonth(calender obj)
{
	int year = 0;

	do
	{
		system("cls");
		title("Months");
		cout << "Enter a year between 1900 and 2100 : ";
		cin >> year;

		if (year >= 1900 && year <= 2100)
		{
			for (int i = 1; i <= 12; i++)
			{
				obj.showMonth(i, year);
				cout << "\n\n";
			}
			cout << "Press any key to exit.\n";
			char ch = _getch();
			break;
		}
		else
		{
			cout << "Invalid Input.";
			cout << "Press any key to enter.\n";
			char ch = _getch();
		}

	} while (true);
}


// Function to show a selected date
void SelectedDate(calender obj)
{
	int year = 0,month = 0;

	do
	{
		system("cls");
		title("Selected Month");
		cout << "Enter a year between 1900 and 2100 : ";
		cin >> year;
		cout << "Enter the month (1 to 12) : ";
		cin >> month;

		if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12)
		{
			obj.showMonth(month, year);
			cout << "Press any key to exit.\n";
			char ch = _getch();
			break;
		}
		else
		{
			cout << "Invalid Input.";
			cout << "Press any key to enter.\n";
			char ch = _getch();
		}

	} while (true);
}


// Function to add event in the tree
Event* AddEvent(Event * root)
{
	system("cls");
	title("Add Event");
	root = binarySearchTree(root, eventData());
	cout << "\nEvent Added Successfully.\n";
	cout << "Press any key to exit.";
	char ch = _getch();
	return root;
}


// Function to find the minimum event  in the tree
Event* minValueNode(Event* root)
{
	Event* Current = root;

	while (Current && Current->left != NULL)
	{
		Current = Current->left;
	}

	return  Current;
}


// Function to delete the event
Event* deleteEvent(Event* root,int day,int month,int year)
{
	if (root == NULL)
	{
		return root;
	}
	else if (root->year > year)
	{
		root->left = deleteEvent(root->left, day,month,year);
	}
	else if (root->year < year)
	{
		root->right = deleteEvent(root->right, day, month, year);
	}
	else
	{
		if (root->month > month)
		{
			root->left = deleteEvent(root->left, day, month, year);
		}
		else if (root->month< month)
		{
			root->right = deleteEvent(root->right, day, month, year);
		}
		else
		{
			if (root->day > day)
			{
				root->left = deleteEvent(root->left, day, month, year);
			}
			else if (root->day < day)
			{
				root->right = deleteEvent(root->right, day, month, year);
			}
			else
			{
				if (root->left == NULL) {
					Event* temp = root->right;
					delete root;
					root = NULL;
					return temp;
				}
				else if (root->right == NULL) {
					Event* temp = root->left;
					delete root;
					root = NULL;
					return temp;
				}

				
				Event* temp = minValueNode(root->right);

				root->day = temp->day;
				root->month = temp->month;
				root->year = temp->year;
				root->title = temp ->title;
				root->description = temp->description;
				root->location = temp->location;

				root->right = deleteEvent(root->right, temp->day, temp->month, temp->year);
				
			}
		}
	}
	return root;
}

// Function to delete the selected event
Event* deleteAnEvent(Event* root)
{
	system("cls");
	title("Delete An Event");

	showSchedule(root);
	int day, month, year;
	cout << "\n\nEnter the day : ";
	cin >> day;
	cout << "Enter the month : ";
	cin >> month;
	cout << " Enter the Year : ";
	cin >> year;
	
	root = deleteEvent(root,day,month,year);
	return root;
}


// Function to edit the event details
void EditDetails(Event* root)
{
	system("cls");
	title("Edit Details");
	string title, description, location;
	int day, month = 0, year = 0;

	cout << "Enter the Title : ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter the Description : ";
	cin >> ws;
	getline(cin, description);
	cout << "Enter the location : ";
	cin >> ws;
	getline(cin, location);
	cout << "Enter the day : ";
	cin >> day;
	cout << "Enter the month : ";
	cin >> month;
	cout << "Enter the year : ";
	cin >> year;

	root->day = day;
	root->month = month;
	root->year = year;
	root->title = title;
	root->description = description;
	root->location = location;

	cout << "Event updated successfully\n";
	char ch = _getch();
}

// Function to update the node in the tree
void UpdateAnEvent(Event* root)
{
	calender caobj;
	system("cls");
	title("Show Events");
	pushingElemetsInQueue(root);
	Event* temp = obj.deQueue();
	int i = 1;

	// First Show all events
	while (temp != NULL)
	{
		cout << endl;
		cout << i << " . \n";
		cout << "Date : " << caobj.monthname(temp->month) << " " << temp->day << ", " << temp->year << endl;
		cout << "Title : " << temp->title << endl;
		i++;
		temp = obj.deQueue();
	}

	// Input the  number to edit the event schedule
	int num = 0;
	cout << "\nEnter the number to Edit An Event : ";
	cin >> num;
	pushingElemetsInQueue(root);

	QueNode* temporary = obj.front;
	if (num == 1)
	{
		EditDetails(temporary->address);
	}
	else
	{
		for (int i = 1; i < num && temporary != NULL; i++)
		{
			temporary = temporary->next;
		}
		if (temporary == NULL)
		{
			cout << "Invalid Entry.\n";
		}
		else
		{
			EditDetails(temporary->address);
		}
	}

	Event* temporary2 = obj.deQueue();

	while (temporary2 != NULL)
	{
		temporary2 = obj.deQueue();
	}

}


// Mian function
int main()
{
	calender obj;

	// Root for the tree
	Event* root = NULL;
	int num = 0;

	// Running the code until exit is selected
	do
	{
		// Use to clear the screen
		system("cls");

		// Use to print title
		title("Calender");

		cout << "1. Current Date.\n";
		cout << "2. Show Months.\n";
		cout << "3. Selected Date.\n";
		cout << "4. Add Event.\n";
		cout << "5. Show Events.\n";
		cout << "6. Delete Events.\n";
		cout << "7. Update Events.\n";
		cout << "8.Exit\n\n";

		int num;
		cout << "Enter the choice : ";
		cin >> num;

		// To run the selected function using switch
		switch (num)
		{
		case 1:CurrentDate(obj); break;
		case 2:ShowMonth(obj); break;
		case 3:SelectedDate(obj); break;
		case 4:root = AddEvent(root); break;
		case 5:showSchedule(root); break;
		case 6:root = deleteAnEvent(root); break;
		case 7:UpdateAnEvent(root); break;
		case 8:break;
		default: cout << "Invalid input.\n";
		}

		// if user selected the exit it ends the close
		if (num == 8)
			break;

	} while (true);

	return 0;
}

// Note

/* This Project is made for the Data Structure 
----
-LinkedList
-Queues
-Trees
----
Calender */