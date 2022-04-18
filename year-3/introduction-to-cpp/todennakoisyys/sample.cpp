#include <map>
#include <algorithm>

#include "sample.h"

Sample::Sample(std::vector<double> values)
    : values(values)
{
}

GroupedSample Sample::group() const
{
    std::vector<GroupedPoint> groupedValues;

    std::map<double, size_t> counts;
    for (const double & v : values)
    {
        std::map<double, size_t>::iterator it(counts.find(v));
        if (it != counts.end()){
           it->second++;
        } else {
           counts[v] = 1;
        }
    }

    for (const auto& pair : counts)
        groupedValues.emplace_back(pair.first, pair.second);

    std::sort(groupedValues.begin(), groupedValues.end(),
              [](const GroupedPoint& a, const GroupedPoint& b) { return a.value() < b.value(); });

    return GroupedSample(groupedValues);
}
