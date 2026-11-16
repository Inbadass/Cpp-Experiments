export module pipeline;

import <vector>;
import <concepts>;
import <ranges>;
import <numeric>;

export template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Keep positive values, then square them
export template <Numeric T>
std::vector<T> processData(const std::vector<T>& data)
{
    std::vector<T> result;

    auto pipeline = data
        | std::views::filter([](T value) { return value > 0; })
        | std::views::transform([](T value) { return value * value; });

    for (T value : pipeline)
        result.push_back(value);

    return result;
}

// NEW: sum of the processed data
export template <Numeric T>
T sumData(const std::vector<T>& data)
{
    return std::accumulate(data.begin(), data.end(), T{});
}
