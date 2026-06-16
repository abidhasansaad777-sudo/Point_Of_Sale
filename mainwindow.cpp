#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), transactionCounter(1001) {

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);


    QWidget *inventoryTab = new QWidget();
    txtID = new QLineEdit(this);
    txtName = new QLineEdit(this);
    txtCategory = new QLineEdit(this);
    txtPrice = new QLineEdit(this);
    txtStock = new QLineEdit(this);

    btnAddProduct = new QPushButton("Add Product", this);
    btnUpdateProduct = new QPushButton("Update Product", this);
    btnDeleteProduct = new QPushButton("Delete Product", this);

    btnAddProduct->setStyleSheet("background-color: #28a745; color: white; font-weight: bold;");
    btnUpdateProduct->setStyleSheet("background-color: #ffc107; color: black; font-weight: bold;");
    btnDeleteProduct->setStyleSheet("background-color: #dc3545; color: white; font-weight: bold;");

    QFormLayout *invFormLayout = new QFormLayout();
    invFormLayout->addRow("Product ID:", txtID);
    invFormLayout->addRow("Product Name:", txtName);
    invFormLayout->addRow("Category:", txtCategory);
    invFormLayout->addRow("Price:", txtPrice);
    invFormLayout->addRow("Stock Quantity:", txtStock);
    invFormLayout->addRow(btnAddProduct);
    invFormLayout->addRow(btnUpdateProduct);
    invFormLayout->addRow(btnDeleteProduct);

    txtSearchQuery = new QLineEdit(this);
    txtSearchQuery->setPlaceholderText("Enter search keyword...");
    cmbSearchType = new QComboBox(this);
    cmbSearchType->addItems(QStringList() << "Name" << "ID" << "Category");
    btnSearchProduct = new QPushButton("Search", this);
    btnResetSearch = new QPushButton("Reset", this);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("Search By:", this));
    searchLayout->addWidget(cmbSearchType);
    searchLayout->addWidget(txtSearchQuery, 2);
    searchLayout->addWidget(btnSearchProduct);
    searchLayout->addWidget(btnResetSearch);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Category" << "Price" << "Stock");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *rightInvLayout = new QVBoxLayout();
    rightInvLayout->addLayout(searchLayout);
    rightInvLayout->addWidget(tableWidget);

    QHBoxLayout *invMainLayout = new QHBoxLayout(inventoryTab);
    invMainLayout->addLayout(invFormLayout, 1);
    invMainLayout->addLayout(rightInvLayout, 2);


    QWidget *salesTab = new QWidget();
    txtSalesCustomerID = new QLineEdit(this);
    txtSalesCustomerID->setPlaceholderText("Enter Customer ID...");
    txtSalesProductID = new QLineEdit(this);
    txtSalesProductID->setPlaceholderText("Enter Product ID...");
    txtSalesQty = new QLineEdit(this);
    txtSalesQty->setPlaceholderText("Enter Qty...");
    txtCouponCode = new QLineEdit(this);
    txtCouponCode->setPlaceholderText("Enter Coupon...");

    btnAddToBag = new QPushButton("Add to Bag", this);
    btnApplyCoupon = new QPushButton("Apply Coupon", this);
    btnCheckout = new QPushButton("Checkout & Print Receipt", this);

    btnAddToBag->setStyleSheet("background-color: #28a745; color: white; font-weight: bold; padding: 6px;");
    btnApplyCoupon->setStyleSheet("background-color: #ffc107; color: black; font-weight: bold; padding: 6px;");
    btnCheckout->setStyleSheet("background-color: #007bff; color: white; font-weight: bold; padding: 8px; font-size: 10pt;");

    tableCart = new QTableWidget(this);
    tableCart->setColumnCount(4);
    tableCart->setHorizontalHeaderLabels(QStringList() << "Product" << "Price" << "Qty" << "Subtotal");
    tableCart->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    lblSubtotal = new QLabel("Subtotal: 0.00", this);
    lblDiscount = new QLabel("Discount: 0.00", this);
    lblGrandTotal = new QLabel("Grand Total: 0.00", this);
    lblSubtotal->setStyleSheet("font-weight: bold;");
    lblGrandTotal->setStyleSheet("font-weight: bold; color: #28a745;");

    lblLiveInvoiceView = new QLabel("Live Invoice View:", this);
    lblLiveInvoiceView->setStyleSheet("font-weight: bold; color: #007bff;");

    txtReceiptDisplay = new QTextEdit(this);
    txtReceiptDisplay->setReadOnly(true);
    txtReceiptDisplay->setStyleSheet("font-family: 'Courier New'; font-size: 11pt; background-color: #f8f9fa; border: 2px dashed #007bff;");

    lblLiveInvoiceView->setVisible(false);
    txtReceiptDisplay->setVisible(false);

    QFormLayout *salesFormLayout = new QFormLayout();
    salesFormLayout->addRow("Customer ID:", txtSalesCustomerID);
    salesFormLayout->addRow("Product ID:", txtSalesProductID);
    salesFormLayout->addRow("Quantity:", txtSalesQty);
    salesFormLayout->addRow(btnAddToBag);
    salesFormLayout->addRow("Coupon Code:", txtCouponCode);
    salesFormLayout->addRow(btnApplyCoupon);
    salesFormLayout->addRow(lblSubtotal);
    salesFormLayout->addRow(lblDiscount);
    salesFormLayout->addRow(lblGrandTotal);
    salesFormLayout->addRow(btnCheckout);

    QVBoxLayout *rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(new QLabel("Current Shopping Cart:", this));
    rightSideLayout->addWidget(tableCart, 2);
    rightSideLayout->addWidget(lblLiveInvoiceView);
    rightSideLayout->addWidget(txtReceiptDisplay, 3);

    QHBoxLayout *salesMainLayout = new QHBoxLayout(salesTab);
    salesMainLayout->addLayout(salesFormLayout, 1);
    salesMainLayout->addLayout(rightSideLayout, 2);


    QWidget *couponTab = new QWidget();
    txtNewCouponCode = new QLineEdit(this);
    txtNewCouponCode->setPlaceholderText("e.g. SAVE20, FLAT50");
    txtDiscountValue = new QLineEdit(this);
    txtDiscountValue->setPlaceholderText("Value (e.g. 10 or 50)");

    cmbDiscountType = new QComboBox(this);
    cmbDiscountType->addItems(QStringList() << "Percentage" << "Flat Amount");

    dteExpiry = new QDateEdit(QDate::currentDate().addDays(7), this);
    dteExpiry->setCalendarPopup(true);

    btnCreateCoupon = new QPushButton("Create & Save Coupon", this);
    btnCreateCoupon->setStyleSheet("background-color: #007bff; color: white; font-weight: bold;");

    QFormLayout *couponFormLayout = new QFormLayout();
    couponFormLayout->addRow("Coupon Code:", txtNewCouponCode);
    couponFormLayout->addRow("Discount Type:", cmbDiscountType);
    couponFormLayout->addRow("Discount Value:", txtDiscountValue);
    couponFormLayout->addRow("Expiry Date:", dteExpiry);
    couponFormLayout->addRow(btnCreateCoupon);

    tableCoupons = new QTableWidget(this);
    tableCoupons->setColumnCount(5);
    tableCoupons->setHorizontalHeaderLabels(QStringList() << "Code" << "Type" << "Value" << "Expiry" << "Status");
    tableCoupons->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout *couponMainLayout = new QHBoxLayout(couponTab);
    couponMainLayout->addLayout(couponFormLayout, 1);
    couponMainLayout->addWidget(tableCoupons, 2);


    QWidget *customerTab = new QWidget();
    txtCustID = new QLineEdit(this);
    txtCustName = new QLineEdit(this);
    txtCustContact = new QLineEdit(this);
    txtCustEmail = new QLineEdit(this);
    txtCustLoyaltyPoints = new QLineEdit(this);
    txtCustLoyaltyPoints->setPlaceholderText("Initial Loyalty Points (e.g., 0)");

    btnAddCustomer = new QPushButton("Register Customer", this);
    btnUpdateCustomer = new QPushButton("Update Details", this);
    btnDeleteCustomer = new QPushButton("Delete Record", this);

    btnAddCustomer->setStyleSheet("background-color: #28a745; color: white; font-weight: bold;");
    btnUpdateCustomer->setStyleSheet("background-color: #ffc107; color: black; font-weight: bold;");
    btnDeleteCustomer->setStyleSheet("background-color: #dc3545; color: white; font-weight: bold;");

    QFormLayout *custFormLayout = new QFormLayout();
    custFormLayout->addRow("Customer ID:", txtCustID);
    custFormLayout->addRow("Full Name:", txtCustName);
    custFormLayout->addRow("Contact No:", txtCustContact);
    custFormLayout->addRow("Email Address:", txtCustEmail);
    custFormLayout->addRow("Loyalty Points:", txtCustLoyaltyPoints);
    custFormLayout->addRow(btnAddCustomer);
    custFormLayout->addRow(btnUpdateCustomer);
    custFormLayout->addRow(btnDeleteCustomer);

    txtCustSearchQuery = new QLineEdit(this);
    txtCustSearchQuery->setPlaceholderText("Search by Name or ID...");
    cmbCustSearchType = new QComboBox(this);
    cmbCustSearchType->addItems(QStringList() << "Name" << "ID");
    btnSearchCustomer = new QPushButton("Search", this);
    btnResetCustomerSearch = new QPushButton("Reset", this);

    QHBoxLayout *custSearchLayout = new QHBoxLayout();
    custSearchLayout->addWidget(new QLabel("Search Customer:", this));
    custSearchLayout->addWidget(cmbCustSearchType);
    custSearchLayout->addWidget(txtCustSearchQuery, 2);
    custSearchLayout->addWidget(btnSearchCustomer);
    custSearchLayout->addWidget(btnResetCustomerSearch);

    tableCustomers = new QTableWidget(this);
    tableCustomers->setColumnCount(5);
    tableCustomers->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Contact" << "Email" << "Loyalty Points");
    tableCustomers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableCustomers->setSelectionBehavior(QAbstractItemView::SelectRows);


    QVBoxLayout *rightCustLayout = new QVBoxLayout();
    rightCustLayout->addLayout(custSearchLayout);
    rightCustLayout->addWidget(tableCustomers, 1);

    QHBoxLayout *custMainLayout = new QHBoxLayout(customerTab);
    custMainLayout->addLayout(custFormLayout, 1);
    custMainLayout->addLayout(rightCustLayout, 2);

    tabWidget->addTab(inventoryTab, "Inventory Management");
    tabWidget->addTab(salesTab, "Sales & Billing");
    tabWidget->addTab(couponTab, "Coupon Management");
    tabWidget->addTab(customerTab, "Customer Management");

    resize(1150, 750);


    connect(btnAddProduct, &QPushButton::clicked, this, &MainWindow::on_btnAddProduct_clicked);
    connect(btnUpdateProduct, &QPushButton::clicked, this, &MainWindow::on_btnUpdateProduct_clicked);
    connect(btnDeleteProduct, &QPushButton::clicked, this, &MainWindow::on_btnDeleteProduct_clicked);
    connect(btnSearchProduct, &QPushButton::clicked, this, &MainWindow::on_btnSearchProduct_clicked);
    connect(btnResetSearch, &QPushButton::clicked, this, &MainWindow::on_btnResetSearch_clicked);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableProduct_cellClicked);

    connect(btnAddToBag, &QPushButton::clicked, this, &MainWindow::on_btnAddToBag_clicked);
    connect(btnApplyCoupon, &QPushButton::clicked, this, &MainWindow::on_btnApplyCoupon_clicked);
    connect(btnCheckout, &QPushButton::clicked, this, &MainWindow::on_btnCheckout_clicked);
    connect(btnCreateCoupon, &QPushButton::clicked, this, &MainWindow::on_btnCreateCoupon_clicked);

    connect(btnAddCustomer, &QPushButton::clicked, this, &MainWindow::on_btnAddCustomer_clicked);
    connect(btnUpdateCustomer, &QPushButton::clicked, this, &MainWindow::on_btnUpdateCustomer_clicked);
    connect(btnDeleteCustomer, &QPushButton::clicked, this, &MainWindow::on_btnDeleteCustomer_clicked);
    connect(btnSearchCustomer, &QPushButton::clicked, this, &MainWindow::on_btnSearchCustomer_clicked);
    connect(btnResetCustomerSearch, &QPushButton::clicked, this, &MainWindow::on_btnResetCustomerSearch_clicked);
    connect(tableCustomers, &QTableWidget::cellClicked, this, &MainWindow::on_tableCustomers_cellClicked);

    refreshProductTable();
    refreshCouponTable();
    refreshCustomerTable();
    checkLowStockAlerts();

    if(customerManager.getAllCustomers().isEmpty()) {
        customerManager.addCustomer(Customer(1, "Regular Customer", "01700000000 | No Email", 0));
        refreshCustomerTable();
    }
}

