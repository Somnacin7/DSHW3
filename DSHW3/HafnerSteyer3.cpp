
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
	int size() {
		return numOfEmails;
	}


};

class Inbox {
private:
	Communication* SearchCommunicaton(string subject);

	Inbox(Inbox& other);
	~Inbox();

public:
	void InsertEmail(Email*);

	bool DeleteCommunication(string subject);

	void DisplayInbox();



};

int main() {
	return 0;
}