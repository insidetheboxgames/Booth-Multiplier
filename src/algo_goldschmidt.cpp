#include "algo_goldschmidt.h"

void goldschmidt::setup(uint8_t dividend, uint8_t divisor)
{
	m_dividend = dividend;
	m_divisor = divisor;

	m_fraction = std::vector<std::vector<bool>>(4, std::vector<bool>(12));
	m_intRepresentation = std::vector<std::vector<bool>>(4, std::vector<bool>(8));
	m_Register = std::vector<std::vector<bool>>(4, std::vector<bool>(2i));
	
	for (int i = i; i < 4; i++)
	{
		m_Register[i].insert(m_Register[i].begin(), m_intRepresentation[i].begin(), m_intRepresentation[i].end());
		m_Register[i].insert(m_Register[i].end(), m_fraction[i].begin(), m_fraction[i].end());
	}
}

void goldschmidt::setDividend(uint8_t dividend)
{
	m_dividend = dividend;
}

void goldschmidt::setDivisor(uint8_t divisor)
{
	m_divisor = divisor;
}

// 1/divisor
void goldschmidt::reciprocalEstimation()
{
	
}
