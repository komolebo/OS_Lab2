#include <list>
#include <map>

const unsigned int MAX_ACCOUNT = 10000;
const unsigned int MIN_ACCOUNT = 1000;

const unsigned int MAX_REQUEST = 11000;
const unsigned int MIN_REQUEST = 10;

struct Mailbox
{
	const unsigned int N_MAX = 100;
	std::list<int> buffer;
};

void process1(std::map <char *, unsigned int> & request);
void process2();
void output();