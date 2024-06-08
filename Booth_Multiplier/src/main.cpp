#include"algo_booth.h"


int main()
{
	std::vector<int> result = {0,0,1,1 };
	//std::cout << "Testing" << std::endl;
	Booths b;

	b.setmultiplicand(7);
	b.setmultiplier(7);
	b.runAlgo();
	
	b.outputResult();

	std::cin.get();

	return 0;
}