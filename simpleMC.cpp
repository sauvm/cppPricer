#include <iostream>
#include <cmath>
#include "lib/Random1.h"
using namespace std;

double SimpleMonteCarlo(double Expiry,
                        double Strike,
                        double Spot,
                        double Vol,
                        double r,
                        unsigned long NumberOfPaths)
{
    double variance = Vol * Vol;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;

    double movedSpot = Spot*exp(r*Expiry + itoCorrection);
    double thisSpot;
    double runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPaths; i++)
    {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot * exp(rootVariance*thisGaussian);
        double thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(r*Expiry);
    return mean;

}


int main() {

    double toto = GetOneGaussianByBoxMuller();
    cout<<toto;

    double result = SimpleMonteCarlo(1,
                                     120,
                                     100,
                                     0.4,
                                     0.03,
                                     10000000);
    cout << "The price is " << result;
};