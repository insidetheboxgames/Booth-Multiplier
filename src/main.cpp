#include"algo_booth.h"


int main()
{
	Booths b;

	//M
	b.setmultiplicand(7);
	//Q
	b.setmultiplier(7);


	b.runAlgo();
	
	b.outputResult();

	std::cin.get();

	return 0;
}