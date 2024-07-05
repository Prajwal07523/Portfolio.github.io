#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct ReturnRequest {
    string orderID;
    string productID;
    string reason;
    string timestamp;
};

queue<ReturnRequest> returnQueue;

void addReturnRequest(const ReturnRequest& request) {
    returnQueue.push(request);
}

void processReturnRequest() {
    if (!returnQueue.empty()) {
        ReturnRequest request = returnQueue.front();
        returnQueue.pop();
        cout << "Processing return for Order ID: " << request.orderID
             << ", Product ID: " << request.productID
             << ", Reason: " << request.reason
             << ", Timestamp: " << request.timestamp << endl;
        // Further processing logic here
    } else {
        cout << "No return requests to process." << endl;
    }
}

int main() {
    addReturnRequest({"order123", "prod456", "Defective item", "2024-06-26T10:00:00Z"});
    addReturnRequest({"order789", "prod101", "Wrong item delivered", "2024-06-26T11:00:00Z"});
    
    processReturnRequest();
    processReturnRequest();
    processReturnRequest();
    
    return 0;
}
