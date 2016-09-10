/*
student name: Weicheng Yin
student id: 5009819
this is the main file for CSCI204 ass1
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "ATM.h"
#include "Account.h"

using namespace std;

void showMenu()
{
	cout << "1. Withdraw" << endl;
	cout << "2. Find balance" << endl;
	cout << "3. Add notes" << endl;
	cout << "4. Quit" << endl;
	cout << "Please choose: ";
}

void loadAmount(ifstream& fin, Account *accPtr, int accAmount)
{

	fin.ignore();
	char temp[32];
	int id, bsb, acc;
	string firstN, secondN;
	double bal;
	for(int i = 0; i < accAmount; i++)
	{
		fin.getline(temp, 32, ',');
		id = atoi(temp);
		fin.getline(temp, 32, ',');
		bsb = atoi(temp);
		fin.getline(temp, 32, ',');
		acc = atoi(temp);
		getline(fin, firstN, ',');
		getline(fin, secondN, ',');
		fin >> bal;
		fin.ignore();
		accPtr[i] = Account(id, bsb, acc, firstN, secondN, bal);
	}
	
}

void loadAtm(ifstream& fin, ATM *aPtr, int atmNum)
{
	fin.ignore();
	char temp[32];
	int id, twenty, fifty;
	for(int i = 0; i < atmNum; i++)
	{
		fin.getline(temp, 32, ',');
		id = atoi(temp);
		fin.getline(temp, 32, ',');
		twenty = atoi(temp);
		fin.getline(temp, 32);
		fifty = atoi(temp);
		aPtr[i] = ATM(id, twenty, fifty);
	}
}

void withdraw(Account *accPtr, ATM *aPtr, int accAmount, int atmNum, ofstream &fout)
{
	int bsb, account, amount;
	int fNotes = 0;
	int tNotes = 0;
	cout << "BSB: ";
	cin >> bsb;
	cout << "Account: ";
	cin >> account;
	cout << "Amount: ";
	cin >>amount;
	bool found = false;
	for(int i = 0; i < accAmount; i++)
	{
		if(accPtr[i].getBsb() == bsb)
		{
			if(accPtr[i].getAccount() == account)
			{
				found = true;
				if(amount > accPtr[i].getBal())
				{
					cout << "the amount cash is bigger than the account balance. Return to main menu." << endl;
					return;
				}
				else if(amount < 20)
				{
					cout << "the amount is invalid. " << endl;
				}
				else
				{//compute how many 50 and 20 notes should be given
					int atm = rand() % 5 + 800001;		//generate the random ATM machine
					//calculate the cash use the greedy algorithm
					int cash = amount;
					int fNum = amount / 50;
					fNotes = fNum;
					cash %= 50;
					bool flag = false;
					for(int j = 0; j <= fNum && !flag; j++)
					{						
						if((cash % 20) != 0)
						{
							cash += 50;
							tNotes = cash / 20;
							fNotes--;
						}
						else
						{
							tNotes = cash / 20;
							flag = true;
						}
						
					}
					if((tNotes == 0) && (fNotes == 0))
					{
						//cant find the proper solution to withdraw the cash
						cout << "the amount you want to withdraw is invalid." << endl;
						return;
					}
					else{
						//the cash is valid
						cout << "You have " << fNotes << "x$50 notes, " << tNotes << "x$20 notes.";
						//modify the balance of the account
						accPtr[i].modifyBal(amount);
						cout << "Your balance is " << accPtr[i].getBal() << endl;
						//update the ATM cash boxes;
						for(int j = 0; j < atmNum; j++)
						{
							if(atm == aPtr[j].getId())
							{
								aPtr[j].modifyCash(tNotes, fNotes);
							}
						}
						//write the log to the ATM.log file
						//ofstream fout;
						//fout.open("ATM.log");
						time_t t = time(0);   // get time now
		    			struct tm * now = localtime( & t );
						fout << atm << ", " << now->tm_mday << "/" << (now->tm_mon + 1) << "/";
						fout << (now->tm_year + 1900) << " " << now->tm_hour << ":";
						fout << now->tm_min << ":" << now->tm_sec << ", " << "withdraw" << ", ";
						fout << bsb << ", " << account << ", " << amount << "." << endl;
					}

				}
			}
		}
	}
	if(!found)
	{
		cout << "incorrect bank account, return to main manu." << endl;
		return;
	}
}


void findBal(Account *accPtr, int accAmount)
{
	int bsb, account;
	cout << "BSB: ";
	cin >> bsb;
	cout << "Account: ";
	cin >> account;
	bool found = false;
	for(int i = 0; i < accAmount && !found; i++)
	{	
		
		if(accPtr[i].getBsb() == bsb)
		{
			if(accPtr[i].getAccount() == account)
			{
				cout << "Your balance is $" << accPtr[i].getBal() << endl;
				found = true;
			}
			
		}
	}
	if(!found)
	{
		cout << "cant find the account details. Return to main menu" << endl;
		return;
	}
}

void addNotes(ATM *aPtr, int atmNum, ofstream& fout)
{
	int id, choice, amount, balance ;
	cout << "ATM ID: ";
	cin >> id;
	cout << "Note type(1-$50, 2-$20): ";
	cin >> choice;
	cout << "Amount: ";
	cin >> amount;
	bool found = false;

	for(int i = 0; i < atmNum && !found; i++)
	{
		if(aPtr[i].getId() == id)
		{
			found = true;
			if(choice != 1 && choice != 2)
			{
				cout << "invalid type choice, back to main menu" << endl;
				return;
			}
			else
			{				
				if(choice == 1)
				{
					if(amount % 50 != 0)
					{
						cout << "the input amount is invalid, back to main menu" << endl;
						return;
					}
					else
					{
						aPtr[i].addFifty(amount);		//add total cash for $50 notes
					}
				}
				else if(amount == 2)
				{
					if(choice % 20 != 0)
					{
						cout << "the input amount is invalid, back to main menu" << endl;
						return;
					}
					else
						aPtr[i].addTwenty(amount);
				}	
			
			}
			time_t t = time(0);   // get time now
		    struct tm * now = localtime( & t );
		    //open the log file and record the log
			//ofstream fout;
			//fout.open("ATM.log");
			fout << id << ", " << now->tm_mday << "/" << (now->tm_mon + 1) << "/";
			fout << (now->tm_year + 1900) << " " << now->tm_hour << ":";
			fout << now->tm_min << ":" << now->tm_sec << ", ";
			if(choice == 1)
				fout << "Add $50 notes, ";
			else
				fout << "Add $20 notes, ";
			fout << amount << ", " << balance << "." << endl;
			//fout.close();
		}
		if(!found)
		{
			cout << "can't find the account numbet, back to main menu." << endl;
			return;
		}
	}
	
}
//save the record to the "ATM.txt" and "Accounts.txt" file
void saveRecord(Account *accPtr, ATM *aPtr, int accAmount, int atmNum)
{
	ofstream fout;
	fout.open("accounts.txt");
	fout << accAmount << endl;
	cout << "account.txt" << endl;
	for(int i = 0; i < accAmount; i++)
	{
		fout << accPtr[i].getId() << ", " << accPtr[i].getBsb() << ", " << accPtr[i].getAccount() << ", ";
		fout << accPtr[i].getFirst() << ", " << accPtr[i].getLast() << ", " << accPtr[i].getBal() << endl;
	}
	fout.close();
	fout.open("ATM.txt");
	cout << "ATM.txt" << endl;
	fout << atmNum << endl;
	for(int i = 0; i < atmNum; i++)
	{
		fout << aPtr[i].getId() << ", " << aPtr[i].getTwenty() << ", " << aPtr[i].getFifty() << endl;
	}
	fout.close();
}

int main(int argc, char** argv)
{
	char accFile[16];
	char atmFile[16];

	//get two file name from the command line
	strcpy(accFile, argv[1]);
	strcpy(atmFile, argv[2]);
	//open the log file to record the status
	ofstream fileWrite;
	fileWrite.open("ATM.log");
	//read the record in account.txt file
	int accNum, atmNum;
	ifstream finAcc, finAtm;	
	finAcc.open(accFile);
	finAcc >> accNum;
	
	Account *accountPtr;			//create dynamic array for account
	accountPtr = new Account[accNum];
	loadAmount(finAcc, accountPtr, accNum);
	finAcc.close();
	cout << "Accounts have been loaded" << endl;

	finAtm.open(atmFile);
	finAtm >> atmNum;				
	ATM *atmPtr;					//create dynamic array for atm
	atmPtr = new ATM[atmNum];
	loadAtm(finAtm, atmPtr, atmNum);
	finAtm.close();
	
	cout << "ATMs have been loaded" << endl;
	
	
	int choice;
	do
	{
		showMenu();
		cin >> choice;
		switch(choice){
			case 1: withdraw(accountPtr, atmPtr, accNum, atmNum, fileWrite);
			break;
			case 2: findBal(accountPtr, accNum);
			break;
			case 3: addNotes(atmPtr, atmNum, fileWrite);
			break;
			case 4: saveRecord(accountPtr, atmPtr, accNum, atmNum);
			break;
			default: cout << "invalid choice, Please input choice again." << endl;
						showMenu();			
		}


	}while(choice != 4);

	fileWrite.close();
	delete [] accountPtr;
	delete [] atmPtr;

	return 0;

}
