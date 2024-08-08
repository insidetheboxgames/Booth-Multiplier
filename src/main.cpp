#include"TestCases.h"
#include"algo_goldschmidt.h"

int main()
{

	convertToBin(-5,4);

	Booth_TestCase b_tc;
	b_tc.runMultiplicationTest();

	goldschmidt gold;
	gold.setup(8,8);

	std::cin.get();

	return 0;
}