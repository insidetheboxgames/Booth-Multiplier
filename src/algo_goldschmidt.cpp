#include "algo_goldschmidt.h"

void goldschmidt::setup(uint8_t dividend, uint8_t divisor)
{
	m_Fraction = std::vector<std::vector<bool>>(4, std::vector<bool>(23));
	m_intRepresentation = std::vector<std::vector<bool>>(4, std::vector<bool>(9));
	m_Register = std::vector<std::vector<bool>>(4, std::vector<bool>(32));
	
	setDividend(dividend);
	setDivisor(divisor);

	for (int i = 0; i < 4; i++)
	{
		m_Register[i].insert(m_Register[i].begin(), m_intRepresentation[i].begin(), m_intRepresentation[i].end());
		m_Register[i].insert(m_Register[i].end(), m_Fraction[i].begin(), m_Fraction[i].end());
		m_Register[i].resize(32);
	}
	reciprocalEstimation();

	
	updateRegisters();
	runAlgo();
}

void goldschmidt::runAlgo()
{
	for (int i = 0; i < 5; i++)
	{
		altMultiplier();
		subtractFromTwo();
		updateRegisters();
	}
	std::cout << convertToDec(m_intRepresentation[2], 9) << std::endl;
	std::cout << (float)((float)convertToDec(m_Fraction[2], 23) / pow(2, 24)) << std::endl;
}

//[0] index 0
void goldschmidt::setDividend(uint8_t dividend)
{
	m_dividend = dividend;
	m_intRepresentation[0] = convertToBin(m_dividend, m_intRepresentation[0].size());
}

//[1] index 1
void goldschmidt::setDivisor(uint8_t divisor)
{
	m_divisor = divisor;
	//Using a variable size allows for easy future modification
	m_intRepresentation[1] = convertToBin(m_divisor, m_intRepresentation[1].size());
}

void goldschmidt::altMultiplier()
{
	int64_t t_largeDividend= convertToDec(m_Register[0], m_Register[0].size());
	int64_t t_largeDivisor = convertToDec(m_Register[1], m_Register[1].size());
	int64_t t_largeFinal = convertToDec(m_Register[2], m_Register[2].size());

	int64_t t_Mult = t_largeDividend * t_largeFinal;
	std::vector<bool> t_MultBinHold = convertToBin(t_Mult, 64);
	std::copy(t_MultBinHold.begin() + 10, t_MultBinHold.begin() + 42, m_Register[0].begin());
	t_Mult = t_largeDivisor * t_largeFinal;
	t_MultBinHold = convertToBin(t_Mult, 64);
	std::copy(t_MultBinHold.begin() + 10, t_MultBinHold.begin() + 42, m_Register[1].begin());
}

// 1/divisor
void goldschmidt::reciprocalEstimation()
{
	bool shifted = false;
	for (int i = 0; i < 9; i++)
	{
		//I don't like
		if (m_intRepresentation[1][i] == 1)
		{
			int shiftAmount = (2 * (8 - i)) + 1;
			std::copy(m_intRepresentation[1].begin(), m_intRepresentation[1].end(), m_Register[2].begin());
			std::rotate(m_Register[2].begin(), std::prev(m_Register[2].end(), shiftAmount), m_Register[2].end());
			shifted = true;
			break;
		}
	}
	//Default Case
	if(!shifted)
		m_Register[2] = m_Register[1];
}

void goldschmidt::subtractFromTwo()
{
	int divisorVal = convertToDec(m_intRepresentation[1], m_intRepresentation[1].size());
	int newFinteger = 2 - divisorVal;
	m_intRepresentation[2] = convertToBin(newFinteger, 9);
	std::copy(m_intRepresentation[2].begin(), m_intRepresentation[2].end(), m_Register[2].begin());

}

void goldschmidt::updateRegisters()
{
	for (int i = 0; i < 4; i++)
	{
		m_intRepresentation[i].assign(m_Register[i].begin(), m_Register[i].begin() + 9);
		m_Fraction[i].assign(m_Register[i].begin() + 9, m_Register[i].end());
	}

}
