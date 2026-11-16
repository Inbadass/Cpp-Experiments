#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <memory>
using namespace std;
template <typename T>
class CustomAllocator
{
public:
    using value_type = T;
    CustomAllocator() {}
    template <typename U> CustomAllocator(const CustomAllocator<U>&) {}

    T* allocate(size_t n)
    {
        cout << "[Allocator] Allocating memory for " << n << " object(s)\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_t)
    {
        cout << "[Allocator] Deallocating memory\n";
        ::operator delete(p);
    }
};
template <typename T, typename U>
bool operator==(const CustomAllocator<T>&, const CustomAllocator<U>&) { return true; }
template <typename T, typename U>
bool operator!=(const CustomAllocator<T>&, const CustomAllocator<U>&) { return false; }

struct FileRecord
{
    char fileName[50];
    int fileSize;
};

const char* DB = "filesystem.dat";

void addFile()
{
    FileRecord file{};
    cout << "Enter File Name: ";
    cin >> setw(50) >> file.fileName;
    cout << "Enter File Size (KB): ";
    cin >> file.fileSize;

    ofstream out(DB, ios::binary | ios::app);
    if (out)
    {
        out.write(reinterpret_cast<char*>(&file), sizeof(FileRecord));
        cout << "File record added successfully.\n";
    }
    else
        cout << "Unable to open file.\n";
}
vector<FileRecord, CustomAllocator<FileRecord>> loadAll()
{
    vector<FileRecord, CustomAllocator<FileRecord>> records;
    ifstream in(DB, ios::binary);
    FileRecord f;
    while (in.read(reinterpret_cast<char*>(&f), sizeof(FileRecord)))
        records.push_back(f);
    return records;
}

void displayFiles()
{
    auto records = loadAll();
    if (records.empty()) { cout << "No file records found.\n"; return; }

    cout << "\n--- File System Records ---\n";
    int total = 0;
    for (auto& f : records)
    {
        cout << "File Name : " << f.fileName << endl;
        cout << "File Size : " << f.fileSize << " KB\n";
        cout << "--------------------------\n";
        total += f.fileSize;
    }
    cout << "Total files: " << records.size() << ", Total size: " << total << " KB\n";   // NEW
}
void searchFile()
{
    char name[50];
    cout << "Enter File Name to search: ";
    cin >> setw(50) >> name;

    auto records = loadAll();
    for (auto& f : records)
        if (strcmp(f.fileName, name) == 0)
        {
            cout << "Found: " << f.fileName << " (" << f.fileSize << " KB)\n";
            return;
        }
    cout << "File not found.\n";
}

int main()
{
    int choice;
    do
    {
        cout << "\nMINI FILE SYSTEM SIMULATOR\n";
        cout << "1. Add File\n2. Display Files\n3. Search File\n4. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) break;

        switch (choice)
        {
        case 1: addFile(); break;
        case 2: displayFiles(); break;
        case 3: searchFile(); break;
        case 4: cout << "Exiting File System Simulator...\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
