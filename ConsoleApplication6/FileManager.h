#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <stack>
#include <queue>

using namespace std;
struct Message {
	string sender;
	string reciever;
	string message;
};
struct Contact {
	string myID;
	string contactID;
	string contactUsername;
};
struct SarahaUsers {
	string username;
	string password;
	string ID;
};
#pragma once
class FileManager
{
public:
	static void getFilesData(list<SarahaUsers>& users, list<Contact>& contacts, stack<Message>& messages, queue<Message>& favoriteMessages);
	static void setSarahaUsers(list<SarahaUsers>);
	static void setContact(list<Contact>);
	static void setMessage(stack<Message>);
	static void setFavoriteMessage(queue<Message>);

	static vector<string> splitLine(string line);
};

