#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Product {
    int price;
    int profit;
};

int optimizeDiscounts(vector<Product>& products, int budget) {
    int n = products.size();
    vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= budget; ++j) {
            if (products[i-1].price <= j) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - products[i-1].price] + products[i-1].profit);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n][budget];
}

int main() {
    vector<Product> products = {
        {10, 60},
        {20, 100},
        {30, 120}
    };
    int budget = 50;
    cout << "Maximum profit: " << optimizeDiscounts(products, budget) << endl;
    return 0;
}
