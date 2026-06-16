#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer {
private:
    int id;
    QString name;
    QString contact;
    int loyaltyPoints;

public:
    Customer(int id = 0, QString name = "", QString contact = "", int points = 0);

    int getId() const;
    QString getName() const;
    QString getContact() const;
    int getLoyaltyPoints() const;

    void addLoyaltyPoints(int points);
    void updateCustomer(QString name, QString contact);
};

#endif