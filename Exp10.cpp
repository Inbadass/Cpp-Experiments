#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>
using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv;

const int MAX_ITEMS = 10;
atomic<int> producedCount(0);
atomic<int> consumedCount(0);      // NEW
atomic<long> consumedSum(0);       // NEW
atomic<bool> finished(false);

void producer()
{
    for (int i = 1; i <= MAX_ITEMS; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(50));
        {
            lock_guard<mutex> lock(mtx);
            buffer.push(i);
            producedCount++;
            cout << "Produced: " << i << endl;
        }
        cv.notify_one();
    }
    {
        lock_guard<mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();
}

// NEW: consumers have IDs, and there are two of them
void consumer(int id)
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty() || finished; });

        if (buffer.empty() && finished) break;

        int item = buffer.front();
        buffer.pop();
        consumedCount++;
        consumedSum += item;
        cout << "Consumer " << id << " consumed: " << item << endl;
    }
}

int main()
{
    cout << "Producer-Consumer System Started\n" << endl;

    thread p(producer);
    thread c1(consumer, 1);
    thread c2(consumer, 2);

    p.join();
    c1.join();
    c2.join();

    cout << "\nTotal Items Produced: " << producedCount << endl;
    cout << "Total Items Consumed: " << consumedCount << endl;
    cout << "Sum of consumed items: " << consumedSum << endl;
    cout << "Producer-Consumer System Completed" << endl;
    return 0;
}
