#ifndef PHARE_TEST_LINEAR_COMBINAISON_H
#define PHARE_TEST_LINEAR_COMBINAISON_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <fstream>
#include <vector>

#include "data/grid/gridlayout.h"
#include "data/grid/gridlayout_impl.h"

using namespace PHARE;


struct Combinaison
{
    int dimension;
    int interpOrder;
    std::vector<int> ix, iy, iz;
    double coef;
};




std::array<Combinaison, 9> readFile(std::string filename)
{
    std::ifstream file{filename};
    std::array<Combinaison, 9> combinaisons;
    int nbrPts;

    for (std::size_t c = 0; c < 9; ++c)
    {
        file >> combinaisons[c].dimension >> combinaisons[c].interpOrder >> nbrPts;

        for (int ip = 0; ip < nbrPts; ++ip)
        {
            int i, j, k;
            if (combinaisons[c].dimension == 1)
            {
                file >> i;
                combinaisons[c].ix.push_back(i);
            }
            else if (combinaisons[c].dimension == 2)
            {
                file >> i >> j;
                combinaisons[c].ix.push_back(i);
                combinaisons[c].iy.push_back(j);
            }
            else
            {
                file >> i >> j >> k;
                combinaisons[c].ix.push_back(i);
                combinaisons[c].iy.push_back(j);
                combinaisons[c].iz.push_back(k);
            }
        }
        file >> combinaisons[c].coef;
    }


    return combinaisons;
}




#endif
