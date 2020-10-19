/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <vector>
#include <array>

size_t compute_sequence_until_sum_reaches(long limit, long a_0, long a_1, long a_2, size_t max_count = 100)
{
    if (a_0 > limit)
        return 1;
    if (a_0 + a_1 > limit)
        return 2;
    if (a_0 + a_1 + a_2 > limit)
        return 3;

    size_t count = 3;
    for (long sum = a_0 + a_1 + a_2, new_val; std::abs(sum) <= limit && count < max_count; sum += new_val, ++count)
    {
        new_val = 3 * a_0 + a_2;
        a_0 = a_1;
        a_1 = a_2;
        a_2 = new_val;
    }

    return count < max_count ? count : 0;
}

int main()
{
    std::vector<std::pair<std::array<long, 4>, size_t>> tests = {
            {{10, 1, 0, -1}, 8},
            {{10, 0, 1, -1}, 10},
            {{10, 0, 0, 0}, 0},
            {{10, 11, 5, 1}, 1},
            {{10, 10, 5, 1}, 2},
            {{10, 7, 5, 2}, 2},
            {{10, 7, 3, 2}, 3},
            {{10, 5, 4, 3}, 3}
    };

    size_t passed_tests_count = 0;
    for (const auto & test : tests)
    {
        long limit = test.first.at(0),
             a_0   = test.first.at(1),
             a_1   = test.first.at(2),
             a_2   = test.first.at(3);

        size_t target_count = test.second;
        size_t count = compute_sequence_until_sum_reaches(limit, a_0, a_1, a_2);

        bool passed = target_count == count;
        std::cout << a_0 << ", " << a_1 << ", " << a_2 << " until sum reaches " << limit
                  << (passed ? " (TEST PASSED)" : " (TEST FAILED)") << std::endl
                  << "    " << "Expected count = " << target_count << std::endl
                  << "    " << "Got      count = " << count << std::endl;

        passed_tests_count += passed;
    }

    std::cout << std::endl << passed_tests_count << " tests passed, " << tests.size() - passed_tests_count << " tests failed" << std::endl;

    return 0;
}