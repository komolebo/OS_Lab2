#include "Functions.h"
#include <iostream>
#include <Windows.h>

using namespace std;

const unsigned int CURR[7] = { 1, 2, 5, 10, 20, 50, 100 };			// Possible currency in ua
unsigned int cur_number[7] = { 100, 100, 100, 100, 100, 100, 10000 };	// Different currency money of cash machine
Mailbox mailbox;													// Mailbox to synchonize

void process1(map <char *, unsigned int> & request)
{
	cout << "Process1: request = " << request["request"] << "/" << request["account"] << endl;
	if (request["request"] > request["account"])
		cout << "Process1: Denied. Not enough money on account." << endl;
	else
	{
		if (mailbox.buffer.size() >= mailbox.N_MAX)
			cout << "Process1: Buffer is already full." << endl;
		else
		{
			mailbox.buffer.push_back(request["request"]);
			cout << "Process1: Request added to buffer." << endl;
		}
	}
}

void process2()
{
	while (true)
	{
		if (mailbox.buffer.size())
		{
			unsigned int money = mailbox.buffer.front(), money_counted = 0;	// Money to give

			int tmp[7] = { 0, 0, 0, 0, 0, 0, 0 };			// Array of currency to give

			for (int i = 6; i >= 0 && money - money_counted; --i)			// Find currency
			{
				unsigned int n = (money - money_counted) / CURR[i];

				tmp[i] += min(n, cur_number[i]);
				money_counted += min(n, cur_number[i]) * CURR[i];
			}

			if (money == money_counted)
			{
				for (int i = 0; i < 7; i++)
					cur_number[i] -= tmp[i];

				cout << "Process2: succeed outcome " << money << endl;
			}
			else
				cout << "Process2: Denied. No currency" << endl;

			mailbox.buffer.pop_front();
		}
		Sleep(500);
	}
}

void output()
{
	cout << "Buffer: " << mailbox.buffer.size() << endl;

	for (int i = 6; i >= 0; --i)
		cout << '\t' << cur_number[i] << " x " << CURR[i] << " ua" << endl << endl;
}