#include "User.h"
#include <iostream>

using namespace std;

User::User() {}
User::User(string username, string password, string id, queue<Message>& favoriteMessages) {
	this->username = username;
	this->password = password;
	this->ID = id;
	Message TempMessage;
	queue<Message> TempFavoriteMessages = favoriteMessages;
	while (!TempFavoriteMessages.empty()) {
		if (getID() == TempFavoriteMessages.front().reciever) {
			TempMessage.sender = TempFavoriteMessages.front().sender;
			TempMessage.reciever = TempFavoriteMessages.front().reciever;
			TempMessage.message = TempFavoriteMessages.front().message;
			currentUserFavoriteMessages.push(TempMessage);
		}
		TempFavoriteMessages.pop();
	}
}


string User::getID() {
	return this->ID;
}

void User::userOptions(list<SarahaUsers>& users, list<Contact>& contacts, stack<Message>& messages, queue<Message>& favoriteMessages)
{
	short int choice = 0;
	while (choice != 12) {
		cout << "Please choose one of the following insturctions: " << endl
			<< "1- Add Contact." << endl														//Done
			<< "2- view all contacts." << endl													//Done
			<< "3- search for a specific contact." << endl										//Done
			<< "4- send a Message." << endl														//Done
			<< "5- view sent messages." << endl													//Done
			<< "6- undo the last message sent to a contact." << endl
			<< "7- View Received Messages." << endl												//Done
			<< "8- View all the received messages from specfic contact." << endl
			<< "9- Add to favourites." << endl
			<< "10- View Favorite Messages." << endl
			<< "11- Remove the oldest message from favorite." << endl
			<< "12- logout." << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice)
		case 1:
		{
			system("cls");
			addContact(users, contacts);
			break;
		case 2:
			system("cls");
			cout << "\t\t___________________________________________" << endl << "\t\t\t\tView Contacts\n";
			cout << "\t\t___________________________________________" << endl << endl;

			viewContacts(contacts);
			break;
		case 3:
			system("cls");
			searchContact(users, contacts);
			break;
		case 4:
			system("cls");
			sendMessage(contacts, messages);
			break;
		case 5:
			system("cls");
			// We will use stack for messages not vector
			viewSentMessages(messages, users);
			break;
		case 6:
			system("cls");
			undoLastSentMessage(messages, users);
			break;
		case 7:
			system("cls");
			viewReceivedMessages(messages);
			break;
		case 8:
			system("cls");
			//cout << "ID: " << getID() << endl << endl;
			viewReceivedMsgsfromContact(contacts, messages);
			break;
		case 9:
			system("cls");
			addToFavorite(favoriteMessages, messages);
			break;
		case 10:
			system("cls");
			viewFavoriteMessages(favoriteMessages);
			break;
		case 11:
			system("cls");
			RemoveOldestFavoriteMessage(favoriteMessages);
			break;
		default:
			system("cls");
			choice = 12;
			break;
		}
	}
}

void User::addContact(list<SarahaUsers>& users, list<Contact>& contacts)
{
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tAdd Contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	string user;
	//short int choice;
	bool contactFound = false;
	Contact TempContact;
	cout << "Enter the Username you want to add: ";
	cin >> user;
	list <SarahaUsers> ::iterator it;
	// The Updated part to validate the entered user is not in the current user contacts
	bool contactInUserContacts = false;
	list <Contact>::iterator contactIt;
	for (contactIt = contacts.begin(); contactIt != contacts.end(); contactIt++) {
		if (getID() == contactIt->myID && user == contactIt->contactUsername) {
			contactInUserContacts = true;
			break;
		}
	}

	for (it = users.begin(); it != users.end() && !contactInUserContacts; it++) {
		if (user == it->username) {
			TempContact.contactUsername = user;
			TempContact.contactID = it->ID;
			TempContact.myID = getID();
			contacts.push_back(TempContact);
			contactFound = true;
			break;
		}
	}
	if (contactFound)
	{
		cout << "Contact added to your contact list." << endl;
		cout << "_____________________________________________\n";
		FileManager::setContact(contacts);
	}
	//This  else if part is also added with the Updated part to validate.
	else if (contactInUserContacts) {
		cout << "The entered user is already in your contacts." << endl;
	}
	else {
		cout << "User not found in the system." << endl;
	}
}


void User::viewContacts(list<Contact> contacts) {

	list <Contact> ::iterator it;
	for (it = contacts.begin(); it != contacts.end(); it++) {
		if (getID() == it->myID) {
			cout << "Username: " << it->contactUsername << endl;
		}
		
	}
	cout << "_______________________________________________\n";
}

void User::searchContact(list<SarahaUsers>users, list<Contact> contacts) {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tSearch a contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	bool contactFound = false;
	string user;
	cout << "Enter the Username you want to search for: ";
	cin >> user;
	list <Contact> ::iterator it;
	for (it = contacts.begin(); it != contacts.end(); it++) {
		if (user == it->contactUsername && getID()==it->myID) {
			contactFound = true;
			break;
		}
	}
	if (contactFound)
	{
		cout << "Contact is found in your contacts." << endl;

	}
	else {
		cout << "User not found in your contacts." << endl;
	}
}

void User::sendMessage(list<Contact> contacts, stack<Message>& messages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\t\tSend Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	string contactUsername;
	Message TempMessage;
	bool inContacts = false;
	cout << "Enter the username of the user to send to: ";
	cin >> contactUsername;
	list <Contact> ::iterator it;
	for (it = contacts.begin(); it != contacts.end(); it++) {
		if (getID() == it->myID && contactUsername == it->contactUsername) {
			TempMessage.sender = getID();
			TempMessage.reciever = it->contactID;
			inContacts = true;
			break;
		}
	}
	if (inContacts) {
		cout << "Enter the message: ";
		cin.ignore();
		getline(cin, TempMessage.message);
		messages.push(TempMessage);
		FileManager::setMessage(messages);
	}
	else {
		cout << "This user is not in your contacts" << endl;
	}
}