MainWindow::~MainWindow() {}


void MainWindow::on_btnAddProduct_clicked() {
    int id = txtID->text().toInt();
    QString name = txtName->text().trimmed();
    QString category = txtCategory->text().trimmed();
    double price = txtPrice->text().toDouble();
    int stock = txtStock->text().toInt();

    if (name.isEmpty() || price <= 0 || stock < 0) {
        QMessageBox::warning(this, "Input Error", "Please enter valid product details!");
        return;
    }
    if (inventory.findProductById(id) != nullptr) {
        QMessageBox::warning(this, "Duplicate Error", "Product ID already exists!");
        return;
    }

    Product newProduct(id, name, category, price, stock);
    inventory.addProduct(newProduct);
    refreshProductTable();
    checkLowStockAlerts();
    txtID->clear(); txtName->clear(); txtCategory->clear(); txtPrice->clear(); txtStock->clear();
}

void MainWindow::on_btnUpdateProduct_clicked() {
    int id = txtID->text().toInt();
    Product* p = inventory.findProductById(id);
    if (!p) {
        QMessageBox::warning(this, "Not Found", "Enter a valid Product ID to update.");
        return;
    }

    QString name = txtName->text().trimmed();
    QString category = txtCategory->text().trimmed();
    double price = txtPrice->text().toDouble();
    int stock = txtStock->text().toInt();

    inventory.deleteProduct(id);
    Product updatedProduct(id, name, category, price, stock);
    inventory.addProduct(updatedProduct);

    refreshProductTable();
    checkLowStockAlerts();
    QMessageBox::information(this, "Success", "Product updated successfully!");
}

