import pipeline;

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> ints = {-5, 10, 20, -3, 15, 30};
    vector<double> reals = {-1.5, 2.5, 4.0, -0.5};   // NEW: works for doubles too

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
