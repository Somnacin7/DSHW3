
#include <iostream>
#include <string>

using namespace std;

class Email {
	string to;
	string from;
	string message;

	Email* newer;
	Email* older;
};

class Communication {
	string subject;
	int numOfEmails;
	Email* newestEmail;

	Communication* newer;
	Communication* older;
};

class Inbox {

};

int main() {
	return 0;
}