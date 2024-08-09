#include"TestCases.h"
#include"algo_goldschmidt.h"

int main()
{

	Booth_TestCase b_tc;
	b_tc.runMultiplicationTest();

	goldschmidt gold;
	gold.setup(86,7);

	std::cin.get();

	return 0;
}