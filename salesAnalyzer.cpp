#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

// Store sales data per item
struct ItemData {
    int quantity = 0;
    int revenue = 0;
};

// Store sales data per month
struct MonthlySales {
    int total_sales = 0;
    unordered_map<string, ItemData> items;
};

void processSalesData(const string& fileName, unordered_map<string, MonthlySales>& monthlySales, int& totalStoreSales) {
    ifstream file(fileName);
    string line;
    
    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string date, sku, unitPriceStr, quantityStr, totalPriceStr;
        
        // Read the CSV line
        getline(ss, date, ',');
        getline(ss, sku, ',');
        getline(ss, unitPriceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, totalPriceStr, ',');

        int unitPrice = stoi(unitPriceStr);
        int quantity = stoi(quantityStr);
        int totalPrice = stoi(totalPriceStr);

        // Extract year and month (first 7 characters of date)
        string month = date.substr(0, 7);

        totalStoreSales += totalPrice;

        monthlySales[month].total_sales += totalPrice;

        monthlySales[month].items[sku].quantity += quantity;
        monthlySales[month].items[sku].revenue += totalPrice;
    }
    file.close();
}

void printReports(const unordered_map<string, MonthlySales>& monthlySales, int totalStoreSales) {
    cout << "1. Total Sales of the Store: " << totalStoreSales << "\n\n";

    cout << "2. Month-wise Sales Totals:\n";
    for (const auto& entry : monthlySales) {
        const string& month = entry.first;
        const MonthlySales& data = entry.second;
        cout << month << ": " << data.total_sales << "\n";
    }

    cout << "\n3. Most Popular Item in Each Month (Most Quantity Sold):\n";
    for (const auto& entry : monthlySales) {
        const string& month = entry.first;
        const MonthlySales& data = entry.second;
        
        auto mostPopularItem = max_element(data.items.begin(), data.items.end(), 
            [](const pair<string, ItemData>& a, const pair<string, ItemData>& b) {
                return a.second.quantity < b.second.quantity;
            });
        cout << month << ": " << mostPopularItem->first << " (Quantity Sold: " << mostPopularItem->second.quantity << ")\n";
    }

    cout << "\n4. Items Generating Most Revenue in Each Month:\n";
    for (const auto& entry : monthlySales) {
        const string& month = entry.first;
        const MonthlySales& data = entry.second;

        auto mostRevenueItem = max_element(data.items.begin(), data.items.end(), 
            [](const pair<string, ItemData>& a, const pair<string, ItemData>& b) {
                return a.second.revenue < b.second.revenue;
            });
        cout << month << ": " << mostRevenueItem->first << " (Revenue: " << mostRevenueItem->second.revenue << ")\n";
    }

    cout << "\n5. Statistics for the Most Popular Item in Each Month:\n";
    for (const auto& entry : monthlySales) {
        const string& month = entry.first;
        const MonthlySales& data = entry.second;

        auto mostPopularItem = max_element(data.items.begin(), data.items.end(), 
            [](const pair<string, ItemData>& a, const pair<string, ItemData>& b) {
                return a.second.quantity < b.second.quantity;
            });
        
        const ItemData& itemData = mostPopularItem->second;
        int minQuantity = itemData.quantity;
        int maxQuantity = itemData.quantity;
        double avgQuantity = static_cast<double>(itemData.quantity);

        cout << month << ": " << mostPopularItem->first
                  << " - Min: " << minQuantity 
                  << ", Max: " << maxQuantity
                  << ", Avg: " << fixed << setprecision(2) << avgQuantity << "\n";
    }
}

int main() {

    unordered_map<string, MonthlySales> monthlySales;
    int totalStoreSales = 0;

    processSalesData("sales_data.csv", monthlySales, totalStoreSales);

    printReports(monthlySales, totalStoreSales);

    return 0;
}
