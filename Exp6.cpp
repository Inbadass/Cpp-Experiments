#include <iostream>
#include <memory>
using namespace std;

// Resource class
class Resource
{
private:
    int id;
public:
    Resource(int i = 0) : id(i)
    {
        cout << "Resource " << id << " acquired" << endl;
    }
    ~Resource()
    {
        cout << "Resource " << id << " released" << endl;
    }
    void use()
    {
        cout << "Resource " << id << " is being used" << endl;
    }
};

// Manual Smart Pointer using RAII
class MySmartPointer
{
private:
    Resource* ptr;
public:
    MySmartPointer(Resource* p) { ptr = p; }

    ~MySmartPointer()
    {
        delete ptr;
        cout << "Manual smart pointer destroyed" << endl;
    }

    Resource* operator->() { return ptr; }
    Resource& operator*()  { return *ptr; }
    Resource* get() const  { return ptr; }

    // Disable copying to avoid double deletion
    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main()
{
    cout << "----- Manual RAII Smart Pointer -----" << endl;
    {
        MySmartPointer smartPtr(new Resource(1));
        smartPtr->use();
        (*smartPtr).use();
    }

    cout << "\n----- unique_ptr -----" << endl;
    {
        unique_ptr<Resource> uniquePtr = make_unique<Resource>(2);
        uniquePtr->use();

        // Ownership transfer
        unique_ptr<Resource> newOwner = move(uniquePtr);
        cout << "Original unique_ptr is "
             << (uniquePtr ? "not empty" : "empty") << " after move" << endl;
        newOwner->use();
    }

    cout << "\n----- shared_ptr -----" << endl;
    {
        shared_ptr<Resource> sharedPtr1 = make_shared<Resource>(3);
        shared_ptr<Resource> sharedPtr2 = sharedPtr1;
        sharedPtr1->use();
        cout << "Shared Pointer Count: " << sharedPtr1.use_count() << endl;

        sharedPtr2.reset();
        cout << "Count after sharedPtr2.reset(): " << sharedPtr1.use_count() << endl;

        // weak_ptr does not increase the reference count
        weak_ptr<Resource> weakPtr = sharedPtr1;
        cout << "Count with weak_ptr attached: " << sharedPtr1.use_count() << endl;
    }

    cout << "\nProgram completed successfully." << endl;
    return 0;
}
