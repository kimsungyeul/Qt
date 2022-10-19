/********************************************************************************
** Form generated from reading UI file 'ordermanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGERFORM_H
#define UI_ORDERMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderManagerForm
{
public:
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *clientcomboBox;
    QComboBox *clientInfocomboBox;
    QTreeWidget *clienttreeWidget;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *productcomboBox;
    QComboBox *productInfocomboBox;
    QTreeWidget *producttreeWidget;
    QFormLayout *formLayout;
    QLabel *oidLabel;
    QLineEdit *oidLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *pnameLabel;
    QLineEdit *pnameLineEdit;
    QLabel *stockLabel;
    QLineEdit *stockLineEdit;
    QLabel *amountLabel;
    QSpinBox *amountspinBox;
    QLabel *totalpriceLabel;
    QLineEdit *totalpriceLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addpushButton;
    QPushButton *modifypushButton;
    QPushButton *deletepushButton;
    QTreeWidget *ordertreeWidget;

    void setupUi(QWidget *OrderManagerForm)
    {
        if (OrderManagerForm->objectName().isEmpty())
            OrderManagerForm->setObjectName(QString::fromUtf8("OrderManagerForm"));
        OrderManagerForm->resize(628, 430);
        horizontalLayout_4 = new QHBoxLayout(OrderManagerForm);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter = new QSplitter(OrderManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        clientcomboBox = new QComboBox(layoutWidget);
        clientcomboBox->addItem(QString());
        clientcomboBox->addItem(QString());
        clientcomboBox->addItem(QString());
        clientcomboBox->setObjectName(QString::fromUtf8("clientcomboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(clientcomboBox->sizePolicy().hasHeightForWidth());
        clientcomboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(clientcomboBox);

        clientInfocomboBox = new QComboBox(layoutWidget);
        clientInfocomboBox->setObjectName(QString::fromUtf8("clientInfocomboBox"));
        clientInfocomboBox->setEnabled(true);

        horizontalLayout->addWidget(clientInfocomboBox);


        verticalLayout->addLayout(horizontalLayout);

        clienttreeWidget = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("CID"));
        clienttreeWidget->setHeaderItem(__qtreewidgetitem);
        clienttreeWidget->setObjectName(QString::fromUtf8("clienttreeWidget"));

        verticalLayout->addWidget(clienttreeWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        productcomboBox = new QComboBox(layoutWidget);
        productcomboBox->addItem(QString());
        productcomboBox->addItem(QString());
        productcomboBox->addItem(QString());
        productcomboBox->setObjectName(QString::fromUtf8("productcomboBox"));
        productcomboBox->setEnabled(true);
        sizePolicy.setHeightForWidth(productcomboBox->sizePolicy().hasHeightForWidth());
        productcomboBox->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(productcomboBox);

        productInfocomboBox = new QComboBox(layoutWidget);
        productInfocomboBox->setObjectName(QString::fromUtf8("productInfocomboBox"));

        horizontalLayout_2->addWidget(productInfocomboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        producttreeWidget = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("PID"));
        producttreeWidget->setHeaderItem(__qtreewidgetitem1);
        producttreeWidget->setObjectName(QString::fromUtf8("producttreeWidget"));

        verticalLayout->addWidget(producttreeWidget);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        oidLabel = new QLabel(layoutWidget);
        oidLabel->setObjectName(QString::fromUtf8("oidLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, oidLabel);

        oidLineEdit = new QLineEdit(layoutWidget);
        oidLineEdit->setObjectName(QString::fromUtf8("oidLineEdit"));
        oidLineEdit->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        oidLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, oidLineEdit);

        nameLabel = new QLabel(layoutWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(layoutWidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        pnameLabel = new QLabel(layoutWidget);
        pnameLabel->setObjectName(QString::fromUtf8("pnameLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pnameLabel);

        pnameLineEdit = new QLineEdit(layoutWidget);
        pnameLineEdit->setObjectName(QString::fromUtf8("pnameLineEdit"));
        pnameLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::FieldRole, pnameLineEdit);

        stockLabel = new QLabel(layoutWidget);
        stockLabel->setObjectName(QString::fromUtf8("stockLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, stockLabel);

        stockLineEdit = new QLineEdit(layoutWidget);
        stockLineEdit->setObjectName(QString::fromUtf8("stockLineEdit"));
        stockLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::FieldRole, stockLineEdit);

        amountLabel = new QLabel(layoutWidget);
        amountLabel->setObjectName(QString::fromUtf8("amountLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, amountLabel);

        amountspinBox = new QSpinBox(layoutWidget);
        amountspinBox->setObjectName(QString::fromUtf8("amountspinBox"));
        amountspinBox->setEnabled(true);
        amountspinBox->setLayoutDirection(Qt::LeftToRight);
        amountspinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::FieldRole, amountspinBox);

        totalpriceLabel = new QLabel(layoutWidget);
        totalpriceLabel->setObjectName(QString::fromUtf8("totalpriceLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, totalpriceLabel);

        totalpriceLineEdit = new QLineEdit(layoutWidget);
        totalpriceLineEdit->setObjectName(QString::fromUtf8("totalpriceLineEdit"));
        totalpriceLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::FieldRole, totalpriceLineEdit);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        addpushButton = new QPushButton(layoutWidget);
        addpushButton->setObjectName(QString::fromUtf8("addpushButton"));

        horizontalLayout_3->addWidget(addpushButton);

        modifypushButton = new QPushButton(layoutWidget);
        modifypushButton->setObjectName(QString::fromUtf8("modifypushButton"));

        horizontalLayout_3->addWidget(modifypushButton);

        deletepushButton = new QPushButton(layoutWidget);
        deletepushButton->setObjectName(QString::fromUtf8("deletepushButton"));

        horizontalLayout_3->addWidget(deletepushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        splitter->addWidget(layoutWidget);
        ordertreeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QString::fromUtf8("OID"));
        ordertreeWidget->setHeaderItem(__qtreewidgetitem2);
        ordertreeWidget->setObjectName(QString::fromUtf8("ordertreeWidget"));
        ordertreeWidget->setEnabled(true);
        splitter->addWidget(ordertreeWidget);

        horizontalLayout_4->addWidget(splitter);

#if QT_CONFIG(shortcut)
        oidLabel->setBuddy(oidLineEdit);
        nameLabel->setBuddy(nameLineEdit);
        pnameLabel->setBuddy(pnameLineEdit);
        stockLabel->setBuddy(stockLineEdit);
        amountLabel->setBuddy(stockLineEdit);
        totalpriceLabel->setBuddy(stockLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(OrderManagerForm);

        QMetaObject::connectSlotsByName(OrderManagerForm);
    } // setupUi

    void retranslateUi(QWidget *OrderManagerForm)
    {
        OrderManagerForm->setWindowTitle(QCoreApplication::translate("OrderManagerForm", "Form", nullptr));
        clientcomboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "--Client Select--", nullptr));
        clientcomboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "CID", nullptr));
        clientcomboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "ClientName", nullptr));

        clientcomboBox->setCurrentText(QCoreApplication::translate("OrderManagerForm", "--Client Select--", nullptr));
        clientcomboBox->setPlaceholderText(QString());
        QTreeWidgetItem *___qtreewidgetitem = clienttreeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("OrderManagerForm", "Name", nullptr));
        productcomboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "--Product Select--", nullptr));
        productcomboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "PID", nullptr));
        productcomboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "ProductName", nullptr));

        productcomboBox->setCurrentText(QCoreApplication::translate("OrderManagerForm", "--Product Select--", nullptr));
        productcomboBox->setPlaceholderText(QString());
        QTreeWidgetItem *___qtreewidgetitem1 = producttreeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        oidLabel->setText(QCoreApplication::translate("OrderManagerForm", "OID", nullptr));
        nameLabel->setText(QCoreApplication::translate("OrderManagerForm", "&ClientName", nullptr));
        pnameLabel->setText(QCoreApplication::translate("OrderManagerForm", "&ProductName", nullptr));
        stockLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Stock", nullptr));
        amountLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Amount", nullptr));
        totalpriceLabel->setText(QCoreApplication::translate("OrderManagerForm", "&TotalPrice", nullptr));
        addpushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Add", nullptr));
        modifypushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Modify", nullptr));
        deletepushButton->setText(QCoreApplication::translate("OrderManagerForm", "&Delete", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ordertreeWidget->headerItem();
        ___qtreewidgetitem2->setText(5, QCoreApplication::translate("OrderManagerForm", "Date", nullptr));
        ___qtreewidgetitem2->setText(4, QCoreApplication::translate("OrderManagerForm", "TotalPrice", nullptr));
        ___qtreewidgetitem2->setText(3, QCoreApplication::translate("OrderManagerForm", "Amount", nullptr));
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("OrderManagerForm", "ProductName", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("OrderManagerForm", "ClientName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManagerForm: public Ui_OrderManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGERFORM_H
