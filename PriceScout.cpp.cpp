#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct Product {
    string name;
    double price;
    string store;
};

// Dynamic array for products
struct ProductArray {
    Product* data;
    int size;
    int capacity;

    ProductArray(int cap) : size(0), capacity(cap) {
        data = new Product[capacity];
    }

    void add(Product product) {
        if (size == capacity) {
            capacity *= 2;
            Product* newData = new Product[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = product;
    }

    Product& operator[](int index) {
        return data[index];
    }

    ~ProductArray() {
        delete[] data;
    }
};

// Comparator for min-heap
struct ComparePrice {
    bool operator()(Product const& p1, Product const& p2) {
        return p1.price > p2.price;
    }
};

// Main Price Comparison system
class PriceComparison {
    ProductArray products = ProductArray(10); // Dynamic array for storing products
    unordered_map<string, ProductArray*> storeMap; // Hash map for store-wise products
    priority_queue<Product, vector<Product>, ComparePrice> minHeap; // Min-heap for cheapest products

public:
    // Add a product to the system
    void addProduct(string name, double price, string store) {
        Product p = {name, price, store};
        products.add(p);

        if (storeMap.find(store) == storeMap.end()) {
            storeMap[store] = new ProductArray(10);
        }
        storeMap[store]->add(p);
        minHeap.push(p);
    }

    // Helper function to round to two decimal places
    double roundToTwoDecimals(double value) {
        return static_cast<int>(value * 100 + 0.5) / 100.0;
    }

    // Display cheapest products
    void displayCheapestProducts(int k) {
        cout << "\n-----------------------------\n";
        cout << "Top " << k << " Cheapest Products:\n";
        cout << "-----------------------------\n";
        auto tempHeap = minHeap;
        for (int i = 0; i < k && !tempHeap.empty(); ++i) {
            Product p = tempHeap.top();
            tempHeap.pop();
            cout << "Product: " << p.name << "\n"
                 << "Price: " << roundToTwoDecimals(p.price) << "\n"
                 << "Store: " << p.store << "\n";
            cout << "-----------------------------\n";
        }
    }
};

int main() {
    PriceComparison system;

    // Adding sample products
    system.addProduct("Laptop", 550.00, "Amazon");
    system.addProduct("Laptop", 500.00, "eBay");
    system.addProduct("Phone", 300.00, "BestBuy");
    system.addProduct("Tablet", 200.00, "Amazon");
    system.addProduct("Headphones", 50.00, "eBay");
    system.addProduct("Phone", 250.00, "Amazon");
    system.addProduct("Tablet", 450.00, "eBay");


    // Display cheapest products
    system.displayCheapestProducts(3);

    return 0;
}
