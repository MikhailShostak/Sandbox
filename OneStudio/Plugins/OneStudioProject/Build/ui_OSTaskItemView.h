/********************************************************************************
** Form generated from reading UI file 'OSTaskItemView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSTASKITEMVIEW_H
#define UI_OSTASKITEMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSTaskItemView
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *titleLayout;
    QLineEdit *descriptionFieldView;
    QLabel *packageLabel;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *removeButton;
    QPushButton *contentButton;
    QWidget *content;
    QFormLayout *formLayout;

    void setupUi(QWidget *OSTaskItemView)
    {
        if (OSTaskItemView->objectName().isEmpty())
            OSTaskItemView->setObjectName(QStringLiteral("OSTaskItemView"));
        OSTaskItemView->resize(460, 55);
        verticalLayout = new QVBoxLayout(OSTaskItemView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLayout = new QHBoxLayout();
        titleLayout->setObjectName(QStringLiteral("titleLayout"));
        descriptionFieldView = new QLineEdit(OSTaskItemView);
        descriptionFieldView->setObjectName(QStringLiteral("descriptionFieldView"));
        descriptionFieldView->setMinimumSize(QSize(200, 0));
        descriptionFieldView->setFrame(false);

        titleLayout->addWidget(descriptionFieldView);

        packageLabel = new QLabel(OSTaskItemView);
        packageLabel->setObjectName(QStringLiteral("packageLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(packageLabel->sizePolicy().hasHeightForWidth());
        packageLabel->setSizePolicy(sizePolicy);

        titleLayout->addWidget(packageLabel);

        upButton = new QPushButton(OSTaskItemView);
        upButton->setObjectName(QStringLiteral("upButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(upButton->sizePolicy().hasHeightForWidth());
        upButton->setSizePolicy(sizePolicy1);
        upButton->setMaximumSize(QSize(24, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("FontAwesome"));
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        upButton->setFont(font);
        upButton->setFlat(true);

        titleLayout->addWidget(upButton);

        downButton = new QPushButton(OSTaskItemView);
        downButton->setObjectName(QStringLiteral("downButton"));
        sizePolicy1.setHeightForWidth(downButton->sizePolicy().hasHeightForWidth());
        downButton->setSizePolicy(sizePolicy1);
        downButton->setMaximumSize(QSize(24, 16777215));
        downButton->setFont(font);
        downButton->setFlat(true);

        titleLayout->addWidget(downButton);

        removeButton = new QPushButton(OSTaskItemView);
        removeButton->setObjectName(QStringLiteral("removeButton"));
        sizePolicy1.setHeightForWidth(removeButton->sizePolicy().hasHeightForWidth());
        removeButton->setSizePolicy(sizePolicy1);
        removeButton->setMaximumSize(QSize(24, 16777215));
        removeButton->setFont(font);
        removeButton->setFlat(true);

        titleLayout->addWidget(removeButton);

        contentButton = new QPushButton(OSTaskItemView);
        contentButton->setObjectName(QStringLiteral("contentButton"));
        sizePolicy1.setHeightForWidth(contentButton->sizePolicy().hasHeightForWidth());
        contentButton->setSizePolicy(sizePolicy1);
        contentButton->setMinimumSize(QSize(80, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("FontAwesome"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        contentButton->setFont(font1);

        titleLayout->addWidget(contentButton);


        verticalLayout->addLayout(titleLayout);

        content = new QWidget(OSTaskItemView);
        content->setObjectName(QStringLiteral("content"));
        formLayout = new QFormLayout(content);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

        verticalLayout->addWidget(content);


        retranslateUi(OSTaskItemView);
        QObject::connect(contentButton, SIGNAL(clicked()), OSTaskItemView, SLOT(changeContentVisibility()));

        QMetaObject::connectSlotsByName(OSTaskItemView);
    } // setupUi

    void retranslateUi(QWidget *OSTaskItemView)
    {
        descriptionFieldView->setPlaceholderText(QApplication::translate("OSTaskItemView", "Description", Q_NULLPTR));
        packageLabel->setText(QApplication::translate("OSTaskItemView", "(Package Label)", Q_NULLPTR));
        upButton->setText(QApplication::translate("OSTaskItemView", "\357\201\242", Q_NULLPTR));
        downButton->setText(QApplication::translate("OSTaskItemView", "\357\201\243", Q_NULLPTR));
        removeButton->setText(QApplication::translate("OSTaskItemView", "\357\200\224", Q_NULLPTR));
        contentButton->setText(QApplication::translate("OSTaskItemView", "\357\204\207", Q_NULLPTR));
        Q_UNUSED(OSTaskItemView);
    } // retranslateUi

};

namespace Ui {
    class OSTaskItemView: public Ui_OSTaskItemView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSTASKITEMVIEW_H
