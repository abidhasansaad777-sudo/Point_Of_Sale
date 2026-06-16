#include "coupon.h"

Coupon::Coupon(QString code, double discountValue, QString type, bool isUsed)
    : code(code), discountValue(discountValue), type(type), isUsed(isUsed) {}

QString Coupon::getCode() const {
    return code;
}

double Coupon::getDiscountValue() const {
    return discountValue;
}

QString Coupon::getType() const {
    return type;
}

bool Coupon::getIsUsed() const {
    return isUsed;
}

void Coupon::markAsUsed() {
    this->isUsed = true;
}

bool Coupon::validate() const {
    return !isUsed;
}