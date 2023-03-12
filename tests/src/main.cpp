#include <corgi/algorithms/enumeration.h>
#include <corgi/test/test.h>

using namespace corgi;

std::vector<std::vector<int>> r1;
std::vector<std::vector<int>> r2;
std::vector<int>              r3;

void first_func()
{
    std::vector<int> keys {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int              elements = 9;
    r1 = algorithms::enumeration::find_arrangements(keys, elements);
}

void second_func()
{
    std::vector<int> keys {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int              elements = 9;
    r2 = algorithms::enumeration::find_arrangements_iterative(keys, elements);
}

void third_func()
{
    std::vector<int> keys {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int              elements = 9;
    r3 = algorithms::enumeration::find_arrangements_opt(keys, elements);
}

int main()
{
    test::add_benchmark("arrangements", 100, &first_func, "recursive",
                        &second_func, "iterative");

    test::add_benchmark("arrangements", 100, &second_func, "iterative",
                        &third_func, "optimized");

    test::add_test(
        "arrangements", "recursive",
        []() -> void
        {
            std::vector<int> keys {1, 2, 3};
            int              elements = 2;
            auto             result =
                algorithms::enumeration::find_arrangements(keys, elements);

            assert_that(result.size(),
                        test::equals(algorithms::enumeration::arrangements_size(
                            static_cast<long>(keys.size()), elements)));

            assert_that(result[0][0], test::equals(1));
            assert_that(result[0][1], test::equals(2));

            assert_that(result[1][0], test::equals(1));
            assert_that(result[1][1], test::equals(3));

            assert_that(result[2][0], test::equals(2));
            assert_that(result[2][1], test::equals(1));

            assert_that(result[3][0], test::equals(2));
            assert_that(result[3][1], test::equals(3));

            assert_that(result[4][0], test::equals(3));
            assert_that(result[4][1], test::equals(1));

            assert_that(result[5][0], test::equals(3));
            assert_that(result[5][1], test::equals(2));
        });

    test::add_test(
        "arrangements", "iterative",
        []() -> void
        {
            std::vector<int> keys {1, 2, 3};
            int              elements = 2;
            auto result = algorithms::enumeration::find_arrangements_iterative(
                keys, elements);

            assert_that(result.size(),
                        test::equals(algorithms::enumeration::arrangements_size(
                            static_cast<long>(keys.size()), elements)));

            assert_that(result[0][0], test::equals(1));
            assert_that(result[0][1], test::equals(2));

            assert_that(result[1][0], test::equals(1));
            assert_that(result[1][1], test::equals(3));

            assert_that(result[2][0], test::equals(2));
            assert_that(result[2][1], test::equals(1));

            assert_that(result[3][0], test::equals(2));
            assert_that(result[3][1], test::equals(3));

            assert_that(result[4][0], test::equals(3));
            assert_that(result[4][1], test::equals(1));

            assert_that(result[5][0], test::equals(3));
            assert_that(result[5][1], test::equals(2));
        });

    test::add_test(
        "arrangements", "one_array",
        []() -> void
        {
            std::vector<int> keys {1, 2, 3};
            int              elements = 2;
            auto             result =
                algorithms::enumeration::find_arrangements_opt(keys, elements);

            assert_that(
                result.size(),
                test::equals(algorithms::enumeration::arrangements_size(
                                 static_cast<long>(keys.size()), elements) *
                             elements));

            assert_that(result[0], test::equals(1));
            assert_that(result[1], test::equals(2));

            assert_that(result[2], test::equals(1));
            assert_that(result[3], test::equals(3));

            assert_that(result[4], test::equals(2));
            assert_that(result[5], test::equals(1));

            assert_that(result[6], test::equals(2));
            assert_that(result[7], test::equals(3));

            assert_that(result[8], test::equals(3));
            assert_that(result[9], test::equals(1));

            assert_that(result[10], test::equals(3));
            assert_that(result[11], test::equals(2));
        });

    test::run_all();
    return 0;
}