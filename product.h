#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product {
private:
    int id;
    QString name;
    QString category;
    double price;
    int stockQuantity;

public:
    Product(int id = 0, QString name = "", QString category = "", double price = 0.0, int stockQuantity = 0);

    int getId() const;
    QString getName() const;
    QString getCategory() const;
    double getPrice() const;
    int getStockQuantity() const;

    void setStockQuantity(int qty);
    void updateProduct(QString name, QString category, double price, int stockQuantity);
};

#endif