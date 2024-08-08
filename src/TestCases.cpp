#include "TestCases.h"

bool Booth_TestCase::runMultiplicationTest()
{
    bool correctResults = true;
    Booths b;

    for (int i = -8; i < 8; i++)
    {
        for (int j = -8; j < 8; j++)
        {
            b.setMultiplicand(i);
            b.setMultiplier(j);
            b.runAlgo();
            int res = b.getReadableResult();

            if (i * j != res)
            {
                correctResults = false;
                std::cout << "ERROR: " << i << " * " << j << " =" << i * j << " the algorithm calcualted " << res << std::endl;
            }
            b.reset();
        }
    }
    
    if (correctResults)
        std::cout << "Passed Test Cases from -8*-8 to 7*7" << std::endl;

    return correctResults;
}
