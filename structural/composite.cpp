/*
It is a structural design pattern that lets you compose objects into tree structure to represent
part whole heirchies

you can treat a group of objects just like you would treat a single object
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class CartItem {
public:
    virtual ~CartItem() = default;

    virtual double getPrice() const = 0;

    virtual void display(const string& indent) const = 0;
};

class Product : public CartItem {
private:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {}

    double getPrice() const override {
        return price;
    }

    void display(const string& indent) const override {
        cout << indent << "Product: " << name << " - \u20B9" << price << "\n";
    }
};

class ProductBundle : public CartItem {
private:
    string bundleName;

    vector<shared_ptr<CartItem>> items;

public:
    ProductBundle(const string& bundleName) : bundleName(bundleName) {}

    void addItem(const shared_ptr<CartItem>& item) {
        items.push_back(item);
    }

    double getPrice() const override {
        double total = 0;

        for (const auto& item : items) {
            total += item->getPrice();
        }

        return total;
    }

    void display(const string& indent) const override {
        cout << indent << "Bundle: " << bundleName << "\n";

        for (const auto& item : items) {
            item->display(indent + "  ");
        }
    }
};

int main() {
    shared_ptr<CartItem> book = make_shared<Product>("Atomic Habits", 499);
    shared_ptr<CartItem> phone = make_shared<Product>("iPhone 15", 79999);
    shared_ptr<CartItem> earbuds = make_shared<Product>("AirPods", 15999);
    shared_ptr<CartItem> charger = make_shared<Product>("20W Charger", 1999);

    shared_ptr<ProductBundle> iphoneCombo = make_shared<ProductBundle>("iPhone Essentials Combo");
    iphoneCombo->addItem(phone);
    iphoneCombo->addItem(earbuds);
    iphoneCombo->addItem(charger);

    shared_ptr<ProductBundle> schoolKit = make_shared<ProductBundle>("Back to School Kit");
    schoolKit->addItem(make_shared<Product>("Notebook Pack", 249));
    schoolKit->addItem(make_shared<Product>("Pen Set", 99));
    schoolKit->addItem(make_shared<Product>("Highlighter", 149));

    shared_ptr<ProductBundle> megaBundle = make_shared<ProductBundle>("Mega Festival Bundle");
    megaBundle->addItem(book);
    megaBundle->addItem(iphoneCombo);
    megaBundle->addItem(schoolKit);

    vector<shared_ptr<CartItem>> cart;
    cart.push_back(book);
    cart.push_back(iphoneCombo);
    cart.push_back(schoolKit);
    cart.push_back(megaBundle);

    cout << "Your Amazon Cart:\n";
    double total = 0;

    for (const auto& item : cart) {
        item->display("  ");
        total += item->getPrice();
    }

    cout << "\nTotal: \u20B9" << total << "\n";
    return 0;
}



// now suppose the client add this to cart he can add both single product and productBundle.
// so there will be an issue