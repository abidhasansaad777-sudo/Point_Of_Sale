#include "customermanager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

CustomerManager::CustomerManager(QString filename)
    : filename(filename) {
    loadFromFile();
}

void CustomerManager::addCustomer(const Customer& customer) {
    customers.append(customer);
    saveToFile();
}

void CustomerManager::updateCustomer(int id, QString name, QString contact) {
    for (auto& c : customers) {
        if (c.getId() == id) {
            c.updateCustomer(name, contact);
            break;
        }
    }
    saveToFile();
}

void CustomerManager::addPointsToCustomer(int id, int points) {
    for (auto& c : customers) {
        if (c.getId() == id) {
            c.addLoyaltyPoints(points);
            break;
        }
    }
    saveToFile();
}

Customer* CustomerManager::findCustomerById(int id) {
    for (auto& c : customers) {
        if (c.getId() == id) {
            return &c;
        }
    }
    return nullptr;
}

QVector<Customer> CustomerManager::getAllCustomers() const {
    return customers;
}

void CustomerManager::loadFromFile() {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    customers.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(",");
        if (tokens.size() == 4) {
            int id = tokens[0].toInt();
            QString name = tokens[1];
            QString contact = tokens[2];
            int points = tokens[3].toInt();
            customers.append(Customer(id, name, contact, points));
        }
    }
    file.close();
}

void CustomerManager::saveToFile() {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto& c : customers) {
        out << c.getId() << ","
            << c.getName() << ","
            << c.getContact() << ","
            << c.getLoyaltyPoints() << "\n";
    }
    file.close();
}