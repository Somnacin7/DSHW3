
#include <iostream>
#include <string>

using namespace std;

class Email {
private:
	string to;
	string from;
	string message;

	Email* newer;
	Email* older;

public:
};

class Communication {
private:
	string subject;
	int numOfEmails;
	Email* newestEmail;

	Communication* newer;
	Communication* older;
public:
};

class Inbox {
	void InsertEmail(Email*);

	bool DeleteCommunication(string subject);

	void DisplayInbox();
	
private:
	Communication* SearchCommunicaton(string subject);

};

int main() {
	return 0;
}