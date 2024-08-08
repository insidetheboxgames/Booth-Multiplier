#include"algo_booth.h"

//Sets the entry values of the result along with estabilishing the count.
void Booths::setup()
{
	multiplicandSize = multiplicand.size();
	count = multiplicandSize;
	
	for (int i = 0; i < 4; i++)
		result.push_back(0);

	result.insert(result.end(), multiplier.begin(),multiplier.end());
}

void Booths::runAlgo()
{
	setup();

	while (count > 0)
	{
		switch (getCode())
		{
			//NOP
			case 0:
				shiftResultRight();
				break;
			//A+M
			case 1:
				additionOperation();
				shiftResultRight();
				break;
			//A-M
			case 2:
				subtractionOperation();
				shiftResultRight();
				break;
			case 255:
				break;
		}
		count--;
	}

	viewableRes = getReadableResult();
}

//Output is 8 bits which allows for results from -128 to 127
//However in this 4 bit signed multiplication the max value is 64 (-8*-8) 
int Booths::getReadableResult()
{
	int calc_res = 0;
	
	//First Three are special cases that seem to cause issues. I've seen it on other calculators.
	//Need to further look at why this is failing and is requiring these if statements
	if (multiplicand[0] == 1 && multiplier[0] == 1 && result[0] == 1)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 0)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res += 1;
	}
	else if (multiplicand[0] == 1 && multiplier[0] == 0 && result[0] == 0)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res *= -1;
	}
	else if (multiplicand[0] == 0 && multiplier[0] == 1 && result[0] == 0)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res *= -1;
	}
	else if (result[0] == 0)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}
	}
	else if (result[0] == 1)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 0)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res += 1;
		calc_res *= -1;
	}

	return calc_res;
}

void Booths::additionOperation()
{
	int result_Dec_TMP = convertToDec(result,4);
	int multiplicand_Dec_TMP = convertToDec(multiplicand,4);

	result_Dec_TMP += multiplicand_Dec_TMP;

	//If there is an overflow.
	if (result_Dec_TMP > 7)
	{
		result_Dec_TMP -= 8;
	}
	else if (result_Dec_TMP < -8)
	{
		result_Dec_TMP += 16;
	}

	std::vector<int> tmp_result = convertToBin(result_Dec_TMP,4);

	for (int i = 0; i < 4; i++)
		result[i] = tmp_result[i];
}

void Booths::subtractionOperation()
{
	int result_Dec_TMP = convertToDec(result,4);
	int multiplicand_Dec_TMP = convertToDec(multiplicand,4);

	result_Dec_TMP -= multiplicand_Dec_TMP;

	//If there is an overflow.
	if (result_Dec_TMP < -9)
	{
		result_Dec_TMP += 8;
	}
	else if (result_Dec_TMP >= 8)
	{
		result_Dec_TMP -= 16;
	}

	std::vector<int> tmp_result = convertToBin(result_Dec_TMP,4);

	for (int i = 0; i < 4; i++)
		result[i] = tmp_result[i];

}

void Booths::shiftResultRight()
{
	bool tmp = result[0];
	
	std::rotate(result.begin(), std::prev(result.end(), 1), result.end());
	result[0] = tmp;
}

uint8_t Booths::getCode()
{
	switch (result[7])
	{
		case 0:
			switch (q_1) 
			{	
				//NOP
				case 0:
					return 0;
				//A+M
				case 1:
					q_1 = 0;
					return 1;
			}
		case 1:
			switch (q_1)
			{
				//A-M
				case 0:
					q_1 = 1;
					return 2;
				//NOP
				case 1:
					return 0;
			}
		default:
			return 255;
	}
}


void Booths::setMultiplicand(int in_Multiplicand)
{ 
	multiplicand = convertToBin(in_Multiplicand,4);
};

void Booths::setMultiplier(int in_Multiplier)
{ 
	multiplier = convertToBin(in_Multiplier,4);
}
void Booths::reset()
{
	result.clear();
	multiplicand.clear();
	multiplier.clear();
	q_1 = 0;
	result_size = 0;
	count = 0;
	multiplicandSize = 0;
	viewableRes = 0;
}