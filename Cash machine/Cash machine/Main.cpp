#include "Functions.h"
#include <thread>
#include <Windows.h>
#include <stdio.h>

using namespace std;

int main()
{
	thread p2(process2);
	map <char *, unsigned int> request;

	while (true)
	{
		request["account"] = MIN_ACCOUNT + rand() % (MAX_ACCOUNT - MIN_ACCOUNT) + 1;
		request["request"] = MIN_REQUEST + rand() % (MAX_REQUEST - MIN_REQUEST) + 1;

		process1(request);

		output();

		Sleep(300);
	}
	p2.join();

	return 0;
}

