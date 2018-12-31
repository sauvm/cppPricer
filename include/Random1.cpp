#include "Random1.h"
#include <cstdlib>
#include <cmath>
#include <random>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

double GetOneGaussianBySummation()
{
	double result=0;

	for (unsigned long j=0; j < 12; j++)
		result += rand()/static_cast<double>(RAND_MAX);

	result -= 6.0;

	return result;

}

double GetGaussianByStdLib()
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    
    double number = distribution(generator);
    return number;
}


double GetOneGaussianByBoxMuller()
{
	double result;

	double x;
	double y;

	double sizeSquared;
	do
	{
		x = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
		y = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
		sizeSquared = x*x + y*y;
	}
	while
		( sizeSquared >= 1.0);

	result = x*sqrt(-2*log(sizeSquared)/sizeSquared);

	return result;

}