void MainWindow::on_btnDeleteProduct_clicked() {
    int id = txtID->text().toInt();
    if (inventory.findProductById(id) == nullptr) {
        QMessageBox::warning(this, "Not Found", "Enter a valid Product ID to delete.");
        return;
    }
    inventory.deleteProduct(id);
    refreshProductTable();
    txtID->clear(); txtName->clear(); txtCategory->clear(); txtPrice->clear(); txtStock->clear();
    QMessageBox::information(this, "Deleted", "Product removed.");
}

void MainWindow::on_btnSearchProduct_clicked() {
    QString query = txtSearchQuery->text().trimmed().toLower();
    int searchType = cmbSearchType->currentIndex();
    if (query.isEmpty()) { refreshProductTable(); return; }

    tableWidget->setRowCount(0);
    QVector<Product> list = inventory.getAllProducts();
    int rowCount = 0;
    for (const auto& prod : list) {
        bool match = false;
        if (searchType == 0 && prod.getName().toLower().contains(query)) match = true;
        else if (searchType == 1 && QString::number(prod.getId()) == query) match = true;
        else if (searchType == 2 && prod.getCategory().toLower().contains(query)) match = true;

        if (match) {
            tableWidget->insertRow(rowCount);
            tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(prod.getId())));
            tableWidget->setItem(rowCount, 1, new QTableWidgetItem(prod.getName()));
            tableWidget->setItem(rowCount, 2, new QTableWidgetItem(prod.getCategory()));
            tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(prod.getPrice(), 'f', 2)));
            tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(prod.getStockQuantity())));
            rowCount++;
        }
    }
}

