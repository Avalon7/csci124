/*
student name: Weicheng Yin
student id: 5009819
this is the .h file for CSCI204 ass1
*/


#ifndef _ATM_
#define _ATM_

class ATM{
private:
	int atmId;
	int twentyNum;
	int fiftyNum;

public:
	ATM();
	ATM(int , int, int);
	
	int getId();
	void addFifty(int);
	void addTwenty(int);
	void loadAtm(char *, ATM *);
	int getTwenty();
	int getFifty();
	void modifyCash(int, int);		//modify the cash box after withdraw
};

#endif
