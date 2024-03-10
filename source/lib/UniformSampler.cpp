#include "UniformSampler.hpp"

#include <iostream>
#include <string>

template <typename REAL>
void UniformSampler<REAL>::sample()
{
    int numParas = this->paraInfo.size();
    int numSample = pow(this->numBins, numParas);
    int index;
    REAL width;
    REAL paraValue;
    REAL likeliHood;

    std::vector<REAL> sample;
    std::vector<int> indexes;

    std::vector<REAL> mins;
    std::vector<REAL> widths;
    // std::vector<REAL> sample;

    this->sampledChain.clear();

    for (auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        mins.push_back(iter->min);
        // std::cout<<"min: "<<iter->min<<std::endl;
        width = (iter->max - iter->min) / this->numBins;
        widths.push_back(width);
        // std::cout<<"width: "<<width<<std::endl;
    }

    for (int i = 0; i < numSample; i++)
    {
        sample.clear();
        indexes.clear();
        for (int j = 0; j < numParas; j++)
        {
            // std::cout<<"size1: "<<sample.size()<<std::endl;
            index = (i % int(pow(this->numBins, j + 1))) / (int(pow(this->numBins, j)));
            // std::cout<<"index"<<j<<": "<<index<<std::endl;
            paraValue = mins.at(j) + (index + 0.5) * widths.at(j);
            // std::cout<<"paraValue"<<j<<","<<index<<": "<<paraValue<<std::endl;
            sample.push_back(paraValue);
            indexes.push_back(index);

        }
        // std::cout<<"size2: "<<sample.size()<<std::endl;
        // std::cout<<"this->likelihood(sample): "<<this->likelihood(sample)<<std::endl;
        likeliHood = this->likelihood(sample);
        sample.push_back(likeliHood);

        for (int k = 0; k < numParas; k++)
        {

            this->marDis.at(k).at(indexes.at(k))+=std::exp(likeliHood);
            // this->marDis[k][indexes[k]]+=likeliHood;
        }

        // std::cout<<"size3: "<<sample.size()<<std::endl;
        // for (REAL val : sample) {
        //     std::cout << val << std::endl;
        // }
        this->sampledChain.push_back(sample);
    }

    // for (int i = 0; i < numSample; i++)
    // {
        
    //     for (auto iter=this->sampledChain.begin();iter<this->sampledChain.end()-1;iter++)
    //     {

    //     }
    // }
}

template void UniformSampler<float>::sample();
template void UniformSampler<double>::sample();