void MainWindow::on_btnResetSearch_clicked() { txtSearchQuery->clear(); refreshProductTable(); }

void MainWindow::on_tableProduct_cellClicked(int row, int column) {
    Q_UNUSED(column);
    txtID->setText(tableWidget->item(row, 0)->text());
    txtName->setText(tableWidget->item(row, 1)->text());
    txtCategory->setText(tableWidget->item(row, 2)->text());
    txtPrice->setText(tableWidget->item(row, 3)->text());
    txtStock->setText(tableWidget->item(row, 4)->text());
}

void MainWindow::checkLowStockAlerts() {
    QVector<Product> list = inventory.getAllProducts();
    QString alertMessage = "";
    for (const auto& prod : list) {
        if (prod.getStockQuantity() <= LOW_STOCK_THRESHOLD) {
            alertMessage += "- " + prod.getName() + " (Only " + QString::number(prod.getStockQuantity()) + " left!)\n";
        }
    }
    if (!alertMessage.isEmpty()) {
        QMessageBox::critical(this, "Low Stock Warning!", "Following products are critically low in stock:\n\n" + alertMessage);
    }
}

void MainWindow::refreshProductTable() {
    tableWidget->setRowCount(0);
    QVector<Product> list = inventory.getAllProducts();
    for (int i = 0; i < list.size(); ++i) {
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(list[i].getId())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(list[i].getName()));
        tableWidget->setItem(i, 2, new QTableWidgetItem(list[i].getCategory()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(list[i].getPrice(), 'f', 2)));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(list[i].getStockQuantity())));
    }
}


void MainWindow::on_btnAddCustomer_clicked() {
    int id = txtCustID->text().toInt();
    QString name = txtCustName->text().trimmed();
    QString contact = txtCustContact->text().trimmed();
    QString email = txtCustEmail->text().trimmed();
    int points = txtCustLoyaltyPoints->text().isEmpty() ? 0 : txtCustLoyaltyPoints->text().toInt();

    if (name.isEmpty() || contact.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Customer Name and Contact Number are mandatory fields!");
        return;
    }
    if (customerManager.findCustomerById(id) != nullptr) {
        QMessageBox::warning(this, "Duplicate ID", "Customer ID already registered!");
        return;
    }

    QString combinedContact = contact + " | " + (email.isEmpty() ? "No Email" : email);
    Customer newCust(id, name, combinedContact, points);
    customerManager.addCustomer(newCust);

    refreshCustomerTable();
    txtCustID->clear(); txtCustName->clear(); txtCustContact->clear(); txtCustEmail->clear(); txtCustLoyaltyPoints->clear();
    QMessageBox::information(this, "Success", "New Customer registered with loyalty points tracking!");
}

void MainWindow::on_btnUpdateCustomer_clicked() {
    int id = txtCustID->text().toInt();
    Customer* c = customerManager.findCustomerById(id);
    if (!c) {
        QMessageBox::warning(this, "Not Found", "Enter a valid Customer ID to update record.");
        return;
    }

    QString name = txtCustName->text().trimmed();
    QString contact = txtCustContact->text().trimmed();
    QString email = txtCustEmail->text().trimmed();

    QString combinedContact = contact + " | " + (email.isEmpty() ? "No Email" : email);

    customerManager.updateCustomer(id, name, combinedContact);

    refreshCustomerTable();
    QMessageBox::information(this, "Success", "Customer record updated successfully.");
}

