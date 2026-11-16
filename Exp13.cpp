#include <iostream>
#include <vector>
#include <concepts>
#include <ranges>
#include <numeric>
using namespace std;
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;
template <Numeric T>
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
template <Numeric T>
T sumData(const std::vector<T>& data)
{
    return std::accumulate(data.begin(), data.end(), T{});
}

int main()
{
    vector<int> ints = {-5, 10, 20, -3, 15, 30};
    vector<double> reals = {-1.5, 2.5, 4.0, -0.5};

    auto r1 = processData(ints);
    auto r2 = processData(reals);

    cout << "Original Data: ";
    for (int v : ints) cout << v << " ";
    cout << "\nProcessed Data: ";
    for (int v : r1) cout << v << " ";
    cout << "\nSum: " << sumData(r1) << endl;

    cout << "\nDouble Data Processed: ";
    for (double v : r2) cout << v << " ";
    cout << "\nSum: " << sumData(r2) << endl;
    return 0;
}
