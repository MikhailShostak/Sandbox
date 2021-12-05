/********************************************************************************
** Form generated from reading UI file 'OSTargetSettingsView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSTARGETSETTINGSVIEW_H
#define UI_OSTARGETSETTINGSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSTargetSettingsView
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *OSTargetSettingsView)
    {
        if (OSTargetSettingsView->objectName().isEmpty())
            OSTargetSettingsView->setObjectName(QStringLiteral("OSTargetSettingsView"));
        OSTargetSettingsView->resize(400, 300);
        verticalLayout = new QVBoxLayout(OSTargetSettingsView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(OSTargetSettingsView);

        QMetaObject::connectSlotsByName(OSTargetSettingsView);
    } // setupUi

    void retranslateUi(QWidget *OSTargetSettingsView)
    {
        OSTargetSettingsView->setWindowTitle(QApplication::translate("OSTargetSettingsView", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSTargetSettingsView: public Ui_OSTargetSettingsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSTARGETSETTINGSVIEW_H
