#include "saleitem.h"

SaleItem::SaleItem(Product product, int quantity)
    : product(product), quantity(quantity) {}

Product SaleItem::getProduct() const {
    return product;
}

int SaleItem::getQuantity() const {
    return quantity;
}

double SaleItem::calculateSubtotal() const {
    return product.getPrice() * quantity;
}