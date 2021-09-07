#include <list>
#include <stack>
#include <iostream>
#include <vector>
#include "User.h"
#include "FileManager.h"

using namespace std;

list<SarahaUsers> users;
list<Contact> contacts;
stack<Message> messages;
queue<Message> favoriteMessages;


void appStart();
bool Login(string& username, string& password, string& id, list<SarahaUsers> users);
void AppDiscription(short int& choice);
void Register(list<SarahaUsers>& users);
void Credits(short int& choice);

int main()
{

	FileManager::getFilesData(users, contacts, messages, favoriteMessages);

	appStart();


}



void appStart() {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tModified-SARAHAH\n";
	cout << "\t\t___________________________________________" << endl << endl;
	short int choice = 0;
	//User currentUser;
	string currentUserUsername = "", currentUserPassword = "", currentUserID = "";
	//User currentUser;
	while (choice != 5) {
		cout << "Please choose one of the following insturctions: " << endl
			<< "1- App Description" << endl
			<< "2- Register" << endl
			<< "3- Log-in" << endl
			<< "4- Credits" << endl
			<< "5- Exit Program" << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			AppDiscription(choice);
			system("cls");
			break;
		case 2:
			system("cls");
			Register(users);
			break;
		case 3:
			system("cls");
			if (Login(currentUserUsername, currentUserPassword, currentUserID, users)) {
				cout << "Successfully Logged in." << endl;
				cout << "______________________________________________" << endl;
				User currentUser = User(currentUserUsername, currentUserPassword, currentUserID, favoriteMessages);
				currentUser.userOptions(users, contacts, messages, favoriteMessages);
			}
			else {
				cout << "Invalid Login" << endl;
			}
			break;
		case 4:
			system("cls");
			Credits(choice);
			break;
		default:
			break;
		}
	}

}

void AppDiscription(short int& choice) {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tAPP DESCRIPTION\n";
	cout << "\t\t___________________________________________" << endl << endl;
	cout << "Modified Sarahah is a website that allows you to send a message in an anonymous way where you dont know anything about the sender except his ID" << endl;
	cout << "1-Return to the start page." << endl
		<< "2-Close the program." << endl
		<< "choice: ";
	cin >> choice;
	choice == 2 ? choice = 5 : choice = 1;
}



void Register(list<SarahaUsers>& users) {
	bool isValid = true;
	SarahaUsers TempUser;
	string username, password;
	cout << "Please enter a username: ";
	cin >> username;
	cout << "Please enter a password: ";
	cin >> password;
	list<SarahaUsers>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (username == it->username) {
			isValid = false;
			break;
		}
	}
	if (isValid) {
		TempUser.username = username;
		TempUser.password = password;
		TempUser.ID = to_string(2000 + users.size());
		users.push_back(TempUser);
		cout << "Successfully Registered." << endl;
	}
	else {
		cout << "Username is Already Exest !!!" << endl;
	}
	FileManager::setSarahaUsers(users);

}

bool Login(string& username, string& password, string& id, list<SarahaUsers> users) {
	bool userFound = false;
	//string enteredUsername, enteredPassword;

	cout << "Please enter a username: ";
	cin >> username;
	cout << "Please enter a password: ";
	cin >> password;
	list<SarahaUsers>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if (username == it->username && password == it->password) {
			id = it->ID;
			userFound = true;
			break;
		}
	}
	return userFound;
}


void Credits(short int& choice) {
	cout << "\t\t___________________________________________" << endl<<"\t\t\t\tCREDITS\n";
	cout << "\t\t___________________________________________" << endl << endl;
	cout << "Team Members:\n1. Zeyad Sultan\n2. Zeyad Elsheikh\n3. SeifEldeen Essam\n4. Sara Mohamed\n5. Rowym Mohamed\n6. SeifEldeen Mostafa\n";
	cout << endl << "1- Return to main page\n2- Close the Program\nChoice: ";
	cin >> choice;
	choice == 2 ? choice = 5 : choice = 1;
}
 
