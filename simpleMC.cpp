#include <iostream>
#include <cmath>
#include <random>
#include "include/Random1.h"
#include "include/PayOff1.h"
#include "include/MinMax.h"
using namespace std;

double SimpleMonteCarlo(const PayOff& thePayOff,
                        double Expiry,
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
    
    //this is in the std library
    default_random_engine generator (123544);
    normal_distribution<double> distribution(0.0, 1.0);

    for (unsigned long i = 0; i < NumberOfPaths; i++)
    {
        double thisGaussian = distribution(generator);
        thisSpot = movedSpot * exp(rootVariance*thisGaussian);
        double thisPayOff = thePayOff(thisSpot);
        runningSum += thisPayOff;
    }

    double mean = runningSum / NumberOfPaths;
    mean *= exp(r*Expiry);
    return mean;

}


int main() {

    PayOffCall thiscallPayoff(120);
    PayOffPut  thisputPayoff(120);
    PayOffDigCall thisDigCallPayoff(120);

    double Cresult = SimpleMonteCarlo(thiscallPayoff,
                                     1,
                                     100,
                                     0.4,
                                     0.03,
                                     5000000);
    cout << "The price of a call is " << Cresult << "\n";

    double Presult = SimpleMonteCarlo(thisputPayoff,
                                     1,
                                     100,
                                     0.4,
                                     0.03,
                                     5000000);
    cout << "The price of a put is " << Presult << "\n";

    double DCresult = SimpleMonteCarlo(thisDigCallPayoff,
                                     1,
                                     100,
                                     0.4,
                                     0.03,
                                     5000000);
    cout << "The price of a digital call is " << DCresult;
};