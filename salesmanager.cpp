#include "salesmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>

SalesManager::SalesManager(QString couponFile, QString salesFile)
    : couponFilename(couponFile), salesFilename(salesFile) {
    loadCouponsFromFile();
}

void SalesManager::addCoupon(const Coupon& coupon) {
    coupons.append(coupon);
    saveCouponsToFile();
}

Coupon* SalesManager::findCouponByCode(QString code) {
    for (auto& cp : coupons) {
        if (cp.getCode() == code) {
            return &cp;
        }
    }
    return nullptr;
}

void SalesManager::saveTransactionReceipt(const Transaction& transaction, int transactionId) {
    QFile file(salesFilename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    out << transactionId << ","
        << currentTime << ","
        << transaction.getCustomer().getId() << ","
        << transaction.getSubtotal() << ","
        << transaction.getDiscount() << ","
        << transaction.getGrandTotal() << "\n";

    file.close();

    QFile receiptFile("receipt_" + QString::number(transactionId) + ".txt");
    if (receiptFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream rout(&receiptFile);
        rout << "====================================\n";
        rout << "         POINT OF SALE RECEIPT      \n";
        rout << "====================================\n";
        rout << "Transaction ID: " << transactionId << "\n";
        rout << "Date/Time: " << currentTime << "\n";
        rout << "Customer ID: " << transaction.getCustomer().getId() << "\n";
        rout << "Customer Name: " << transaction.getCustomer().getName() << "\n";
        rout << "------------------------------------\n";
        rout << "Items:\n";

        for (const auto& item : transaction.getItems()) {
            rout << item.getProduct().getName() << " x"
                 << item.getQuantity() << " @ "
                 << item.getProduct().getPrice() << " = "
                 << item.calculateSubtotal() << "\n";
        }

        rout << "------------------------------------\n";
        rout << "Subtotal: " << transaction.getSubtotal() << "\n";
        rout << "Discount: " << transaction.getDiscount() << "\n";
        rout << "Grand Total: " << transaction.getGrandTotal() << "\n";
        rout << "====================================\n";
        receiptFile.close();
    }
}

void SalesManager::loadCouponsFromFile() {
    QFile file(couponFilename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    coupons.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(",");
        if (tokens.size() == 4) {
            QString code = tokens[0];
            double value = tokens[1].toDouble();
            QString type = tokens[2];
            bool isUsed = (tokens[3].toInt() == 1);
            coupons.append(Coupon(code, value, type, isUsed));
        }
    }
    file.close();
}

void SalesManager::saveCouponsToFile() {
    QFile file(couponFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto& cp : coupons) {
        out << cp.getCode() << ","
            << cp.getDiscountValue() << ","
            << cp.getType() << ","
            << (cp.getIsUsed() ? 1 : 0) << "\n";
    }
    file.close();
}