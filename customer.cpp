#include "customer.h"

Customer::Customer(int id, QString name, QString contact, int points)
    : id(id), name(name), contact(contact), loyaltyPoints(points) {}

int Customer::getId() const {
    return id;
}

QString Customer::getName() const {
    return name;
}

QString Customer::getContact() const {
    return contact;
}

int Customer::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void Customer::addLoyaltyPoints(int points) {
    this->loyaltyPoints += points;
}

void Customer::updateCustomer(QString name, QString contact) {
    this->name = name;
    this->contact = contact;
}