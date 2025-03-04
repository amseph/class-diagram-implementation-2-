#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits> 
using namespace std;


class Customer{
private: 
    string customerName;
    string email; 
    string customerID = "A001";

public:
    void customerInfo (){
        cout<<"\nCustomer Information";
        cout<<"\nCustomer Name: ";
        getline(cin,customerName);
        cout<<"Email: ";
        getline(cin,email);
        cout<<"Customer ID: "<<customerID<<endl;
    }
};

class Product {
private:
    int productID;
    string name;
    double price;

public:
    Product(int productID, string name, double price) : productID(productID), name(name), price(price) {}

    int getProductID() const { return productID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
};

class ShoppingCart {
private:
    vector<pair<Product, int>> products;

public:
    void addProduct(const Product& product, int quantity) {
        products.push_back(make_pair(product, quantity));
        cout << "Product added successfully!" << endl;
    }

    void viewCart() const {
        if (products.empty()) {
            cout << "\nShopping Cart is empty." << endl;
            return;
        }
        
        cout << "\nShopping Cart:" << endl;
        cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(15) << "Price" << setw(15) << "Quantity" << endl;
        for (const auto& item : products) {
            cout << left << setw(15) << item.first.getProductID() 
                 << setw(15) << item.first.getName() 
                 << setw(15) << item.first.getPrice() 
                 << setw(15) << item.second << endl;
        }
    }

    double getTotalPrice() const {
        double total = 0.0;
        for (const auto& item : products) {
            total += item.first.getPrice() * item.second;
        }
        return total;
    }

    void clearCart() { products.clear(); }

    bool isEmpty() const { return products.empty(); }
};

class Order {
private:
    int orderID;
    ShoppingCart cart;
    string orderStatus;

public:
    Order(int orderID, const ShoppingCart& cart) : orderID(orderID), cart(cart), orderStatus("Placed") {}

    void displayOrder() const {
        cout << "\nOrder ID: " << orderID << endl;
        cout << "Total Amount: " << cart.getTotalPrice() << endl;
        cout << "Order Details:" << endl;
        cart.viewCart();
        cout << "Order Status: " << orderStatus << endl;
    }
};


int getValidIntInput(string prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < minVal || value > maxVal) {
            cout << "Invalid Input. Try Again." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            return value;
        }
    }
}

int main() {

    Customer customer;
    customer.customerInfo();



    vector<Product> products = {
        {1, "Paper", 5.0},
        {2, "Pencil", 7.0},
        {3, "Book", 70.0},
        {4, "Notebook", 25.0}
    };

    ShoppingCart cart;
    vector<Order> orders;
    int orderCounter = 1;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. Checkout\n";
        cout << "4. View Orders\n";
        cout << "5. Exit\n";

        choice = getValidIntInput("Enter your choice: ", 1, 5);

        if (choice == 1) {
            cout << "\n" << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(15) << "Price" << endl;
            for (const auto& p : products) {
                cout << left << setw(15) << p.getProductID() 
                     << setw(15) << p.getName() 
                     << setw(15) << p.getPrice() << endl;
            }

            char addMore;
            do {
                int productID = getValidIntInput("Enter the ID of the product to add to cart: ");
                int quantity = getValidIntInput("Enter quantity: ", 1);

                bool productFound = false;
                for (const auto& p : products) {
                    if (p.getProductID() == productID) {
                        cart.addProduct(p, quantity);
                        productFound = true;
                        break;
                    }
                }

                if (!productFound) {
                    cout << "\nInvalid Product ID. Try Again." << endl;
                }

                cout << "Do you want to add another product? (Y/N): ";
                cin >> addMore;

            } while (addMore == 'Y' || addMore == 'y');

        } else if (choice == 2) {
            cart.viewCart();

        } else if (choice == 3) {
            if (!cart.isEmpty()) {
                cout << "\nYou have successfully checked out the products!" << endl;
                orders.emplace_back(orderCounter++, cart);
                cart.clearCart();
            } else {
                cout << "\nCart is empty!" << endl;
            }

        } else if (choice == 4) {
            if (orders.empty()) {
                cout << "\nNo orders placed yet." << endl;
            } else {
                for (const auto& order : orders) {
                    order.displayOrder();
                }
            }

        } else if (choice == 5) {
            cout << "Exiting the program. Thank you!" << endl;
            break;
        }
    }
    
    return 0;
}
