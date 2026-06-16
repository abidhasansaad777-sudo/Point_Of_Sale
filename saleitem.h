#ifndef SALEITEM_H
#define SALEITEM_H

#include "product.h"

class SaleItem {
private:
    Product product;
    int quantity;

public:
    SaleItem(Product product = Product(), int quantity = 0);

    Product getProduct() const;
    int getQuantity() const;
    double calculateSubtotal() const;
};

#endif