#ifndef ALGO_GOLDSCHMIDT_H
#define ALGO_GOLDSCHMIDT_H
#include<iostream>
#include<vector>

#include "util.h"

class goldschmidt
{
public: 
	void setup(uint8_t dividend, uint8_t divisor);
	
	void runAlgo();

	void setDividend(uint8_t dividend);
	void setDivisor(uint8_t divisor);

private:
	void altMultiplier();
	void reciprocalEstimation();

	uint8_t m_dividend;
	uint8_t m_divisor;

	//[0] = N, [1]=D, [2]= F, [3]= intermediate
	std::vector<std::vector<bool>> m_fraction;
	std::vector<std::vector<bool>> m_intRepresentation;
	//Gives the example of the register
	std::vector<std::vector<bool>> m_Register;

};

#endif