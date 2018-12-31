#include "PayOff1.h"
#include "MinMax.h"

PayOff::PayOff(double Strike_, OptionType TheOptionsType_)
:
  Strike(Strike_), TheOptionsType(TheOptionsType_)
  {
  }
double PayOff::operator()(double spot) const
{
    switch (TheOptionsType)
    {
    case call:
        return max(spot - Strike, 0.0);

    case put:
        return max(Strike - spot, 0.0);

    case digitalcall:
        if ((Strike - spot) > 0) {
            return 1;
        }
        else {
            return 0;
        }


    default:
        throw("Unknown options type found");
    }
}