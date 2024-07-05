#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Transaction {
    string transactionID;
    double amount;
    string timestamp;
    bool isFraud;
};

vector<Transaction> transactions;

// Function to calculate the likelihood of fraud based on historical data
double calculateFraudLikelihood(const vector<Transaction>& history, const Transaction& current) {
    // DP table to store the likelihoods
    vector<double> dp(history.size() + 1, 0.0);
    double threshold = 1000.0; // Example threshold for high-value transactions

    // Fill the DP table
    for (size_t i = 1; i <= history.size(); ++i) {
        if (history[i - 1].amount > threshold) {
            dp[i] = dp[i - 1] + 1; // Increment fraud likelihood for high-value transactions
        } else {
            dp[i] = dp[i - 1];
        }
    }

    // Calculate the likelihood for the current transaction
    double likelihood = 0.0;
    if (current.amount > threshold) {
        likelihood = dp.back() + 1;
    } else {
        likelihood = dp.back();
    }

    // Normalize likelihood
    return likelihood / (history.size() + 1);
}

int main() {
    // Example transactions
    transactions.push_back({"tx123", 500.0, "2024-06-26T10:00:00Z", false});
    transactions.push_back({"tx124", 1500.0, "2024-06-26T11:00:00Z", false});
    transactions.push_back({"tx125", 800.0, "2024-06-26T12:00:00Z", false});

    // New transaction to evaluate
    Transaction newTransaction = {"tx126", 2000.0, "2024-06-26T13:00:00Z", false};

    // Calculate fraud likelihood
    double fraudLikelihood = calculateFraudLikelihood(transactions, newTransaction);
    cout << "Fraud Likelihood for transaction " << newTransaction.transactionID << ": " << fraudLikelihood << endl;

    // Threshold to determine if a transaction is fraudulent
    double fraudThreshold = 0.5;
    newTransaction.isFraud = (fraudLikelihood > fraudThreshold);

    cout << "Transaction " << newTransaction.transactionID << " is "
         << (newTransaction.isFraud ? "fraudulent" : "not fraudulent") << endl;

    return 0;
}
