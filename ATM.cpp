/*
student name: Weicheng Yin
student id: 5009819
this is the .cpp file for CSCI204 ass1
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ATM.h"

using namespace std;

ATM::ATM()
{
	atmId = 0;
	twentyNum = 0;
	fiftyNum = 0;
}

ATM::ATM(int aId, int aTwenty, int aFifty)
{
	atmId = aId;
	twentyNum = aTwenty;
	fiftyNum = aFifty;
}

int ATM::getId()
{
	return atmId;
}

int ATM::getTwenty()
{
	return twentyNum;
}

int ATM::getFifty()
{
	return fiftyNum;
}

void ATM::addTwenty(int amou)
{
	twentyNum += amou;
}

void ATM::addFifty(int amou)
{
	fiftyNum += amou;
}


void ATM::modifyCash(int twenty, int fifty)
{
	fiftyNum -= 50 * fifty;
	twentyNum -= 20 * twenty;
}
