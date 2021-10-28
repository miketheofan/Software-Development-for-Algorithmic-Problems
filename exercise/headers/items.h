#ifndef ITEMS_H
#define ITEMS_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class item{

private:

	int trick;
	string itemID;
	vector<double> coordinates;

public:

	item(string,vector<double>);
	item(const item&);
	string getID();
	int32_t getTrick();
	void setTrick(int32_t);
	vector<double> *getVector();
	int getDimension();
	double getCoordinatein(int);
	void print();
};

#endif