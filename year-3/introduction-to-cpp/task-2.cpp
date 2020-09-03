/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>

size_t compute_sequence_until_sum_reaches(long limit, long a_0, long a_1, long a_2)
{
    if (a_0 > limit)
        return 1;
    else if (a_0 + a_1 > limit)
        return 2;
    else if (a_0 + a_1 + a_2 > limit)
        return 3;

    long sum = a_0 + a_1 + a_2;
    size_t count = 3;
    while (sum <= limit)
    {
        long new_val = 3 * a_0 + a_2;
        a_0 = a_1;
        a_1 = a_2;
        a_2 = new_val;

        sum += new_val;
        ++count;
    }

    return count;
}

int main()
{
    long limit;
    std::cout << "Enter the limit:" << std::endl;
    std::cin >> limit;

    long a_0, a_1, a_2;
    std::cout << "Enter the first three numbers of the sequence:" << std::endl;
    std::cin >> a_0 >> a_1 >> a_2;

    size_t count = compute_sequence_until_sum_reaches(limit, a_0, a_1, a_2);
    std::cout << "There were " << count << " elements computed before their sum went over " << limit << std::endl;

    return 0;
}