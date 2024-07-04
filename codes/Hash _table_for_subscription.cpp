#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Subscription {
    string product;
    int quantity;
    int deliveryFrequency; // in days
};

unordered_map<string, vector<Subscription>> subscriptions;

void addSubscription(const string& customerID, const Subscription& subscription) {
    subscriptions[customerID].push_back(subscription);
}

void removeSubscription(const string& customerID, const string& product) {
    if (subscriptions.find(customerID) != subscriptions.end()) {
        auto& subs = subscriptions[customerID];
        subs.erase(remove_if(subs.begin(), subs.end(), [&](const Subscription& sub) {
            return sub.product == product;
        }), subs.end());
    }
}

void printSubscriptions(const string& customerID) {
    if (subscriptions.find(customerID) != subscriptions.end()) {
        cout << "Subscriptions for customer " << customerID << ":\n";
        for (const auto& sub : subscriptions[customerID]) {
            cout << "- Product: " << sub.product << ", Quantity: " << sub.quantity 
                 << ", Frequency: " << sub.deliveryFrequency << " days\n";
        }
    } else {
        cout << "No subscriptions found for customer " << customerID << ".\n";
    }
}

int main() {
    addSubscription("customer1", {"Milk", 2, 7});
    addSubscription("customer1", {"Eggs", 12, 14});
    addSubscription("customer2", {"Bread", 1, 3});
    
    printSubscriptions("customer1");
    printSubscriptions("customer2");
    
    removeSubscription("customer1", "Milk");
    
    printSubscriptions("customer1");
    
    return 0;
}
