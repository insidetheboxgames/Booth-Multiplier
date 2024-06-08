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

}

//Output is 8 bits which allows for results from -128 to 127
//However in this 4 bit signed multiplication the max value is 64 (-8*-8) 
void Booths::outputResult()
{
	int calc_res = 0;

	if (result[0] == 0)
	{
		for (int i = 8; i > 1; i--)
		{
			if (result[8 - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}
	}
	if (result[0] == 1)
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

	std::cout << calc_res << std::endl;
}

void Booths::additionOperation()
{
	int result_Dec_TMP = convertToDec(result);
	int multiplicand_Dec_TMP = convertToDec(multiplicand);

	result_Dec_TMP += multiplicand_Dec_TMP;

	//If there is an overflow.
	if (result_Dec_TMP > 7)
	{
		result_Dec_TMP -= 8;
	}

	std::vector<int> tmp_result = convertToBin(result_Dec_TMP);

	for (int i = 0; i < 4; i++)
		result[i] = tmp_result[i];
}

void Booths::subtractionOperation()
{
	int result_Dec_TMP = convertToDec(result);
	int multiplicand_Dec_TMP = convertToDec(multiplicand);

	result_Dec_TMP -= multiplicand_Dec_TMP;

	//If there is an overflow.
	if (result_Dec_TMP < -8)
	{
		result_Dec_TMP += 8;
	}

	std::vector<int> tmp_result = convertToBin(result_Dec_TMP);

	for (int i = 0; i < 4; i++)
		result[i] = tmp_result[i];

}

std::vector<int> Booths::convertToBin(int convertVal)
{
	std::vector<int> bin_result;
	int powerHolder = 0;

	if (convertVal > 0)
	{
		bin_result.push_back(0);
		for (int i = 1; i < 4; i++)
		{
			powerHolder = pow(2, 3 - i);
			if (convertVal % powerHolder >= 1 && convertVal >= powerHolder)
			{
				bin_result.push_back(1);
				convertVal -= powerHolder;
			}
			else if (convertVal == powerHolder)
			{
				bin_result.push_back(1);
				convertVal -= powerHolder;
			}
			else
			{
				bin_result.push_back(0);
			}
		}
	}
	else if (convertVal < 0)
	{
		//-8 is the max negative value allowed by signed 4 bit numbers. Thus its result would be 1000 
		//so by adding the negative value by 8 it allows me to compute the positive version.
		convertVal += 8;
		bin_result.push_back(1);

		for (int i = 1; i < 4; i++)
		{
			powerHolder = pow(2, 3 - i);
			if (convertVal % powerHolder >= 1 && convertVal >= powerHolder)
			{
				bin_result.push_back(1);
				convertVal -= powerHolder;
			}
			else if (convertVal == powerHolder)
			{
				bin_result.push_back(1);
				convertVal -= powerHolder;
			}
			else
			{
				bin_result.push_back(0);
			}
		}
	}
	else
		bin_result.insert(bin_result.begin(), { 0,0,0,0 });
	
	return bin_result;
}

int Booths::convertToDec(std::vector<int>& inConvert)
{
	int calc_res = 0;
	
	//Checks if the number is negative or not because that changes how I will calculate the decimal value
	if (inConvert[0] == 0)
	{
		for (int i = 4; i > 1; i--)
		{
			if (inConvert[4 - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}
	}
	if (inConvert[0] == 1)
	{
		for (int i = 4; i > 1; i--)
		{
			if (inConvert[4 - i + 1] == 0)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res += 1;
		calc_res *= -1;
	}

	return calc_res;
}

void Booths::shiftResultRight()
{
	//Right Shift
	if (result[0] == 1)
	{
		std::rotate(result.begin(), std::prev(result.end(), 1), result.end());
		//Preserves the Twos Complement Sate
		result[0] = 1;
	}
	else
	{
		std::rotate(result.begin(), std::prev(result.end(), 1), result.end());
		//Preserves the Twos Complement Sate
		result[0] = 0;
	}
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


void Booths::setmultiplicand(int in_Multiplicand)
{ 
	multiplicand = convertToBin(in_Multiplicand);
};

void Booths::setmultiplier(int in_Multiplier)
{ 
	multiplier = convertToBin(in_Multiplier);
};