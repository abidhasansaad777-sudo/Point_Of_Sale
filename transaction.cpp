#include "transaction.h"

Transaction::Transaction(Customer customer)
    : customer(customer), subtotal(0.0), discount(0.0), grandTotal(0.0) {}

void Transaction::addItem(const SaleItem& item) {
    items.append(item);
}

void Transaction::applyCoupon(const Coupon& cp) {
    this->coupon = cp;
}

QVector<SaleItem> Transaction::getItems() const {
    return items;
}

Customer Transaction::getCustomer() const {
    return customer;
}

Coupon Transaction::getCoupon() const {
    return coupon;
}

double Transaction::getSubtotal() const {
    return subtotal;
}

double Transaction::getDiscount() const {
    return discount;
}

double Transaction::getGrandTotal() const {
    return grandTotal;
}

void Transaction::finalize() {
    subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item.calculateSubtotal();
    }

    discount = 0.0;
    if (coupon.validate()) {
        if (coupon.getType() == "Percentage") {
            discount = subtotal * (coupon.getDiscountValue() / 100.0);
        } else if (coupon.getType() == "Flat") {
            discount = coupon.getDiscountValue();
        }
    }

    grandTotal = subtotal - discount;
    if (grandTotal < 0.0) {
        grandTotal = 0.0;
    }
}