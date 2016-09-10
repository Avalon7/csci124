/*
student name: Weicheng Yin
student id: 5009819
this is the .cpp file for CSCI204 ass1
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "Account.h"


using namespace std;

//constructor 
Account::Account()
{
	idNum = 0;
	bsbNum = 0;
	accNum = 0;
	balance = 0;
	firstName  = "";
	lastName = "";
	tWithdraw = 0;
	
}

//this is the destructor


Account::Account(int id, int bsb, int acc, string fname, string lname, double bal)
{
	idNum = id;
	bsbNum = bsb;
	accNum = acc;
	firstName = fname;
	lastName = lname;
	balance = bal;

}


int Account::getBsb()
{
	return bsbNum;
}


int Account::getAccount()
{
	return accNum;
}

double Account::getBal()
{
	return balance;
}

void Account::modifyBal(int cash)
{
	balance -= cash;
}

string Account::getFirst()
{
	return firstName;
}


string Account::getLast()
{
	return lastName;
}

int Account::getId()
{
	return idNum;
}
