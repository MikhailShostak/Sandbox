/********************************************************************************
** Form generated from reading UI file 'OSProjectToolBarView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSPROJECTTOOLBARVIEW_H
#define UI_OSPROJECTTOOLBARVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSProjectToolBarView
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *projectsComboBox;
    QComboBox *targetsComboBox;

    void setupUi(QWidget *OSProjectToolBarView)
    {
        if (OSProjectToolBarView->objectName().isEmpty())
            OSProjectToolBarView->setObjectName(QStringLiteral("OSProjectToolBarView"));
        OSProjectToolBarView->resize(401, 20);
        horizontalLayout = new QHBoxLayout(OSProjectToolBarView);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        projectsComboBox = new QComboBox(OSProjectToolBarView);
        projectsComboBox->setObjectName(QStringLiteral("projectsComboBox"));
        projectsComboBox->setMinimumSize(QSize(200, 20));

        horizontalLayout->addWidget(projectsComboBox);

        targetsComboBox = new QComboBox(OSProjectToolBarView);
        targetsComboBox->setObjectName(QStringLiteral("targetsComboBox"));
        targetsComboBox->setMinimumSize(QSize(200, 20));

        horizontalLayout->addWidget(targetsComboBox);


        retranslateUi(OSProjectToolBarView);

        QMetaObject::connectSlotsByName(OSProjectToolBarView);
    } // setupUi

    void retranslateUi(QWidget *OSProjectToolBarView)
    {
        Q_UNUSED(OSProjectToolBarView);
    } // retranslateUi

};

namespace Ui {
    class OSProjectToolBarView: public Ui_OSProjectToolBarView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSPROJECTTOOLBARVIEW_H
