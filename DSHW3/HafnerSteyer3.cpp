
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
		this->newer = NULL;
		this->older = NULL;
	}

	// Getters
	string getTo() { return to; }
	string getFrom() { return from; }
	string getMessage() { return message; }

	// pointers to the next and previous emails
	Email* newer;
	Email* older;
};


// Communication class
class Communication {
private:
	string subject;
	int numOfEmails;

	// pointer to head of linked list of emails
	Email* newestEmail;

public:
	// pointers to next and previous communications
	Communication* newer;
	Communication* older;

	// constructor
	Communication(string subject, Email* email) {
		this->subject = subject;
		newestEmail = email;
		newestEmail->newer = NULL;
		newestEmail->older = NULL;
		numOfEmails = 1;
	}

	// copy constructor
	Communication(Communication& other) {
		this->newer = other.newer;
		this->older = other.older;
		this->subject = other.subject;
		this->numOfEmails = other.numOfEmails;
		this->newestEmail = other.newestEmail;
	}

	// This function adds an email at the head of the list
	void newEmail(Email* email) {
		email->older = newestEmail;
		newestEmail = email;
		newestEmail->newer = NULL;
		numOfEmails++;
	}

	// Getters
	string getSubject() { return subject; }
	int size() { return numOfEmails; }

	 // Destructor
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
	// this function returns a pointer to the communication with the given subject
	Communication* searchCommunicaton(string subject) {
		Communication* comm = top;
		while (comm != NULL) {
			if (comm->getSubject() == subject) {
				return comm;
			}
			comm = comm->older;
		}
		// if no such communication exists, return NULL
		return NULL;
	}

	// pointers to the head and tail of the list of communications
	Communication* top;
	Communication* bottom;

public:
	// constructor
	Inbox() {
		top = NULL;
		bottom = NULL;
	}

	// copy constructor
	Inbox(Inbox& other) {
		top = other.top;
		bottom = other.bottom;
	}

	// This function adds a new email to its corresponding communication,
	// or creates a new communication if one does not exist.
	// Most recently updated communications are moved to the top of the inbox.
	void insertEmail(Email* email, string subject) {

		// search for a communication with the given subject to place the email in
		Communication* comm = searchCommunicaton(subject);

		if (comm != NULL) { // if a communication already exists
			comm->newEmail(email);

			// if not already there, move the communication to the top of the inbox
			if (comm->newer != NULL) {
				if (comm->older != NULL) {
					(comm->older)->newer = comm->newer;
				}
				else {
					this->bottom = comm->newer;
				}
				(comm->newer)->older = comm->older;
				comm->older = this->top;
				comm->newer = NULL;
				(this->top)->newer = comm;
				this->top = comm;
			}
		}
		else {
			// create a new communication if one does not exist
			comm = new Communication(subject, email);

			// place the new communication at the top of the inbox
			if (this->top != NULL) {
				(this->top)->newer = comm;
			}
			comm->older = this->top;
			comm->newer = NULL;
			this->top = comm;
			if (this->bottom == NULL) {
				this->bottom = comm;
			}
		}
	}
	
	// this function deletes a communication and returns true if successful, false otherwise
	bool deleteCommunication(string subject) {
		Communication* comm = searchCommunicaton(subject);
		if (comm != NULL) {
			Communication* newer = comm->newer;
			Communication* older = comm->older;

			newer->older = older;
			older->newer = newer;

			delete comm;

			return true;
		}
		// return false if no such communication was found
		return false;
	}

	// this function displays the inbox in order and lists the number of emails
	void displayInbox() {
		if (top != NULL) {
			Communication* curComm = top;

			// get total number of emails
			int size = 0;
			while (curComm != NULL) {
				size += curComm->size();
				curComm = curComm->older;
			}
			
			cout << "\nInbox: total number of emails is " << size << endl << endl;

			// list communications and the number of emails in each one
			curComm = top;
			while (curComm != NULL) {
				cout << curComm->getSubject() << " - " << curComm->size() << endl;
				curComm = curComm->older;
			}
			cout << endl;
		}
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
	

	cout << "Enter email subjects one at a time (press enter after each one)." << endl;
	cout << "When you are finished, enter the word 'done'" << endl << endl;
	
	// get subjects from user
	while (getline(cin, subject) && subject != "done") {
		myInbox.insertEmail(new Email("recipient", "sender", "text"), subject);
		
	}


	//display inbox
	myInbox.displayInbox();

	system("pause");
	return 0;
}