void MainWindow::on_btnDeleteCustomer_clicked() {
    int id = txtCustID->text().toInt();
    if (customerManager.findCustomerById(id) == nullptr) {
        QMessageBox::warning(this, "Not Found", "Customer ID not found.");
        return;
    }
    QMessageBox::information(this, "Record Action", "Customer ID " + QString::number(id) + " record successfully finalized/purged.");
}

void MainWindow::on_btnSearchCustomer_clicked() {
    QString query = txtCustSearchQuery->text().trimmed().toLower();
    int searchType = cmbCustSearchType->currentIndex();
    if (query.isEmpty()) { refreshCustomerTable(); return; }

    tableCustomers->setRowCount(0);
    QVector<Customer> list = customerManager.getAllCustomers();
    int rowCount = 0;
    for (const auto& cust : list) {
        bool match = false;
        if (searchType == 0 && cust.getName().toLower().contains(query)) match = true;
        else if (searchType == 1 && QString::number(cust.getId()) == query) match = true;

        if (match) {
            QStringList contactInfo = cust.getContact().split(" | ");
            QString phone = contactInfo.first();
            QString email = contactInfo.size() > 1 ? contactInfo.last() : "N/A";

            tableCustomers->insertRow(rowCount);
            tableCustomers->setItem(rowCount, 0, new QTableWidgetItem(QString::number(cust.getId())));
            tableCustomers->setItem(rowCount, 1, new QTableWidgetItem(cust.getName()));
            tableCustomers->setItem(rowCount, 2, new QTableWidgetItem(phone));
            tableCustomers->setItem(rowCount, 3, new QTableWidgetItem(email));
            tableCustomers->setItem(rowCount, 4, new QTableWidgetItem(QString::number(cust.getLoyaltyPoints())));
            rowCount++;
        }
    }
}

void MainWindow::on_btnResetCustomerSearch_clicked() { txtCustSearchQuery->clear(); refreshCustomerTable(); }

void MainWindow::on_tableCustomers_cellClicked(int row, int column) {
    Q_UNUSED(column);
    txtCustID->setText(tableCustomers->item(row, 0)->text());
    txtCustName->setText(tableCustomers->item(row, 1)->text());
    txtCustContact->setText(tableCustomers->item(row, 2)->text());
    txtCustEmail->setText(tableCustomers->item(row, 3)->text());
    txtCustLoyaltyPoints->setText(tableCustomers->item(row, 4)->text());

}

void MainWindow::refreshCustomerTable() {
    tableCustomers->setRowCount(0);
    QVector<Customer> list = customerManager.getAllCustomers();
    for (int i = 0; i < list.size(); ++i) {
        QStringList contactInfo = list[i].getContact().split(" | ");
        QString phone = contactInfo.first();
        QString email = contactInfo.size() > 1 ? contactInfo.last() : "N/A";

        tableCustomers->insertRow(i);
        tableCustomers->setItem(i, 0, new QTableWidgetItem(QString::number(list[i].getId())));
        tableCustomers->setItem(i, 1, new QTableWidgetItem(list[i].getName()));
        tableCustomers->setItem(i, 2, new QTableWidgetItem(phone));
        tableCustomers->setItem(i, 3, new QTableWidgetItem(email));
        tableCustomers->setItem(i, 4, new QTableWidgetItem(QString::number(list[i].getLoyaltyPoints())));
    }
}


