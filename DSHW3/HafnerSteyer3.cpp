
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

	
	// Getters
	string getTo() { return to; }
	string getFrom() { return from; }
	string getMessage() { return message; }


	Email* newer;
	Email* older;
	
};

// Communication class
class Communication {
private:
	string subject;
	int numOfEmails;
	Email* newestEmail;

	

public:
	Communication* newer;
	Communication* older;

	// constructor
	Communication(string subject, Email* email) {
		this->subject = subject;
		newestEmail = email;
		newestEmail->newer = NULL;
		newestEmail->older = NULL;
	}


		
	// Add an email at the head
	void InsertEmail(Email* email) {
		email->older = newestEmail;
		newestEmail = email;
		newestEmail->newer = NULL;
	}

	// Getters
	string getSubject() { return subject; }
	int size() { return numOfEmails; }

	// Destructors
	~Communication() {
		Email* emailTmp = newestEmail;
		Email* emailTmp2 = newestEmail;
		while (emailTmp != NULL) {
			emailTmp2 = emailTmp;
			emailTmp = emailTmp->older;
			delete emailTmp2;
		}
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
			comm = comm->older;
		}
		return NULL;
	}

	Communication* top;
	Communication* bottom;

public:
	Inbox() {

	}



	void InsertEmail(Email* email, string subject) {

		// search for a communication with the given subject to place the email in
		Communication* comm = SearchCommunicaton(subject);
		if (comm != NULL) {
			comm->InsertEmail(email);
		} else {
			// create a new communication
			comm = new Communication(subject, email);

			// place the new communication at the top of the inbox
			comm
		}
	}
	
	// return true if successful, false for failure
	bool DeleteCommunication(string subject) {
		Communication* comm = SearchCommunicaton(subject);
		if (comm != NULL) {
			Communication* newer = comm->newer;
			Communication* older = comm->older;

			newer->older = older;
			older->newer = newer;

			delete comm;

			return true;

		}
		return false;
	}

	void DisplayInbox() {

	}

	~Inbox() {
		Communication* commTmp = top;
		Communication* commTmp2 = top;
		while (commTmp != NULL) {
			commTmp2 = commTmp;
			commTmp = commTmp->older;
			delete commTmp2;
		}
	}
};

int main() {
	string subject = "";
	Inbox myInbox;
	Email* mail = new Email("recipient", "sender", "text");
	Communication comm((string)"sub", mail);

	cout << "Enter email subjects one at a time (press enter after each one)." << endl;
	cout << "When you are finished, enter the word 'done'" << endl << endl;
	
	// get subjects from user
	while (getline(cin, subject) && subject != "done") {
		myInbox.InsertEmail(mail, subject);
		
	}

	//display inbox
	myInbox.DisplayInbox();

	return 0;
}