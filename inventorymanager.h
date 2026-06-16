#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QVector>
#include <QString>
#include "product.h"

class InventoryManager {
private:
    QVector<Product> products;
    QString filename;

public:
    InventoryManager(QString filename = "products.csv");

    void addProduct(const Product& product);
    void updateProduct(int id, QString name, QString category, double price, int stockQuantity);
    void deleteProduct(int id);
    Product* findProductById(int id);
    QVector<Product> getAllProducts() const;

    void loadFromFile();
    void saveToFile();
};

#endif