#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Promotion {
    int startTime;
    int endTime;
    int effectiveness; // higher value means better promotion
};

bool comparePromotions(const Promotion& a, const Promotion& b) {
    return a.effectiveness > b.effectiveness;
}

vector<Promotion> schedulePromotions(vector<Promotion>& promotions) {
    sort(promotions.begin(), promotions.end(), comparePromotions);

    vector<Promotion> schedule;
    int currentTime = 0;

    for (const auto& promo : promotions) {
        if (promo.startTime >= currentTime) {
            schedule.push_back(promo);
            currentTime = promo.endTime;
        }
    }

    return schedule;
}

int main() {
    vector<Promotion> promotions = {
        {1, 3, 50},
        {2, 5, 30},
        {4, 6, 60},
        {7, 8, 40}
    };

    vector<Promotion> scheduledPromotions = schedulePromotions(promotions);

    cout << "Scheduled Promotions:" << endl;
    for (const auto& promo : scheduledPromotions) {
        cout << "Start: " << promo.startTime << ", End: " << promo.endTime << ", Effectiveness: " << promo.effectiveness << endl;
    }

    return 0;
}
