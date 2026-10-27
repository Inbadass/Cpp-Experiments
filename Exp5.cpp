#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    vector<Student> students = {
        {"Arun", 85, ' '},
        {"Bala", 72, ' '},
        {"Kumar", 91, ' '},
        {"Ravi", 65, ' '},
        {"Divya", 45, ' '}
    };

    // Sort students based on marks (descending)
    sort(students.begin(), students.end(),
        [](const Student &a, const Student &b)
        {
            return a.mark > b.mark;
        });

    // Assign grades using transform
    transform(students.begin(), students.end(), students.begin(),
        [](Student s)
        {
            if (s.mark >= 90)      s.grade = 'A';
            else if (s.mark >= 75) s.grade = 'B';
            else if (s.mark >= 50) s.grade = 'C';
            else                   s.grade = 'F';
            return s;
        });

    // Find first student scoring above 80
    auto it = find_if(students.begin(), students.end(),
        [](const Student &s) { return s.mark > 80; });

    // Total and average using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
        [](int sum, const Student &s) { return sum + s.mark; });
    float average = (float)total / students.size();

    // NEW: topper, lowest scorer, pass count, above-average count
    auto topper = max_element(students.begin(), students.end(),
        [](const Student &a, const Student &b) { return a.mark < b.mark; });
    auto lowest = min_element(students.begin(), students.end(),
        [](const Student &a, const Student &b) { return a.mark < b.mark; });
    int passCount = count_if(students.begin(), students.end(),
        [](const Student &s) { return s.grade != 'F'; });
    int aboveAvg = count_if(students.begin(), students.end(),
        [average](const Student &s) { return s.mark > average; });

    cout << "Student Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";
    for (const Student &s : students)
        cout << s.name << "\t" << s.mark << "\t" << s.grade << endl;

    if (it != students.end())
        cout << "\nFirst student scoring above 80: " << it->name << endl;

    cout << "Topper: " << topper->name << " (" << topper->mark << ")" << endl;
    cout << "Lowest: " << lowest->name << " (" << lowest->mark << ")" << endl;
    cout << "Total Marks: " << total << endl;
    cout << "Average Mark: " << average << endl;
    cout << "Students Passed: " << passCount << " / " << students.size() << endl;
    cout << "Students Above Average: " << aboveAvg << endl;

    return 0;
}
