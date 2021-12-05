/********************************************************************************
** Form generated from reading UI file 'OSPluginPreferencesView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSPLUGINPREFERENCESVIEW_H
#define UI_OSPLUGINPREFERENCESVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "OSTargetSettingsView.h"

QT_BEGIN_NAMESPACE

class Ui_OSPluginPreferencesView
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    OSTargetSettingsView *settingsView;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QPushButton *rejectButton;

    void setupUi(QWidget *OSPluginPreferencesView)
    {
        if (OSPluginPreferencesView->objectName().isEmpty())
            OSPluginPreferencesView->setObjectName(QStringLiteral("OSPluginPreferencesView"));
        OSPluginPreferencesView->resize(763, 300);
        horizontalLayout = new QHBoxLayout(OSPluginPreferencesView);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListWidget(OSPluginPreferencesView);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMaximumSize(QSize(260, 16777215));
        listView->setFrameShape(QFrame::NoFrame);

        horizontalLayout->addWidget(listView);

        widget = new QWidget(OSPluginPreferencesView);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        settingsView = new OSTargetSettingsView(widget);
        settingsView->setObjectName(QStringLiteral("settingsView"));

        verticalLayout->addWidget(settingsView);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        acceptButton = new QPushButton(widget);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));

        horizontalLayout_2->addWidget(acceptButton);

        rejectButton = new QPushButton(widget);
        rejectButton->setObjectName(QStringLiteral("rejectButton"));

        horizontalLayout_2->addWidget(rejectButton);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(OSPluginPreferencesView);
        QObject::connect(rejectButton, SIGNAL(clicked()), OSPluginPreferencesView, SLOT(close()));
        QObject::connect(acceptButton, SIGNAL(clicked()), OSPluginPreferencesView, SLOT(accept()));

        QMetaObject::connectSlotsByName(OSPluginPreferencesView);
    } // setupUi

    void retranslateUi(QWidget *OSPluginPreferencesView)
    {
        OSPluginPreferencesView->setWindowTitle(QApplication::translate("OSPluginPreferencesView", "Project Plugin Preferences", Q_NULLPTR));
        acceptButton->setText(QApplication::translate("OSPluginPreferencesView", "Ok", Q_NULLPTR));
        rejectButton->setText(QApplication::translate("OSPluginPreferencesView", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSPluginPreferencesView: public Ui_OSPluginPreferencesView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSPLUGINPREFERENCESVIEW_H
