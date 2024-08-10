#include"TestCases.h"
#include"algo_goldschmidt.h"

int main()
{

	Booth_TestCase b_tc;
	b_tc.runMultiplicationTest();

	goldschmidt gold;
	gold.setup(12,6);

	std::cin.get();

	return 0;
}