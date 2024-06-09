#ifndef ALGO_BOOTHS_H
#define ALGO_BOOTHS_H
#include<iostream>
#include<vector>

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


	std::vector<int> convertToBin(int convertVal);
	int convertToDec(std::vector<int>& inConvert);
	void shiftResultRight();

	uint8_t getCode();

	//Using int because bool for a better visual debugging experience

	//Commonly shown as M
	std::vector<int> multiplicand;
	//Commonly shown as Q
	std::vector<int> multiplier;
	//Special Q-1 Register
	bool q_1;

	std::vector<int> result;
	int result_size;

	int count;
	int multiplicandSize;

	int viewableRes;
};

#endif ALGO_BOOTHS_H