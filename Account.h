/*
student name: Weicheng Yin
student id: 5009819
this is the .h file for CSCI204 ass1
*/


#ifndef _ACCOUNT_
#define _ACCOUNT_

class Account{
private:
	int idNum;
	int bsbNum;
	int accNum;
	std::string firstName;
	std::string lastName;
	double balance;
	double tWithdraw;


public:
	Account();
	Account(int, int, int, std::string, std::string, double);

	int getId();
	int getBsb();
	int getAccount();
	std::string getFirst();
	std::string getLast();
	double getBal();

	void modifyBal(int);		//modify the account balance 

};	

#endif
