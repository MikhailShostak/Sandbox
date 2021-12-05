/********************************************************************************
** Form generated from reading UI file 'OSDefinitionsView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSDEFINITIONSVIEW_H
#define UI_OSDEFINITIONSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSDefinitionsView
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeView;

    void setupUi(QWidget *OSDefinitionsView)
    {
        if (OSDefinitionsView->objectName().isEmpty())
            OSDefinitionsView->setObjectName(QStringLiteral("OSDefinitionsView"));
        OSDefinitionsView->resize(400, 300);
        verticalLayout = new QVBoxLayout(OSDefinitionsView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeWidget(OSDefinitionsView);
        treeView->headerItem()->setText(0, QString());
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->header()->setVisible(false);

        verticalLayout->addWidget(treeView);


        retranslateUi(OSDefinitionsView);

        QMetaObject::connectSlotsByName(OSDefinitionsView);
    } // setupUi

    void retranslateUi(QWidget *OSDefinitionsView)
    {
        OSDefinitionsView->setWindowTitle(QApplication::translate("OSDefinitionsView", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSDefinitionsView: public Ui_OSDefinitionsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSDEFINITIONSVIEW_H
