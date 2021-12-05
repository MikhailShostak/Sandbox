/********************************************************************************
** Form generated from reading UI file 'OSTargetView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSTARGETVIEW_H
#define UI_OSTARGETVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSTargetView
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *targetsComboBox;

    void setupUi(QWidget *OSTargetView)
    {
        if (OSTargetView->objectName().isEmpty())
            OSTargetView->setObjectName(QStringLiteral("OSTargetView"));
        OSTargetView->resize(202, 20);
        horizontalLayout = new QHBoxLayout(OSTargetView);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        targetsComboBox = new QComboBox(OSTargetView);
        targetsComboBox->setObjectName(QStringLiteral("targetsComboBox"));
        targetsComboBox->setMinimumSize(QSize(200, 20));

        horizontalLayout->addWidget(targetsComboBox);


        retranslateUi(OSTargetView);

        QMetaObject::connectSlotsByName(OSTargetView);
    } // setupUi

    void retranslateUi(QWidget *OSTargetView)
    {
        Q_UNUSED(OSTargetView);
    } // retranslateUi

};

namespace Ui {
    class OSTargetView: public Ui_OSTargetView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSTARGETVIEW_H
