#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    string department;
    float cgpa;
    static int count;   // tracks number of active students

public:
    // Constructor
    Student(int r, string n, string d, float c)
    {
        rollNo = r;
        name = n;
        department = d;
        cgpa = c;
        count++;
        cout << "Student object created: " << name << endl;
    }

    // Member function
    void display() const
    {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "CGPA: " << cgpa << endl;
    }

    static int getCount()
    {
        return count;
    }

    // Destructor
    ~Student()
    {
        count--;
        cout << "Student object destroyed: " << name << endl;
    }
};

int Student::count = 0;

int main()
{
    Student s1(101, "Arun", "CSE", 8.5);
    s1.display();

    {
        Student s2(102, "Bala", "IT", 8.1);
        s2.display();
        cout << "Active students: " << Student::getCount() << endl;
    }   

    cout << "Active students after block: " << Student::getCount() << endl;
    return 0;
}
