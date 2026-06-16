#ifndef COUPON_H
#define COUPON_H

#include <QString>

class Coupon {
private:
    QString code;
    double discountValue;
    QString type;
    bool isUsed;

public:
    Coupon(QString code = "", double discountValue = 0.0, QString type = "Percentage", bool isUsed = false);

    QString getCode() const;
    double getDiscountValue() const;
    QString getType() const;
    bool getIsUsed() const;

    void markAsUsed();
    bool validate() const;
};

#endif