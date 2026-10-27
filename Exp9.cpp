#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

/**
 * @brief Observer interface.
 */
class Observer
{
public:
    virtual void notify(const string& message) = 0;
    virtual string getName() const = 0;
    virtual ~Observer() {}
};

/**
 * @brief Email notification observer.
 */
class EmailNotification : public Observer
{
private:
    string email;
public:
    EmailNotification(string e) { email = e; }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email << ": " << message << endl;
    }

    string getName() const override { return email; }
};

/**
 * @brief SMS notification observer.
 */
class SMSNotification : public Observer
{
private:
    string phoneNumber;
public:
    SMSNotification(string number) { phoneNumber = number; }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber << ": " << message << endl;
    }

    string getName() const override { return phoneNumber; }
};

/**
 * @brief Push notification observer (newly added type).
 */
class PushNotification : public Observer
{
private:
    string deviceId;
public:
    PushNotification(string id) { deviceId = id; }

    void notify(const string& message) override
    {
        cout << "Push sent to device " << deviceId << ": " << message << endl;
    }

    string getName() const override { return deviceId; }
};

/**
 * @brief Factory class for creating notifications.
 */
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
            return make_shared<EmailNotification>(receiver);
        else if (type == "SMS")
            return make_shared<SMSNotification>(receiver);
        else if (type == "PUSH")
            return make_shared<PushNotification>(receiver);

        return nullptr;
    }
};

/**
 * @brief Singleton Event Manager.
 */
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    // Private constructor prevents external object creation
    EventManager() {}

public:
    // Delete copy constructor and assignment operator
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    // Singleton access method
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        if (observer != nullptr)
            observers.push_back(observer);
    }

    // NEW: remove an observer
    void unsubscribe(shared_ptr<Observer> observer)
    {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end());
        cout << "Unsubscribed: " << observer->getName() << endl;
    }

    int getObserverCount() const { return observers.size(); }

    void triggerEvent(const string& message)
    {
        cout << "\nEvent Triggered: " << message << endl;
        cout << "Sending Notifications to " << observers.size() << " observer(s)...\n";

        for (auto observer : observers)
            observer->notify(message);
    }
};

int main()
{
    // Access Singleton EventManager
    EventManager& manager = EventManager::getInstance();

    // Verify singleton: both references point to the same object
    EventManager& manager2 = EventManager::getInstance();
    cout << "Same EventManager instance? "
         << (&manager == &manager2 ? "Yes" : "No") << endl;

    // Create observers using Factory Pattern
    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification("EMAIL", "student@gmail.com");
    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification("SMS", "9876543210");
    shared_ptr<Observer> pushUser =
        NotificationFactory::createNotification("PUSH", "DEVICE-101");
    shared_ptr<Observer> invalidUser =
        NotificationFactory::createNotification("FAX", "12345");

    if (invalidUser == nullptr)
        cout << "Factory: unknown notification type 'FAX' rejected." << endl;

    // Subscribe observers
    manager.subscribe(emailUser);
    manager.subscribe(smsUser);
    manager.subscribe(pushUser);
    manager.subscribe(invalidUser);   // ignored (nullptr)

    // Trigger event
    manager.triggerEvent("University examination starts tomorrow!");

    // Unsubscribe one observer and trigger again
    manager.unsubscribe(smsUser);
    manager.triggerEvent("Result will be published on Friday!");

    return 0;
}
