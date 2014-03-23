#pragma once
#include <vector>
#include <string>
using namespace std;

class gamelog{
public:
	void logSetup();
	void findItem(string item);
	void fight(string attkr, string defnr);
	string getLogForOutput();

private:
	vector<string> Log;
};