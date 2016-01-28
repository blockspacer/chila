/* Copyright 2011-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

#include "util.hpp"
#include "OperationProviderMap.hpp"
#include "VariableProviderMap.hpp"

#include "nspDef.hpp"

MY_NSP_START
{
    void printPrefix(std::vector<bool> &prefixList)
    {
        int lastPosition = prefixList.size() - 1, i;
        for (i = 0; i < lastPosition; ++i)
        {
            std::cout << (prefixList[i] ? " |  ":"    ");
        }
        if (i < prefixList.size()) {
            std::cout << " |--";
        }
    }

}
MY_NSP_END
