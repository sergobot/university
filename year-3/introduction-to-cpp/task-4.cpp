/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

int main() {
    std::vector<std::vector<std::string>> table = {{"N", "x / pi", "cos x", "sin x"}};

    size_t max_n;
    std::cout << "What is the desired maximum value of N?" << std::endl << ">>> ";
    std::cin >> max_n;

    std::stringstream formatter;
    formatter.precision(3);
    formatter.setf(std::stringstream::scientific);

    std::vector<size_t> column_length;
    for (std::string & s : table[0])
        column_length.push_back(s.length());
    std::vector<size_t> rightmost_point = {0, 0, 0};

    double prod = 1;
    for (size_t i = 1; i <= max_n; ++i)
    {
        prod *= i;
        double x = M_PI / prod;
        double x_over_pi = x / M_PI;
        double cos_x = cos(x), sin_x = sin(x);

        std::vector<std::string> row;

        formatter << i << " " << x_over_pi << " " << cos_x << " " << sin_x;
        std::string si, sxopi, scx, ssx;
        formatter >> si >> sxopi >> scx >> ssx;
        row.push_back(si);
        row.push_back(sxopi);
        row.push_back(scx);
        row.push_back(ssx);

        column_length[0] = std::max(column_length[0], si.length());
        column_length[1] = std::max(column_length[1], sxopi.length());
        column_length[2] = std::max(column_length[2], scx.length());
        column_length[3] = std::max(column_length[3], ssx.length());

        rightmost_point[0] = std::max(rightmost_point[0], sxopi.find('.'));
        rightmost_point[1] = std::max(rightmost_point[1], scx.find('.'));
        rightmost_point[2] = std::max(rightmost_point[2], ssx.find('.'));

        table.push_back(row);
        formatter.clear();
    }

    for (size_t i = 0; i < table.size(); ++i)
        for (size_t j = 0; j < 4; ++j)
        {
            auto row = table[i];
            std::string prespace, postspace;

            if (i == 0)
            {
                size_t pre = (column_length[j] - row[j].length()) / 2;
                size_t post = (column_length[j] - row[j].length() + 1) / 2;
                prespace = std::string(pre, ' '), postspace = std::string(post, ' ');
            }
            else
            {
                if (j == 0)
                {
                    prespace = std::string(column_length[j] - row[j].length(), ' ');
                }
                else
                {
                    long point = row[j].find('.');
                    if (rightmost_point[j - 1] - point > 0)
                        prespace = std::string(rightmost_point[j - 1] - point, ' ');
                    if (column_length[j] - rightmost_point[j - 1] + point > 0)
                        postspace = std::string(column_length[j] - rightmost_point[j - 1] + point - row[j].length(), ' ');
                }
            }

            std::cout << prespace << row[j] << postspace << (j < 3 ? " | " : "\n");
        }

    return 0;
}