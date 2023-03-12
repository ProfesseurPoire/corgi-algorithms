#include "corgi/algorithms/enumeration.h"

namespace corgi::algorithms::enumeration
{

static long factorial(long v)
{
    if(v <= 1)
        return 1;
    else
        return factorial(v - 1) * v;
}

void find_arrangements_rec(std::vector<std::vector<int>>& results,
                           std::vector<int>&              arrangement,
                           std::vector<int>&              set,
                           int                            size,
                           int                            position)
{
    if(position == size)
    {
        results.push_back(arrangement);
    }
    else
    {
        int              i = 0;
        std::vector<int> new_arrangement;
        new_arrangement.reserve(size);
        std::vector<int> new_set;
        new_set.reserve(size);

        for(auto item : set)
        {
            new_arrangement = arrangement;
            new_arrangement.push_back(item);
            new_set = set;
            new_set.erase(new_set.begin() + i);

            find_arrangements_rec(results, new_arrangement, new_set, size,
                                  position + 1);
            i++;
        }
    }
}

std::vector<std::vector<int>> find_arrangements(std::vector<int> set, int size)
{
    std::vector<std::vector<int>> results;
    results.reserve(arrangements_size(static_cast<int>(set.size()), size));

    std::vector<int> ar;
    find_arrangements_rec(results, ar, set, size, 0);

    return results;
}

std::vector<std::vector<int>> find_arrangements_iterative(std::vector<int> set,
                                                          int              size)
{
    std::vector<std::vector<int>> results;
    results.reserve(arrangements_size(static_cast<int>(set.size()), size));

    size_t sum     = 0;
    size_t setsize = set.size();
    for(int i = 0; i < size; i++)
    {
        sum += setsize;
        setsize--;
    }

    std::vector<std::vector<int>> arrangements;
    arrangements.resize(sum);

    for(auto& ar : arrangements)
        ar.reserve(size);

    int arrangement_pointer = 0;

    std::vector<std::vector<int>> subsets;
    subsets.resize(sum);
    subsets[0] = set;

    for(auto& s : subsets)
        s.reserve(size);

    std::vector<int> new_arrangement;
    new_arrangement.reserve(size);

    std::vector<int> arrangement;
    arrangement.reserve(size);

    std::vector<int> new_set;
    new_set.reserve(set.size());

    size_t i = 0;

    while(arrangement_pointer >= 0)
    {
        arrangement = arrangements[arrangement_pointer];
        new_set     = subsets[arrangement_pointer];

        arrangement_pointer--;

        if(arrangement.size() == static_cast<int>(size))
        {
            results.push_back(arrangement);
            continue;
        }

        i = new_set.size() - 1;

        for(auto it = new_set.rbegin(); it != new_set.rend(); it++)
        {
            arrangement_pointer++;
            arrangements[arrangement_pointer] = arrangement;
            arrangements[arrangement_pointer].push_back(*it);
            subsets[arrangement_pointer] = new_set;
            subsets[arrangement_pointer].erase(
                subsets[arrangement_pointer].begin() + i);
            i--;
        }
    }
    return results;
}

struct optimized_arrangement
{
    std::vector<int> arrangement;
    std::vector<int> subset;
    size_t           subset_size;
};

std::vector<int> find_arrangements_opt(std::vector<int> set, int size)
{
    // We start by computing how many combination there is. Might be nice
    // to
    auto count = arrangements_size(static_cast<int>(set.size()), size);
    std::vector<int> results;
    results.resize(count * size);

    size_t sum     = 0;
    size_t setsize = set.size();
    for(int i = 0; i < size; i++)
    {
        sum += setsize;
        setsize--;
    }

    int offset             = size + static_cast<int>(set.size()) + 1;
    int subset_offset      = size;
    int subset_size_offset = size + static_cast<int>(set.size());

    std::vector<int> rdatas;
    std::vector<int> rdata;
    rdata.resize(offset);
    rdatas.resize(sum * offset);

    memcpy(&rdatas.data()[subset_offset], set.data(), sizeof(int) * set.size());
    rdatas.data()[subset_size_offset] = static_cast<int>(set.size());

    int arrangement_pointer = 0;

    int i = 0;

    int current_result = 0;

    const size_t set_size    = set.size();
    auto         pdata       = rdata.data();
    auto         result_data = results.data();
    auto         prdatas     = rdatas.data();
    int          j           = 0;
    int          dest        = 0;

    while(arrangement_pointer >= 0)
    {

        memcpy(pdata, prdatas + (offset * arrangement_pointer),
               offset * sizeof(int));

        arrangement_pointer--;

        i = static_cast<int>(rdata[subset_size_offset]) - 1;

        for(auto it = i; i >= 0; it--)
        {

            if(((set_size - rdata[subset_size_offset]) + 1) ==
               static_cast<int>(size))
            {
                memcpy(&result_data[current_result * size], pdata,
                       size * sizeof(int));
                result_data[current_result * size + size - 1] =
                    rdata[subset_offset + (rdata[subset_size_offset] - 1 - it)];
                current_result++;
                i--;
                continue;
            }

            arrangement_pointer++;
            dest = arrangement_pointer * offset;

            memcpy(&rdatas[dest], pdata, sizeof(int) * size);

            rdatas[dest + set_size - rdata[subset_size_offset]] =
                rdata[subset_offset + it];

            memcpy(&rdatas[dest + subset_offset], &rdata[subset_offset],
                   sizeof(int) * set_size);

            rdatas[dest + subset_size_offset] = rdata[subset_size_offset] - 1;

            for(j = i; j < rdata[subset_size_offset] - 1; j++)
            {
                rdatas[dest + subset_offset + j] =
                    rdatas[dest + subset_offset + j + 1];
            }

            i--;
        }
    }
    return results;
}

int arrangements_size(int set_item, int size)
{
    return factorial(set_item) / factorial(set_item - size);
}
}    // namespace corgi::algorithms::enumeration