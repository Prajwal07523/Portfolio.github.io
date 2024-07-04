#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int optimizeSpace(vector<int>& itemSizes, int warehouseSize) {
    vector<int> dp(warehouseSize + 1, 0);
    
    for (int size : itemSizes) {
        for (int j = warehouseSize; j >= size; --j) {
            dp[j] = max(dp[j], dp[j - size] + size);
        }
    }
    
    return dp[warehouseSize];
}

int main() {
    vector<int> itemSizes = {3, 5, 7, 9};
    int warehouseSize = 15;
    
    int optimizedSpace = optimizeSpace(itemSizes, warehouseSize);
    cout << "Optimized space usage: " << optimizedSpace << endl;
    
    return 0;
}
