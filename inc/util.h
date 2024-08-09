#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<vector>

//Rewrite this
 static std::vector<bool> convertToBin(int64_t convertVal, int maxSize)
{
	std::vector<bool> bin_result;
	uint64_t powerHolder = pow(2,maxSize-1);
	int i = 2;

	if (convertVal == 0)
	{
		for (int j = maxSize; j > 0; j--)
			bin_result.push_back(0);

		return bin_result;
	}

	if (convertVal > 0)
		bin_result.push_back(0);
	else
	{
		bin_result.push_back(1);
		convertVal += powerHolder; 
	}

	powerHolder = pow(2, maxSize - 2);
	while (maxSize-i >= 0)
	{
		if (convertVal == powerHolder)
		{
			bin_result.push_back(1);
			convertVal -= powerHolder;
		}
		else if (convertVal % powerHolder >= 1 && convertVal >= powerHolder)
		{
			bin_result.push_back(1);
			convertVal -= powerHolder;
		}
		else
		{
			bin_result.push_back(0);
		}
		i++;
		powerHolder = (pow(2, maxSize - i));
	}
	
	return bin_result;
};

static int convertToDec(std::vector<bool>& inConvert, int bitsToConvert)
{
	int calc_res = 0;
	//Checks if the number is negative or not because that changes how I will calculate the decimal value
	if (inConvert[0] == 0)
	{
		for (int i = bitsToConvert; i > 1; i--)
		{
			if (inConvert[bitsToConvert - i + 1] == 1)
			{
				calc_res += pow(2, i - 2);
			}
		}
	}
	if (inConvert[0] == 1)
	{
		for (int i = bitsToConvert; i > 1; i--)
		{
			if (inConvert[bitsToConvert - i + 1] == 0)
			{
				calc_res += pow(2, i - 2);
			}
		}

		calc_res += 1;
		calc_res *= -1;
	}

	return calc_res;
};

#endif UTIL_H