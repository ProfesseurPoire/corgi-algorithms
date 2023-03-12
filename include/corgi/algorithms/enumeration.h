#pragma once

#include <vector>

namespace corgi::algorithms
{

/**
 * @brief   This namespace wil contains functions related to enumerations
 *          Meaning it deals with arrangements, combinations, permutations etc
 */
namespace enumeration
{
/**
 * @brief   Find arrangements for the given @p set for @p size elements.
 *          No repetition for this function. Arrangements are different from
 *          combinations, as they include the order
 *
 *          Warning : this version is very BADLY optimized (not at all actually)
 */
std::vector<std::vector<int>> find_arrangements(std::vector<int> set, int size);

std::vector<std::vector<int>> find_arrangements_iterative(std::vector<int> set,
                                                          int size);

std::vector<int> find_arrangements_opt(std::vector<int> set, int size);

int arrangements_size(int set_item, int size);

}    // namespace enumeration
}    // namespace corgi::algorithms