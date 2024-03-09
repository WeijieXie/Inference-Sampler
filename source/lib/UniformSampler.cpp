#include "UniformSampler.hpp"

#include <iostream>
#include <string>

template <typename REAL>
void UniformSampler<REAL>::sample()
{
    int numParas = this->paraInfo.size();
    int numSample = pow(this->numBins,numParas);
    int index;
    REAL width;
    REAL paraValue;

    std::vector<REAL> mins;
    std::vector<REAL> widths;
    // std::vector<REAL> sample;

    this->sampledChain.clear();

    for(auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        mins.push_back(iter->min);
        // std::cout<<"min: "<<iter->min<<std::endl;
        width = (iter->max-iter->min)/this->numBins;
        widths.push_back(width);
        // std::cout<<"width: "<<width<<std::endl;
    }

    for(int i = 0; i < numSample; i++)
    {
        // sample.clear();
        std::vector<REAL> sample;
        for(int j = 0; j < numParas; j++) 
        {
            // std::cout<<"size1: "<<sample.size()<<std::endl;
            index = (i%int(pow(this->numBins,j+1)))/(int(pow(this->numBins,j)));
            // std::cout<<"index"<<j<<": "<<index<<std::endl;
            paraValue = mins.at(j) + (index+0.5)*widths.at(j);
            std::cout<<"paraValue"<<j<<","<<index<<": "<<paraValue<<std::endl;
            sample.push_back(paraValue);
        }
        // std::cout<<"size2: "<<sample.size()<<std::endl;
        // std::cout<<"this->likelihood(sample): "<<this->likelihood(sample)<<std::endl;
        sample.push_back(this->likelihood(sample));
        // std::cout<<"size3: "<<sample.size()<<std::endl;
        // for (REAL val : sample) {
        //     std::cout << val << std::endl;
        // }
        this->sampledChain.push_back(sample);
    }
}

template void UniformSampler<float>::sample();
template void UniformSampler<double>::sample();