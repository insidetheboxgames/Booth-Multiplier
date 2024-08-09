#ifndef ALGO_BOOTHS_H
#define ALGO_BOOTHS_H
#include<iostream>
#include<vector>
#include"util.h"

class Booths
{
public:
	void setup();

	void runAlgo();

	int getReadableResult();


	void setMultiplicand(int in_Multiplicand);
	void setMultiplier(int in_Multiplier);

	void reset();

private:

	void additionOperation();
	void subtractionOperation();

	void shiftResultRight();

	uint8_t getCode();

	//Using int because bool for a better visual debugging experience

	//Commonly shown as M
	std::vector<bool> multiplicand;
	//Commonly shown as Q
	std::vector<bool> multiplier;
	//Special Q-1 Register
	bool q_1;

	std::vector<bool> result;
	int result_size;

	int count;
	int multiplicandSize;

	int viewableRes;
};

#endif ALGO_BOOTHS_H