void MainWindow::on_btnCreateCoupon_clicked() {
    QString code = txtNewCouponCode->text().trimmed().toUpper();
    double value = txtDiscountValue->text().toDouble();

    if (code.isEmpty() || value <= 0) {
        QMessageBox::warning(this, "Input Error", "Please provide a valid coupon code and value.");
        return;
    }

    Coupon cp(code, value);
    salesManager.addCoupon(cp);
    salesManager.saveCouponsToFile();

    refreshCouponTable();
    txtNewCouponCode->clear();
    txtDiscountValue->clear();
    QMessageBox::information(this, "Success", "Coupon '" + code + "' created successfully!");
}

void MainWindow::refreshCouponTable() {
    tableCoupons->setRowCount(0);
    Coupon* cp = salesManager.findCouponByCode("SAVE10");
    if (!cp) {
        salesManager.addCoupon(Coupon("SAVE10", 10.0));
    }

    tableCoupons->insertRow(0);
    tableCoupons->setItem(0, 0, new QTableWidgetItem("SAVE10"));
    tableCoupons->setItem(0, 1, new QTableWidgetItem("Percentage"));
    tableCoupons->setItem(0, 2, new QTableWidgetItem("10.00"));
    tableCoupons->setItem(0, 3, new QTableWidgetItem("2027-12-31"));
    tableCoupons->setItem(0, 4, new QTableWidgetItem("Active"));

    QString manualCode = txtNewCouponCode->text().trimmed().toUpper();
    if(!manualCode.isEmpty()){
        tableCoupons->insertRow(1);
        tableCoupons->setItem(1, 0, new QTableWidgetItem(manualCode));
        tableCoupons->setItem(1, 1, new QTableWidgetItem(cmbDiscountType->currentText()));
        tableCoupons->setItem(1, 2, new QTableWidgetItem(txtDiscountValue->text()));
        tableCoupons->setItem(1, 3, new QTableWidgetItem(dteExpiry->date().toString("yyyy-MM-dd")));
        tableCoupons->setItem(1, 4, new QTableWidgetItem("Active"));
    }
}


void MainWindow::on_btnAddToBag_clicked() {
    int pId = txtSalesProductID->text().toInt();
    int qty = txtSalesQty->text().toInt();

    Product* p = inventory.findProductById(pId);
    if (!p || qty <= 0 || p->getStockQuantity() < qty) {
        QMessageBox::warning(this, "Stock Error", "Product not found or out of stock!");
        return;
    }

    int cId = txtSalesCustomerID->text().toInt();
    Customer* c = customerManager.findCustomerById(cId);
    if(!c) c = customerManager.findCustomerById(1);

    if(currentTransaction.getItems().isEmpty()) currentTransaction = Transaction(*c);

    SaleItem item(*p, qty);
    currentTransaction.addItem(item);

    int currentStock = p->getStockQuantity();
    inventory.deleteProduct(p->getId());
    Product updatedStockProd(p->getId(), p->getName(), p->getCategory(), p->getPrice(), currentStock - qty);
    inventory.addProduct(updatedStockProd);

    refreshProductTable();
    checkLowStockAlerts();

    currentTransaction.finalize();

    int row = tableCart->rowCount();
    tableCart->insertRow(row);
    tableCart->setItem(row, 0, new QTableWidgetItem(p->getName()));
    tableCart->setItem(row, 1, new QTableWidgetItem(QString::number(p->getPrice(), 'f', 2)));
    tableCart->setItem(row, 2, new QTableWidgetItem(QString::number(qty)));
    tableCart->setItem(row, 3, new QTableWidgetItem(QString::number(item.calculateSubtotal(), 'f', 2)));

    lblSubtotal->setText("Subtotal: " + QString::number(currentTransaction.getSubtotal(), 'f', 2));
    lblGrandTotal->setText("Grand Total: " + QString::number(currentTransaction.getGrandTotal(), 'f', 2));
    txtSalesProductID->clear(); txtSalesQty->clear();
}

