#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include <QVector>
#include <QString>
#include "coupon.h"
#include "transaction.h"

class SalesManager {
private:
    QVector<Coupon> coupons;
    QString couponFilename;
    QString salesFilename;

public:
    SalesManager(QString couponFile = "coupons.csv", QString salesFile = "sales.csv");

    void addCoupon(const Coupon& coupon);
    Coupon* findCouponByCode(QString code);
    void saveTransactionReceipt(const Transaction& transaction, int transactionId);

    void loadCouponsFromFile();
    void saveCouponsToFile();
};

#endif