#pragma once

#include <span>
#include <vector>
/**
 * @brief The goal of this namespace is to gather algorithms/features
 * related to arrays, ector etc
 */
namespace corgi::algorithms::array
{

/**
 * @brief   Checks if first and second containers are distinct
 */
bool distincts(const std::vector<int>& first, const std::vector<int>& second)
{
    return first != second;
}

/**
 * @bief    Checks if @p containers are distinct by comparing them two by two
 */
bool distincts(const std::vector<std::vector<int>>& containers)
{
    for(auto i = 0; i < containers.size(); i++)
    {
        for(auto j = i + 1; j < containers.size(); j++)
        {
            if(containers[i] == containers[j])
                return false;
        }
    }
    return true;
}

}    // namespace corgi::algorithms::array