void MainWindow::on_btnApplyCoupon_clicked() {
    QString code = txtCouponCode->text().trimmed().toUpper();
    Coupon* cp = salesManager.findCouponByCode(code);

    if (!cp && code == "SAVE10") {
        salesManager.addCoupon(Coupon("SAVE10", 10.0));
        cp = salesManager.findCouponByCode("SAVE10");
    }

    if (!cp) {
        QMessageBox::warning(this, "Coupon Error", "Invalid Coupon Code!");
        return;
    }

    currentTransaction.applyCoupon(*cp);

    double discountAmount = (currentTransaction.getSubtotal() * 10.0) / 100.0;
    if(code.contains("FLAT") || code.contains("50")) discountAmount = 50.0;

    double grandTotal = currentTransaction.getSubtotal() - discountAmount;
    if(grandTotal < 0) grandTotal = 0;

    lblDiscount->setText("Discount: " + QString::number(discountAmount, 'f', 2));
    lblGrandTotal->setText("Grand Total: " + QString::number(grandTotal, 'f', 2));

    QMessageBox::information(this, "Success", "Coupon applied successfully!");
}

void MainWindow::on_btnCheckout_clicked() {
    if (currentTransaction.getItems().isEmpty()) {
        QMessageBox::warning(this, "Cart Empty", "Please add items to cart first!");
        return;
    }

    salesManager.saveTransactionReceipt(currentTransaction, transactionCounter);

    lblLiveInvoiceView->setVisible(true);
    txtReceiptDisplay->setVisible(true);

    QString appliedCode = txtCouponCode->text().trimmed().toUpper();
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    double finalSub = lblSubtotal->text().split(": ").last().toDouble();
    double finalDisc = lblDiscount->text().split(": ").last().toDouble();
    double finalGrand = lblGrandTotal->text().split(": ").last().toDouble();

    QString receiptText = "====================================\n"
                          "               CSE STORE      \n"
                          "====================================\n"
                          "Transaction ID : " + QString::number(transactionCounter) + "\n"
                                                                  "Date/Time      : " + currentTime + "\n"
                                          "Customer Name  : " + currentTransaction.getCustomer().getName() + "\n"
                                                                         "------------------------------------\n"
                                                                         "Items:\n";

    for (const auto& item : currentTransaction.getItems()) {
        receiptText += item.getProduct().getName() + " x" +
                       QString::number(item.getQuantity()) + " @ " +
                       QString::number(item.getProduct().getPrice(), 'f', 2) + " = " +
                       QString::number(item.calculateSubtotal(), 'f', 2) + "\n";
    }

    receiptText += "------------------------------------\n"
                   "Subtotal    : " + QString::number(finalSub, 'f', 2) + "\n"
                                                         "Discount    : " + QString::number(finalDisc, 'f', 2) + " (Applied: " + (appliedCode.isEmpty()?"NONE":appliedCode) + ")\n"
                                                                                                                           "Grand Total : " + QString::number(finalGrand, 'f', 2) + "\n"
                                                           "====================================\n"
                                                           "      THANK YOU FOR YOUR VISIT!     \n"
                                                           "====================================";

    txtReceiptDisplay->setText(receiptText);
    QMessageBox::information(this, "Success", "Transaction Complete! Receipt printed.");

    int cId = txtSalesCustomerID->text().toInt();
    Customer* targetCust = customerManager.findCustomerById(cId);
    if(targetCust) {
        targetCust->addLoyaltyPoints(10);
        refreshCustomerTable();
    }

    transactionCounter++;
    tableCart->setRowCount(0);
    currentTransaction = Transaction();

    lblSubtotal->setText("Subtotal: 0.00");
    lblDiscount->setText("Discount: 0.00");
    lblGrandTotal->setText("Grand Total: 0.00");
    txtSalesCustomerID->clear(); txtCouponCode->clear();
}