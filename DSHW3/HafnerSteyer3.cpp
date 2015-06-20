
#include <iostream>
#include <string>

using namespace std;

// Email class
class Email {
private:
	string to;
	string from;
	string message;

public:
	// constructor
	Email(string to, string from, string message) {
		this->to = to;
		this->from = from;
		this->message = message;
	}

	Email* newer;
	Email* older;
};

// Communication class
class Communication {
private:
	string subject;
	int numOfEmails;
	Email* newestEmail;

	Communication* newer;
	Communication* older;

public:
	// constructor
	Communication(string subject, Email* email) {
		this->subject = subject;
		newestEmail = email;
		newestEmail->newer = NULL;
		newestEmail->older = NULL;
	}

	void InsertEmail(Email* email) {
		email->older = newestEmail;
		newestEmail = email;
		newestEmail->newer = NULL;
	}

	string getSubject() {
		return subject;
	}

	Communication* getNewer() {
		return newer;
	}

	Communication* getOlder() {
		return older;
	}
};

// Inbox class
class Inbox {
private:
	Communication* SearchCommunicaton(string subject) {
		Communication* comm = top;
		while (comm != NULL) {
			if (comm->getSubject() == subject) {
				return comm;
			}
			comm = comm->getOlder();
		}
		return NULL;
	}

	Communication* top;
	Communication* bottom;

public:
	void InsertEmail(Email* email, string subject) {

		// search for a communication with the given subject to place the email in
		Communication* comm = SearchCommunicaton(subject);
		if (comm != NULL) {
			comm->InsertEmail(email);

			// move the communication to the top of the inbox

		}
		else {
			// create a new communication
			comm = new Communication(subject, email);

			// place the new communication at the top of the inbox
			comm
		}
	}

	bool DeleteCommunication(string subject) {

	}

	void DisplayInbox() {

	}
};

int main() {
	string subject = "";
	Inbox myInbox;
	Email mail("recipient", "sender", "text");
	Communication comm((string)"sub", &mail);

	cout << "Enter email subjects one at a time (press enter after each one)." << endl;
	cout << "When you are finished, enter the word 'done'" << endl << endl;
	
	// get subjects from user
	while (getline(cin, subject) && subject != "done") {
		myInbox.InsertEmail(&mail, subject);
		
	}

	//display inbox
	myInbox.DisplayInbox();

	return 0;
}