void User::viewSentMessages(stack<Message> messages, list<SarahaUsers>users) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Sent Messages\n";
	cout << "\t\t___________________________________________" << endl << endl;

	while (!messages.empty()) {
		if (getID() == messages.top().sender) {
			cout << "The message is sent to: " << getUsername(messages.top().reciever, users) << endl
				<< "The message: " << messages.top().message << endl;
		}
		messages.pop();
	}
}

void User::undoLastSentMessage(stack<Message>& messages, list<SarahaUsers>users)
{
	cout << "\t\t___________________________________________" << endl << "\t\t\tUndo Last Sent Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	messages.pop();
	cout << "Last sent message undoed\n";
	cout << "last sent messages after deleting last sent one:\n";
	viewSentMessages(messages, users);
	FileManager::setMessage(messages);
}

string User::getUsername(string id, list<SarahaUsers>users) {

	list <SarahaUsers> ::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		if (id == it->ID) {
			return it->username;
		}
	}
}

void User::viewReceivedMessages(stack<Message> messages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Received Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	while (!messages.empty()) {
		if (messages.top().reciever == getID()) {
			cout << "The message sent From: " << messages.top().sender << endl
				<< "The message: " << messages.top().message << endl;
			cout << "__________________\n";
		}
		messages.pop();
	}
	cout << "____________________________________________________________\n";
}
void User::viewReceivedMsgsfromContact( list<Contact>contacts, stack<Message> messages ) {
	cout << "\t\t___________________________________________" << endl << "\t\tMy Received Messages from a specific contact\n";
	cout << "\t\t___________________________________________" << endl << endl;

	cout << "Contacts: " << endl;
	viewContacts(contacts);
	cout << endl;
	bool found = false;
		list<Contact>::iterator it;

		while (!found) 
		{
			cout << "_____________________________________" << endl;
			cout << "Enter the contact name: ";
			Contact cnt;
			cin >> cnt.contactUsername;
			for (it = contacts.begin(); it != contacts.end(); it++) {
				if (cnt.contactUsername == it->contactUsername && getID() == it->myID) {
					cnt.contactID = it->contactID;
					found = true;
					break;
				}
			}
			if (found) {
				while (!messages.empty()) {
					if (cnt.contactID == messages.top().sender && getID() == messages.top().reciever) {
						cout << "The message: " << messages.top().message << endl;
					}
					messages.pop();
				}
			}
			else {
				cout << "User is not in your contacts please choose one from the above" << endl;
			}
	    }
		
}


void User::viewFavoriteMessages(queue<Message> favoriteMessages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tMy Favorite Messages\n";
	cout << "\t\t___________________________________________" << endl << endl;

	queue<Message> secondaryQueue = currentUserFavoriteMessages;
	while (!secondaryQueue.empty()) {
		cout << "The message was sent from: " << secondaryQueue.front().sender << endl
			<< "The message: " << secondaryQueue.front().message << endl;
		secondaryQueue.pop();
	}
}

void User::addToFavorite(queue<Message>& favoriteMessages, stack<Message> messages) {
	cout << "\t\t___________________________________________" << endl << "\t\t\tAdd to Favorite\n";
	cout << "\t\t___________________________________________" << endl << endl;

	queue<Message> secondaryMessages1;

	while(!messages.empty()){
		if (getID() == messages.top().reciever) {
			secondaryMessages1.push(messages.top());
		}
		messages.pop();
	}
	queue<Message> secondaryMessages2 = secondaryMessages1;
	int i = 0;
	while(!secondaryMessages1.empty()) {
		cout << i + 1 << "- " << secondaryMessages1.front().message << endl;
		secondaryMessages1.pop();
		i++;
	}
	short int messageNum;
	cout << "Please enter the number of the message you want to add to the Favorite: ";
	cin >> messageNum;
	i = 0;
	if (messageNum > 0 && messageNum <= secondaryMessages2.size()) {
		while (!secondaryMessages2.empty()) {
			i++;
			if (i == messageNum) {
				favoriteMessages.push(secondaryMessages2.front());
				currentUserFavoriteMessages.push(secondaryMessages2.front());
			}
			secondaryMessages2.pop();
		}
		FileManager::setFavoriteMessage(favoriteMessages);
	}
	else {
		cout << "You entered a wrong number." << endl;
	}

}

void User::RemoveOldestFavoriteMessage(queue<Message>& favoriteMessages) {
	cout << "\t\t___________________________________________" << endl << "\t\tRemove Oldest Favorite Message\n";
	cout << "\t\t___________________________________________" << endl << endl;

	Message TempRemovedMessage = currentUserFavoriteMessages.front();
	currentUserFavoriteMessages.pop();
	queue<Message> secondaryQueue1 = favoriteMessages;
	queue<Message> secondaryQueue2;
	while (!secondaryQueue1.empty()) {
		if (secondaryQueue1.front().sender == TempRemovedMessage.sender && secondaryQueue1.front().reciever == TempRemovedMessage.reciever && secondaryQueue1.front().message == TempRemovedMessage.message) {
			secondaryQueue1.pop();
			continue;
		}
		secondaryQueue2.push(secondaryQueue1.front());
		secondaryQueue1.pop();
	}
	favoriteMessages = secondaryQueue2;
	FileManager::setFavoriteMessage(favoriteMessages);
	cout << "The oldest message successfully deleted." << endl;
}