#include "product.h"

Product::Product(int id, QString name, QString category, double price, int stockQuantity)
    : id(id), name(name), category(category), price(price), stockQuantity(stockQuantity) {}

int Product::getId() const {
    return id;
}

QString Product::getName() const {
    return name;
}

QString Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getStockQuantity() const {
    return stockQuantity;
}

void Product::setStockQuantity(int qty) {
    stockQuantity = qty;
}

void Product::updateProduct(QString name, QString category, double price, int stockQuantity) {
    this->name = name;
    this->category = category;
    this->price = price;
    this->stockQuantity = stockQuantity;
}