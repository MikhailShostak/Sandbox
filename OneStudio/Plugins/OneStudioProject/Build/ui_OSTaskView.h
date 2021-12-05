/********************************************************************************
** Form generated from reading UI file 'OSTaskView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSTASKVIEW_H
#define UI_OSTASKVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSTaskView
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QComboBox *addTaskComboBox;

    void setupUi(QWidget *OSTaskView)
    {
        if (OSTaskView->objectName().isEmpty())
            OSTaskView->setObjectName(QStringLiteral("OSTaskView"));
        OSTaskView->resize(72, 44);
        verticalLayout = new QVBoxLayout(OSTaskView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(OSTaskView);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);

        verticalLayout->addWidget(titleLabel);

        addTaskComboBox = new QComboBox(OSTaskView);
        addTaskComboBox->setObjectName(QStringLiteral("addTaskComboBox"));

        verticalLayout->addWidget(addTaskComboBox);


        retranslateUi(OSTaskView);
        QObject::connect(addTaskComboBox, SIGNAL(currentIndexChanged(int)), OSTaskView, SLOT(addTask(int)));

        QMetaObject::connectSlotsByName(OSTaskView);
    } // setupUi

    void retranslateUi(QWidget *OSTaskView)
    {
        OSTaskView->setWindowTitle(QApplication::translate("OSTaskView", "Form", Q_NULLPTR));
        titleLabel->setText(QApplication::translate("OSTaskView", "Task", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSTaskView: public Ui_OSTaskView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSTASKVIEW_H
