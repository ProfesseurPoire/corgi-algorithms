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

std::vector<std::vector<int>>
combination_without_repetition(std::vector<int> set, int k);

/**
 * @brief   Returns every combination with repetition of @p set for subset of k
 *          @p cardinality
 */
std::vector<std::vector<int>> combination_with_repetition(std::vector<int> set,
                                                          int              k);

/**
 * @brief   Find arrangements for the given @p set for @p size elements.
 *          No repetition for this function. Arrangements are different from
 *          combinations, as they include the order
 *
 *          Warning : this version is very BADLY optimized (not at all actually)
 */
std::vector<std::vector<int>> arrangements(std::vector<int> set, int size);

/**
 * @brief   Find every arrangement of size @p n with repetition for the given @p
 *          set
 */
std::vector<std::vector<int>> arrangements_with_repetition(std::vector<int> set,
                                                           int              n);

std::vector<std::vector<int>> arrangements_iterative(std::vector<int> set,
                                                     int              size);

std::vector<int> arrangements_opt(std::vector<int> set, int size);

/**
 * @brief   Computes the arrangement count with repetition for a k-tuple of set
 *          E with |E| = n
 *
 *          The arrangement count for a k-tuple with repetition equals k^n
 *
 * @param k size of an arrangement (or k-tuple)
 * @param n Cardinality of the set E
 */
int arrangement_count_with_repetition(int k, int n);

/**
 * @brief   Computes the arrangement count without repetition for a k-tuple
 *          included in set E with |E|=n
 *
 *          The arrangement count for a k-tuple without repetition equals
 *          n! / (n-k)!
 *
 * @param k size of an arrangement (or k-tuple)
 * @param n Cardinality of the set E
 */
int arrangement_count_without_repetition(int k, int n);

/**
 * @brief   Computes the combination count without repetition for a subset K
 *          |K|=k of set E with |E| = n
 *
 *          The combination count is : n!/(k!)(n-k)!
 */
int combination_count_without_repetition(int k, int n);

/**
 * @brief   Computes the combination count with repetition for a subset K
 *          |K|=k of set E with |E| = n
 *
 *          The combination count is : n!/(k!)(n-k)!
 */
int combination_count_with_repetition(int k, int n);

int permutation_count_with_repetition(int k);
int permutation_count_without_repetition(int k);

std::vector<std::vector<int>>
permutations_without_repetition(std::vector<int> set);

std::vector<std::vector<int>>
permutations_with_repetition(std::vector<int> set);

}    // namespace enumeration
}    // namespace corgi::algorithms