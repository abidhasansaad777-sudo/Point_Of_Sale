#include "inventorymanager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

InventoryManager::InventoryManager(QString filename)
    : filename(filename) {
    loadFromFile();
}

void InventoryManager::addProduct(const Product& product) {
    products.append(product);
    saveToFile();
}

void InventoryManager::updateProduct(int id, QString name, QString category, double price, int stockQuantity) {
    for (auto& p : products) {
        if (p.getId() == id) {
            p.updateProduct(name, category, price, stockQuantity);
            break;
        }
    }
    saveToFile();
}

void InventoryManager::deleteProduct(int id) {
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].getId() == id) {
            products.removeAt(i);
            break;
        }
    }
    saveToFile();
}

Product* InventoryManager::findProductById(int id) {
    for (auto& p : products) {
        if (p.getId() == id) {
            return &p;
        }
    }
    return nullptr;
}

QVector<Product> InventoryManager::getAllProducts() const {
    return products;
}

void InventoryManager::loadFromFile() {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    products.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(",");
        if (tokens.size() == 5) {
            int id = tokens[0].toInt();
            QString name = tokens[1];
            QString category = tokens[2];
            double price = tokens[3].toDouble();
            int stock = tokens[4].toInt();
            products.append(Product(id, name, category, price, stock));
        }
    }
    file.close();
}

void InventoryManager::saveToFile() {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto& p : products) {
        out << p.getId() << ","
            << p.getName() << ","
            << p.getCategory() << ","
            << p.getPrice() << ","
            << p.getStockQuantity() << "\n";
    }
    file.close();
}