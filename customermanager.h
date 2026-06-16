#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <QVector>
#include <QString>
#include "customer.h"

class CustomerManager {
private:
    QVector<Customer> customers;
    QString filename;

public:
    CustomerManager(QString filename = "customers.csv");

    void addCustomer(const Customer& customer);
    void updateCustomer(int id, QString name, QString contact);
    void addPointsToCustomer(int id, int points);
    Customer* findCustomerById(int id);
    QVector<Customer> getAllCustomers() const;

    void loadFromFile();
    void saveToFile();
};

#endif