#include "FileManager.h"
#include "User.h"
#include <iostream>

using namespace std;

void FileManager::getFilesData(list<SarahaUsers>& users, list<Contact>& contacts, stack<Message>& messages, queue<Message>& favoriteMessages) {
	// Read Data From Files
	fstream readData;
	readData.open("sarahaUsers.txt", ios::in);
	string line;
	SarahaUsers TempUser;
	while (true) {
		getline(readData, line);
		if (line == "")break;
		vector<string> values = splitLine(line);
		TempUser.username = values[0];
		TempUser.password = values[1];
		TempUser.ID = values[2];
		users.push_back(TempUser);
	}
	readData.close();

	Contact TempContact;
	readData.open("contacts.txt", ios::in);
	while (true) {
		getline(readData, line);
		if (line == "")break;
		vector<string> values = splitLine(line);
		TempContact.myID = values[0];
		TempContact.contactID = values[1];
		TempContact.contactUsername = values[2];
		contacts.push_back(TempContact);
	}
	readData.close();

	Message TempMessages;
	readData.open("messages.txt", ios::in);
	while (true) {
		getline(readData, line);
		if (line == "")break;
		vector<string> values = splitLine(line);
		TempMessages.sender = values[0];
		TempMessages.reciever = values[1];
		TempMessages.message = values[2];
		messages.push(TempMessages);
	}
	readData.close();

	Message TempFavoriteMessages;
	readData.open("favoriteMessages.txt", ios::in);
	while (true) {
		getline(readData, line);
		if (line == "")break;
		vector<string> values = splitLine(line);
		TempFavoriteMessages.sender = values[0];
		TempFavoriteMessages.reciever = values[1];
		TempFavoriteMessages.message = values[2];
		favoriteMessages.push(TempFavoriteMessages);
	}
	readData.close();
}

void FileManager::setSarahaUsers(list<SarahaUsers> users) {
	// Write Data From Files
	fstream WriteData;
	WriteData.open("sarahaUsers.txt", std::fstream::out | std::fstream::trunc);
	list<SarahaUsers>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		WriteData << it->username << "," << it->password << "," << it->ID << endl;
	}
	WriteData.close();
}

void FileManager::setContact(list<Contact> contacts) {
	list <Contact> ::iterator it;
	fstream WriteData;
	WriteData.open("contacts.txt", std::fstream::out | std::fstream::trunc);
	for (it = contacts.begin(); it != contacts.end(); it++) {
		WriteData << it->myID << "," << it->contactID << "," << it->contactUsername << endl;
	}
	WriteData.close();

}

void FileManager::setMessage(stack<Message> messages)
{
	list<Message> msgs;
	while (!messages.empty()) {
		msgs.push_back(messages.top());
		messages.pop();
	}
	msgs.reverse();
	fstream WriteData;
	WriteData.open("messages.txt", std::fstream::out | std::fstream::trunc);
	list<Message>::iterator it;
	for (it = msgs.begin(); it != msgs.end(); it++) {
		WriteData << it->sender << "," << it->reciever << "," << it->message << endl;

	}
	WriteData.close();
}

void FileManager::setFavoriteMessage(queue<Message> favoriteMessages)
{
	queue<Message> copyFavMessages = favoriteMessages;
	fstream WriteData;
	WriteData.open("favoriteMessages.txt", std::fstream::out | std::fstream::trunc);
	while (!copyFavMessages.empty())
	{
		WriteData << copyFavMessages.front().sender << "," << copyFavMessages.front().reciever << "," << copyFavMessages.front().message << endl;
		copyFavMessages.pop();
	}
	WriteData.close();
}


//void FileManager::setFilesData(vector<SarahaUsers> users, vector<Contact> contacts, vector<Message> messages, vector<Message> favoriteMessages) {
//	// Write Data From Files
//	fstream WriteData;
//	WriteData.open("sarahaUsers.txt", std::fstream::out|std::fstream::trunc);
//	for (int i = 0;i < users.size();i++) {
//		WriteData << users[i].username << "," << users[i].password << "," << users[i].ID << endl;
//	}
//	WriteData.close();
//
//	WriteData.open("contacts.txt", std::fstream::out | std::fstream::trunc);
//	for (int i = 0;i < contacts.size();i++) {
//		WriteData << contacts[i].ID << "," << contacts[i].username << endl;
//	}
//	WriteData.close();
//
//
//	WriteData.open("messages.txt", ios::in);
//	for (int i = 0;i < messages.size();i++) {
//		WriteData << messages[i].sender << "," << messages[i].reciever << "," << messages[i].message << endl;
//	}
//	WriteData.close();
//
//	WriteData.open("favoriteMessages.txt", ios::in);
//	for (int i = 0;i < favoriteMessages.size();i++) {
//		WriteData << favoriteMessages[i].sender << "," << favoriteMessages[i].reciever << "," << favoriteMessages[i].message << endl;
//	}
//	WriteData.close();
//}








vector<string> FileManager::splitLine(string line) {
	vector<string> values;
	stringstream s_stream(line);
	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, ',');
		values.push_back(substr);
	}
	return values;
}