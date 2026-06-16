#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include "inventorymanager.h"
#include "customermanager.h"
#include "salesmanager.h"
#include "transaction.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAddProduct_clicked();
    void on_btnUpdateProduct_clicked();
    void on_btnDeleteProduct_clicked();
    void on_btnSearchProduct_clicked();
    void on_btnResetSearch_clicked();
    void on_tableProduct_cellClicked(int row, int column);
    void refreshProductTable();
    void checkLowStockAlerts();


    void on_btnAddToBag_clicked();
    void on_btnApplyCoupon_clicked();
    void on_btnCheckout_clicked();


    void on_btnCreateCoupon_clicked();
    void refreshCouponTable();


    void on_btnAddCustomer_clicked();
    void on_btnUpdateCustomer_clicked();
    void on_btnDeleteCustomer_clicked();
    void on_btnSearchCustomer_clicked();
    void on_btnResetCustomerSearch_clicked();
    void on_tableCustomers_cellClicked(int row, int column);
    void refreshCustomerTable();

private:
    QTabWidget *tabWidget;


    QLineEdit *txtID;
    QLineEdit *txtName;
    QLineEdit *txtCategory;
    QLineEdit *txtPrice;
    QLineEdit *txtStock;
    QPushButton *btnAddProduct;
    QPushButton *btnUpdateProduct;
    QPushButton *btnDeleteProduct;
    QLineEdit *txtSearchQuery;
    QComboBox *cmbSearchType;
    QPushButton *btnSearchProduct;
    QPushButton *btnResetSearch;
    QTableWidget *tableWidget;

    QLineEdit *txtSalesCustomerID;
    QLineEdit *txtSalesProductID;
    QLineEdit *txtSalesQty;
    QLineEdit *txtCouponCode;
    QPushButton *btnAddToBag;
    QPushButton *btnApplyCoupon;
    QPushButton *btnCheckout;
    QTableWidget *tableCart;
    QLabel *lblSubtotal;
    QLabel *lblDiscount;
    QLabel *lblGrandTotal;


    QLabel *lblLiveInvoiceView;
    QTextEdit *txtReceiptDisplay;


    QLineEdit *txtNewCouponCode;
    QLineEdit *txtDiscountValue;
    QComboBox *cmbDiscountType;
    QDateEdit *dteExpiry;
    QPushButton *btnCreateCoupon;
    QTableWidget *tableCoupons;


    QLineEdit *txtCustID;
    QLineEdit *txtCustName;
    QLineEdit *txtCustContact;
    QLineEdit *txtCustEmail;
    QLineEdit *txtCustLoyaltyPoints;
    QPushButton *btnAddCustomer;
    QPushButton *btnUpdateCustomer;
    QPushButton *btnDeleteCustomer;
    QLineEdit *txtCustSearchQuery;
    QComboBox *cmbCustSearchType;
    QPushButton *btnSearchCustomer;
    QPushButton *btnResetCustomerSearch;
    QTableWidget *tableCustomers;
    QTextEdit *txtPurchaseHistoryDisplay;

    InventoryManager inventory;
    CustomerManager customerManager;
    SalesManager salesManager;
    Transaction currentTransaction;
    int transactionCounter;
    const int LOW_STOCK_THRESHOLD = 5;
};
#endif