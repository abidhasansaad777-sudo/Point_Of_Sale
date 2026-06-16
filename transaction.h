#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QVector>
#include "saleitem.h"
#include "customer.h"
#include "coupon.h"

class Transaction {
private:
    QVector<SaleItem> items;
    Customer customer;
    Coupon coupon;
    double subtotal;
    double discount;
    double grandTotal;

public:
    Transaction(Customer customer = Customer());

    void addItem(const SaleItem& item);
    void applyCoupon(const Coupon& coupon);

    QVector<SaleItem> getItems() const;
    Customer getCustomer() const;
    Coupon getCoupon() const;
    double getSubtotal() const;
    double getDiscount() const;
    double getGrandTotal() const;

    void finalize();
};

#endif