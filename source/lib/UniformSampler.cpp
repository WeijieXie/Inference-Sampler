#include "UniformSampler.hpp"

template <typename REAL>
void UniformSampler<REAL>::sample()
{
    int numParas = this->paraInfo.size();
    int numSample = pow(this->numBins,numParas);
    int index;
    REAL para;

    std::vector<REAL> mins;
    std::vector<REAL> width;
    std::vector<REAL> Sample;

    for(auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        mins.push_back(*iter->min);
        width.push_back((*iter->max-*iter->max)/this->numBins);
    }

    for(uint i = 0; i < numSample; i++)
    {
        for(uint j = 0; j < numSample; j++) 
        {
            index = i/pow(this->numBins,j);
            para = mins.at(j) + (index+0.5)*width.at(j);
            Sample.push_back(index+0.5);
        }
        Sample.push_back(this->likelihood(Sample));
        this->sampledChain.push_back(Sample);
    }
}