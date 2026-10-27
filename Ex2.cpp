#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Shape
{
public:
    virtual float area() const = 0;          // Pure virtual function
    virtual string name() const = 0;
    virtual ~Shape() {}                      // Virtual destructor
};

class Circle : public Shape
{
private:
    float radius;
public:
    Circle(float r) { radius = r; }
    float area() const override { return 3.14f * radius * radius; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape
{
private:
    float length, breadth;
public:
    Rectangle(float l, float b) { length = l; breadth = b; }
    float area() const override { return length * breadth; }
    string name() const override { return "Rectangle"; }
};

class Triangle : public Shape
{
private:
    float base, height;
public:
    Triangle(float b, float h) { base = b; height = h; }
    float area() const override { return 0.5f * base * height; }
    string name() const override { return "Triangle"; }
};

int main()
{
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5));
    shapes.push_back(new Rectangle(4, 6));
    shapes.push_back(new Triangle(10, 8));

    float total = 0;
    Shape* largest = shapes[0];

    for (Shape* s : shapes)
    {
        cout << "Area of " << s->name() << ": " << s->area() << endl;
        total += s->area();
        if (s->area() > largest->area())
            largest = s;
    }

    cout << "Total Area: " << total << endl;
    cout << "Largest Shape: " << largest->name() << endl;

    for (Shape* s : shapes)
        delete s;                            // safe because of virtual destructor

    return 0;
}
