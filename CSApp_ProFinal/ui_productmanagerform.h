/********************************************************************************
** Form generated from reading UI file 'productmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTMANAGERFORM_H
#define UI_PRODUCTMANAGERFORM_H

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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductManagerForm
{
public:
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *inputPage;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QFormLayout *clientFormLayout;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *pnameLabel;
    QLineEdit *pnameLineEdit;
    QLabel *priceLabel;
    QLineEdit *priceLineEdit;
    QLabel *stockLabel;
    QLineEdit *stockLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QPushButton *deletePushButton;
    QWidget *searchPage;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *searchTreeWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;
    QTreeWidget *producttreeWidget;

    void setupUi(QWidget *ProductManagerForm)
    {
        if (ProductManagerForm->objectName().isEmpty())
            ProductManagerForm->setObjectName(QString::fromUtf8("ProductManagerForm"));
        ProductManagerForm->resize(571, 426);
        horizontalLayout_4 = new QHBoxLayout(ProductManagerForm);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter = new QSplitter(ProductManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 284, 366));
        horizontalLayout_3 = new QHBoxLayout(inputPage);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        clientFormLayout = new QFormLayout();
        clientFormLayout->setObjectName(QString::fromUtf8("clientFormLayout"));
        idLabel = new QLabel(inputPage);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        clientFormLayout->setWidget(0, QFormLayout::LabelRole, idLabel);

        idLineEdit = new QLineEdit(inputPage);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setReadOnly(true);

        clientFormLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        pnameLabel = new QLabel(inputPage);
        pnameLabel->setObjectName(QString::fromUtf8("pnameLabel"));

        clientFormLayout->setWidget(1, QFormLayout::LabelRole, pnameLabel);

        pnameLineEdit = new QLineEdit(inputPage);
        pnameLineEdit->setObjectName(QString::fromUtf8("pnameLineEdit"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, pnameLineEdit);

        priceLabel = new QLabel(inputPage);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, priceLabel);

        priceLineEdit = new QLineEdit(inputPage);
        priceLineEdit->setObjectName(QString::fromUtf8("priceLineEdit"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, priceLineEdit);

        stockLabel = new QLabel(inputPage);
        stockLabel->setObjectName(QString::fromUtf8("stockLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, stockLabel);

        stockLineEdit = new QLineEdit(inputPage);
        stockLineEdit->setObjectName(QString::fromUtf8("stockLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, stockLineEdit);


        verticalLayout->addLayout(clientFormLayout);

        verticalSpacer = new QSpacerItem(14, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addPushButton = new QPushButton(inputPage);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        horizontalLayout_2->addWidget(addPushButton);

        modifyPushButton = new QPushButton(inputPage);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        horizontalLayout_2->addWidget(modifyPushButton);

        deletePushButton = new QPushButton(inputPage);
        deletePushButton->setObjectName(QString::fromUtf8("deletePushButton"));

        horizontalLayout_2->addWidget(deletePushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        toolBox->addItem(inputPage, QString::fromUtf8("&Input"));
        searchPage = new QWidget();
        searchPage->setObjectName(QString::fromUtf8("searchPage"));
        searchPage->setGeometry(QRect(0, 0, 284, 366));
        verticalLayout_3 = new QVBoxLayout(searchPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        searchTreeWidget = new QTreeWidget(searchPage);
        searchTreeWidget->setObjectName(QString::fromUtf8("searchTreeWidget"));
        searchTreeWidget->setRootIsDecorated(false);

        verticalLayout_3->addWidget(searchTreeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        horizontalLayout->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(searchPage);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        horizontalLayout->addWidget(searchLineEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        searchPushButton = new QPushButton(searchPage);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        verticalLayout_3->addWidget(searchPushButton);

        toolBox->addItem(searchPage, QString::fromUtf8("&Search"));
        splitter->addWidget(toolBox);
        producttreeWidget = new QTreeWidget(splitter);
        producttreeWidget->setObjectName(QString::fromUtf8("producttreeWidget"));
        producttreeWidget->setRootIsDecorated(false);
        splitter->addWidget(producttreeWidget);

        horizontalLayout_4->addWidget(splitter);

#if QT_CONFIG(shortcut)
        idLabel->setBuddy(idLineEdit);
        pnameLabel->setBuddy(pnameLineEdit);
        priceLabel->setBuddy(priceLineEdit);
        stockLabel->setBuddy(stockLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ProductManagerForm);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ProductManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ProductManagerForm)
    {
        ProductManagerForm->setWindowTitle(QCoreApplication::translate("ProductManagerForm", "Client Info", nullptr));
        idLabel->setText(QCoreApplication::translate("ProductManagerForm", "&PID", nullptr));
        pnameLabel->setText(QCoreApplication::translate("ProductManagerForm", "&ProductName", nullptr));
        priceLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Price", nullptr));
        stockLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Stock", nullptr));
        addPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Modify", nullptr));
        deletePushButton->setText(QCoreApplication::translate("ProductManagerForm", "&Delete", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("ProductManagerForm", "&Input", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = searchTreeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ProductManagerForm", "ProductName", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ProductManagerForm", "PID", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ProductManagerForm", "PID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ProductManagerForm", "ProductName", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ProductManagerForm", "S&earch", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("ProductManagerForm", "&Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = producttreeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("ProductManagerForm", "ProductName", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("ProductManagerForm", "PID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductManagerForm: public Ui_ProductManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTMANAGERFORM_H
