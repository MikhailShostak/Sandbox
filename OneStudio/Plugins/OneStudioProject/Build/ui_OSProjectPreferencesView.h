/********************************************************************************
** Form generated from reading UI file 'OSProjectPreferencesView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSPROJECTPREFERENCESVIEW_H
#define UI_OSPROJECTPREFERENCESVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "OSTargetSettingsView.h"
#include "OSTaskView.h"

QT_BEGIN_NAMESPACE

class Ui_OSProjectPreferencesView
{
public:
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *targetsTab;
    QHBoxLayout *horizontalLayout;
    QWidget *targetsListContentView;
    QVBoxLayout *targetListContentViewLayout;
    QHBoxLayout *targetListButtonsLayout;
    QComboBox *addTargetComboBox;
    QPushButton *removeTargetButton;
    QListWidget *targetListView;
    QVBoxLayout *targetInfoLayout;
    QLabel *targetNameLabel;
    QTabWidget *targetTabView;
    QWidget *targetDependenciesView;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *targetDependenciesListLayout;
    QComboBox *addTargetDependenceComboBox;
    QPushButton *removeTargetDependenceButton;
    QListWidget *targetDependenciesListView;
    QWidget *targetBuildingStepsView;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *buildingGroupStepsLayout;
    QScrollArea *buildStepScrollView;
    QWidget *buildStepScrollContentView;
    QVBoxLayout *verticalLayout_10;
    OSTaskView *buildStepTaskView;
    QSpacerItem *buildStepBottomSpacer;
    QScrollArea *cleanStepScrollView;
    QWidget *cleanStepScrollContentView;
    QVBoxLayout *verticalLayout_9;
    OSTaskView *cleanStepTaskView;
    QSpacerItem *cleanStepBottomSpacer;
    QWidget *installingStepsTabView;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *installingGroupStepsLayout;
    QScrollArea *installStepScrollView;
    QWidget *installStepScrollContentView;
    QVBoxLayout *verticalLayout_11;
    OSTaskView *installStepTaskView;
    QSpacerItem *installStepBottomSpacer;
    QScrollArea *uninstallStepScrollView;
    QWidget *uninstallStepScrollContentView;
    QVBoxLayout *verticalLayout_14;
    OSTaskView *uninstallStepTaskView;
    QSpacerItem *uninstallStepBottomSpacer;
    QWidget *runningStepsTabView;
    QVBoxLayout *verticalLayout_16;
    QLabel *targetRunLabel;
    QFormLayout *targetRunFormLayout;
    QLabel *targetRunApplicationLabel;
    QLineEdit *targetRunApplicationField;
    QLabel *targetRunArgumentsLabel;
    QLineEdit *targetRunArgumentsField;
    QSpacerItem *verticalSpacer_2;
    QWidget *targetSettingsTabView;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *targetSettingsListView;
    QScrollArea *targetSettingsScrollView;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    OSTargetSettingsView *targetSettingsView;
    QSpacerItem *verticalSpacer;
    QWidget *settingsTab;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *projectSettingsListView;
    QScrollArea *projectSettingsScrollView;
    QWidget *projectSettingsContentView;
    QVBoxLayout *verticalLayout_7;
    OSTargetSettingsView *projectSettingsView;
    QSpacerItem *projectSettingsPlaceholder;

    void setupUi(QWidget *OSProjectPreferencesView)
    {
        if (OSProjectPreferencesView->objectName().isEmpty())
            OSProjectPreferencesView->setObjectName(QStringLiteral("OSProjectPreferencesView"));
        OSProjectPreferencesView->resize(913, 318);
        horizontalLayout_2 = new QHBoxLayout(OSProjectPreferencesView);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(OSProjectPreferencesView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 300));
        targetsTab = new QWidget();
        targetsTab->setObjectName(QStringLiteral("targetsTab"));
        horizontalLayout = new QHBoxLayout(targetsTab);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        targetsListContentView = new QWidget(targetsTab);
        targetsListContentView->setObjectName(QStringLiteral("targetsListContentView"));
        targetsListContentView->setMinimumSize(QSize(260, 0));
        targetsListContentView->setMaximumSize(QSize(260, 16777215));
        targetListContentViewLayout = new QVBoxLayout(targetsListContentView);
        targetListContentViewLayout->setObjectName(QStringLiteral("targetListContentViewLayout"));
        targetListContentViewLayout->setContentsMargins(0, 0, 0, 0);
        targetListButtonsLayout = new QHBoxLayout();
        targetListButtonsLayout->setObjectName(QStringLiteral("targetListButtonsLayout"));
        addTargetComboBox = new QComboBox(targetsListContentView);
        addTargetComboBox->setObjectName(QStringLiteral("addTargetComboBox"));
        addTargetComboBox->setFocusPolicy(Qt::StrongFocus);

        targetListButtonsLayout->addWidget(addTargetComboBox);

        removeTargetButton = new QPushButton(targetsListContentView);
        removeTargetButton->setObjectName(QStringLiteral("removeTargetButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(removeTargetButton->sizePolicy().hasHeightForWidth());
        removeTargetButton->setSizePolicy(sizePolicy);
        removeTargetButton->setMaximumSize(QSize(24, 24));
        QFont font;
        font.setFamily(QStringLiteral("FontAwesome"));
        font.setPointSize(13);
        removeTargetButton->setFont(font);
        removeTargetButton->setFlat(true);

        targetListButtonsLayout->addWidget(removeTargetButton);


        targetListContentViewLayout->addLayout(targetListButtonsLayout);

        targetListView = new QListWidget(targetsListContentView);
        targetListView->setObjectName(QStringLiteral("targetListView"));

        targetListContentViewLayout->addWidget(targetListView);


        horizontalLayout->addWidget(targetsListContentView);

        targetInfoLayout = new QVBoxLayout();
        targetInfoLayout->setObjectName(QStringLiteral("targetInfoLayout"));
        targetNameLabel = new QLabel(targetsTab);
        targetNameLabel->setObjectName(QStringLiteral("targetNameLabel"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        targetNameLabel->setFont(font1);

        targetInfoLayout->addWidget(targetNameLabel);

        targetTabView = new QTabWidget(targetsTab);
        targetTabView->setObjectName(QStringLiteral("targetTabView"));
        targetDependenciesView = new QWidget();
        targetDependenciesView->setObjectName(QStringLiteral("targetDependenciesView"));
        verticalLayout_6 = new QVBoxLayout(targetDependenciesView);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        targetDependenciesListLayout = new QHBoxLayout();
        targetDependenciesListLayout->setObjectName(QStringLiteral("targetDependenciesListLayout"));
        addTargetDependenceComboBox = new QComboBox(targetDependenciesView);
        addTargetDependenceComboBox->setObjectName(QStringLiteral("addTargetDependenceComboBox"));

        targetDependenciesListLayout->addWidget(addTargetDependenceComboBox);

        removeTargetDependenceButton = new QPushButton(targetDependenciesView);
        removeTargetDependenceButton->setObjectName(QStringLiteral("removeTargetDependenceButton"));
        removeTargetDependenceButton->setMaximumSize(QSize(24, 24));
        removeTargetDependenceButton->setFont(font);
        removeTargetDependenceButton->setFlat(true);

        targetDependenciesListLayout->addWidget(removeTargetDependenceButton);


        verticalLayout_6->addLayout(targetDependenciesListLayout);

        targetDependenciesListView = new QListWidget(targetDependenciesView);
        targetDependenciesListView->setObjectName(QStringLiteral("targetDependenciesListView"));

        verticalLayout_6->addWidget(targetDependenciesListView);

        targetTabView->addTab(targetDependenciesView, QString());
        targetBuildingStepsView = new QWidget();
        targetBuildingStepsView->setObjectName(QStringLiteral("targetBuildingStepsView"));
        verticalLayout_13 = new QVBoxLayout(targetBuildingStepsView);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        buildingGroupStepsLayout = new QHBoxLayout();
        buildingGroupStepsLayout->setSpacing(0);
        buildingGroupStepsLayout->setObjectName(QStringLiteral("buildingGroupStepsLayout"));
        buildStepScrollView = new QScrollArea(targetBuildingStepsView);
        buildStepScrollView->setObjectName(QStringLiteral("buildStepScrollView"));
        buildStepScrollView->setFrameShape(QFrame::NoFrame);
        buildStepScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        buildStepScrollView->setWidgetResizable(true);
        buildStepScrollContentView = new QWidget();
        buildStepScrollContentView->setObjectName(QStringLiteral("buildStepScrollContentView"));
        buildStepScrollContentView->setGeometry(QRect(0, 0, 286, 199));
        verticalLayout_10 = new QVBoxLayout(buildStepScrollContentView);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        buildStepTaskView = new OSTaskView(buildStepScrollContentView);
        buildStepTaskView->setObjectName(QStringLiteral("buildStepTaskView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buildStepTaskView->sizePolicy().hasHeightForWidth());
        buildStepTaskView->setSizePolicy(sizePolicy1);

        verticalLayout_10->addWidget(buildStepTaskView);

        buildStepBottomSpacer = new QSpacerItem(20, 243, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(buildStepBottomSpacer);

        buildStepScrollView->setWidget(buildStepScrollContentView);

        buildingGroupStepsLayout->addWidget(buildStepScrollView);

        cleanStepScrollView = new QScrollArea(targetBuildingStepsView);
        cleanStepScrollView->setObjectName(QStringLiteral("cleanStepScrollView"));
        cleanStepScrollView->setFrameShape(QFrame::NoFrame);
        cleanStepScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cleanStepScrollView->setWidgetResizable(true);
        cleanStepScrollContentView = new QWidget();
        cleanStepScrollContentView->setObjectName(QStringLiteral("cleanStepScrollContentView"));
        cleanStepScrollContentView->setGeometry(QRect(0, 0, 285, 199));
        verticalLayout_9 = new QVBoxLayout(cleanStepScrollContentView);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        cleanStepTaskView = new OSTaskView(cleanStepScrollContentView);
        cleanStepTaskView->setObjectName(QStringLiteral("cleanStepTaskView"));
        sizePolicy1.setHeightForWidth(cleanStepTaskView->sizePolicy().hasHeightForWidth());
        cleanStepTaskView->setSizePolicy(sizePolicy1);

        verticalLayout_9->addWidget(cleanStepTaskView);

        cleanStepBottomSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(cleanStepBottomSpacer);

        cleanStepScrollView->setWidget(cleanStepScrollContentView);

        buildingGroupStepsLayout->addWidget(cleanStepScrollView);


        verticalLayout_13->addLayout(buildingGroupStepsLayout);

        targetTabView->addTab(targetBuildingStepsView, QString());
        installingStepsTabView = new QWidget();
        installingStepsTabView->setObjectName(QStringLiteral("installingStepsTabView"));
        verticalLayout_12 = new QVBoxLayout(installingStepsTabView);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        installingGroupStepsLayout = new QHBoxLayout();
        installingGroupStepsLayout->setSpacing(0);
        installingGroupStepsLayout->setObjectName(QStringLiteral("installingGroupStepsLayout"));
        installStepScrollView = new QScrollArea(installingStepsTabView);
        installStepScrollView->setObjectName(QStringLiteral("installStepScrollView"));
        installStepScrollView->setFrameShape(QFrame::NoFrame);
        installStepScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        installStepScrollView->setWidgetResizable(true);
        installStepScrollContentView = new QWidget();
        installStepScrollContentView->setObjectName(QStringLiteral("installStepScrollContentView"));
        installStepScrollContentView->setGeometry(QRect(0, 0, 286, 199));
        verticalLayout_11 = new QVBoxLayout(installStepScrollContentView);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        installStepTaskView = new OSTaskView(installStepScrollContentView);
        installStepTaskView->setObjectName(QStringLiteral("installStepTaskView"));
        sizePolicy1.setHeightForWidth(installStepTaskView->sizePolicy().hasHeightForWidth());
        installStepTaskView->setSizePolicy(sizePolicy1);

        verticalLayout_11->addWidget(installStepTaskView);

        installStepBottomSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(installStepBottomSpacer);

        installStepScrollView->setWidget(installStepScrollContentView);

        installingGroupStepsLayout->addWidget(installStepScrollView);

        uninstallStepScrollView = new QScrollArea(installingStepsTabView);
        uninstallStepScrollView->setObjectName(QStringLiteral("uninstallStepScrollView"));
        uninstallStepScrollView->setFrameShape(QFrame::NoFrame);
        uninstallStepScrollView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        uninstallStepScrollView->setWidgetResizable(true);
        uninstallStepScrollContentView = new QWidget();
        uninstallStepScrollContentView->setObjectName(QStringLiteral("uninstallStepScrollContentView"));
        uninstallStepScrollContentView->setGeometry(QRect(0, 0, 285, 199));
        verticalLayout_14 = new QVBoxLayout(uninstallStepScrollContentView);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        uninstallStepTaskView = new OSTaskView(uninstallStepScrollContentView);
        uninstallStepTaskView->setObjectName(QStringLiteral("uninstallStepTaskView"));
        sizePolicy1.setHeightForWidth(uninstallStepTaskView->sizePolicy().hasHeightForWidth());
        uninstallStepTaskView->setSizePolicy(sizePolicy1);

        verticalLayout_14->addWidget(uninstallStepTaskView);

        uninstallStepBottomSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(uninstallStepBottomSpacer);

        uninstallStepScrollView->setWidget(uninstallStepScrollContentView);

        installingGroupStepsLayout->addWidget(uninstallStepScrollView);


        verticalLayout_12->addLayout(installingGroupStepsLayout);

        targetTabView->addTab(installingStepsTabView, QString());
        runningStepsTabView = new QWidget();
        runningStepsTabView->setObjectName(QStringLiteral("runningStepsTabView"));
        verticalLayout_16 = new QVBoxLayout(runningStepsTabView);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        targetRunLabel = new QLabel(runningStepsTabView);
        targetRunLabel->setObjectName(QStringLiteral("targetRunLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(targetRunLabel->sizePolicy().hasHeightForWidth());
        targetRunLabel->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        targetRunLabel->setFont(font2);

        verticalLayout_16->addWidget(targetRunLabel);

        targetRunFormLayout = new QFormLayout();
        targetRunFormLayout->setObjectName(QStringLiteral("targetRunFormLayout"));
        targetRunFormLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        targetRunApplicationLabel = new QLabel(runningStepsTabView);
        targetRunApplicationLabel->setObjectName(QStringLiteral("targetRunApplicationLabel"));

        targetRunFormLayout->setWidget(0, QFormLayout::LabelRole, targetRunApplicationLabel);

        targetRunApplicationField = new QLineEdit(runningStepsTabView);
        targetRunApplicationField->setObjectName(QStringLiteral("targetRunApplicationField"));

        targetRunFormLayout->setWidget(0, QFormLayout::FieldRole, targetRunApplicationField);

        targetRunArgumentsLabel = new QLabel(runningStepsTabView);
        targetRunArgumentsLabel->setObjectName(QStringLiteral("targetRunArgumentsLabel"));

        targetRunFormLayout->setWidget(1, QFormLayout::LabelRole, targetRunArgumentsLabel);

        targetRunArgumentsField = new QLineEdit(runningStepsTabView);
        targetRunArgumentsField->setObjectName(QStringLiteral("targetRunArgumentsField"));

        targetRunFormLayout->setWidget(1, QFormLayout::FieldRole, targetRunArgumentsField);


        verticalLayout_16->addLayout(targetRunFormLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_2);

        targetTabView->addTab(runningStepsTabView, QString());
        targetSettingsTabView = new QWidget();
        targetSettingsTabView->setObjectName(QStringLiteral("targetSettingsTabView"));
        horizontalLayout_3 = new QHBoxLayout(targetSettingsTabView);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        targetSettingsListView = new QListWidget(targetSettingsTabView);
        targetSettingsListView->setObjectName(QStringLiteral("targetSettingsListView"));
        targetSettingsListView->setMaximumSize(QSize(260, 16777215));
        targetSettingsListView->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(targetSettingsListView);

        targetSettingsScrollView = new QScrollArea(targetSettingsTabView);
        targetSettingsScrollView->setObjectName(QStringLiteral("targetSettingsScrollView"));
        targetSettingsScrollView->setFrameShape(QFrame::NoFrame);
        targetSettingsScrollView->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 335, 201));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        targetSettingsView = new OSTargetSettingsView(scrollAreaWidgetContents);
        targetSettingsView->setObjectName(QStringLiteral("targetSettingsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(targetSettingsView->sizePolicy().hasHeightForWidth());
        targetSettingsView->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(targetSettingsView);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        targetSettingsScrollView->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(targetSettingsScrollView);

        targetTabView->addTab(targetSettingsTabView, QString());

        targetInfoLayout->addWidget(targetTabView);


        horizontalLayout->addLayout(targetInfoLayout);

        tabWidget->addTab(targetsTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        horizontalLayout_4 = new QHBoxLayout(settingsTab);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        projectSettingsListView = new QListWidget(settingsTab);
        projectSettingsListView->setObjectName(QStringLiteral("projectSettingsListView"));
        projectSettingsListView->setMaximumSize(QSize(260, 16777215));
        projectSettingsListView->setFrameShape(QFrame::NoFrame);

        horizontalLayout_4->addWidget(projectSettingsListView);

        projectSettingsScrollView = new QScrollArea(settingsTab);
        projectSettingsScrollView->setObjectName(QStringLiteral("projectSettingsScrollView"));
        projectSettingsScrollView->setFrameShape(QFrame::NoFrame);
        projectSettingsScrollView->setWidgetResizable(true);
        projectSettingsContentView = new QWidget();
        projectSettingsContentView->setObjectName(QStringLiteral("projectSettingsContentView"));
        projectSettingsContentView->setGeometry(QRect(0, 0, 631, 273));
        verticalLayout_7 = new QVBoxLayout(projectSettingsContentView);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        projectSettingsView = new OSTargetSettingsView(projectSettingsContentView);
        projectSettingsView->setObjectName(QStringLiteral("projectSettingsView"));
        sizePolicy3.setHeightForWidth(projectSettingsView->sizePolicy().hasHeightForWidth());
        projectSettingsView->setSizePolicy(sizePolicy3);

        verticalLayout_7->addWidget(projectSettingsView);

        projectSettingsPlaceholder = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(projectSettingsPlaceholder);

        projectSettingsScrollView->setWidget(projectSettingsContentView);

        horizontalLayout_4->addWidget(projectSettingsScrollView);

        tabWidget->addTab(settingsTab, QString());

        horizontalLayout_2->addWidget(tabWidget);


        retranslateUi(OSProjectPreferencesView);
        QObject::connect(targetListView, SIGNAL(currentRowChanged(int)), OSProjectPreferencesView, SLOT(selectTarget(int)));
        QObject::connect(addTargetComboBox, SIGNAL(currentIndexChanged(int)), OSProjectPreferencesView, SLOT(addTarget(int)));
        QObject::connect(removeTargetButton, SIGNAL(clicked()), OSProjectPreferencesView, SLOT(removeTarget()));
        QObject::connect(projectSettingsListView, SIGNAL(currentRowChanged(int)), OSProjectPreferencesView, SLOT(selectProjectSettings(int)));
        QObject::connect(targetSettingsListView, SIGNAL(currentRowChanged(int)), OSProjectPreferencesView, SLOT(selectTargetSettings(int)));

        tabWidget->setCurrentIndex(0);
        targetTabView->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(OSProjectPreferencesView);
    } // setupUi

    void retranslateUi(QWidget *OSProjectPreferencesView)
    {
        OSProjectPreferencesView->setWindowTitle(QApplication::translate("OSProjectPreferencesView", "Form", Q_NULLPTR));
        addTargetComboBox->clear();
        addTargetComboBox->insertItems(0, QStringList()
         << QApplication::translate("OSProjectPreferencesView", "Create target", Q_NULLPTR)
        );
        removeTargetButton->setText(QApplication::translate("OSProjectPreferencesView", "\357\200\224", Q_NULLPTR));
        targetNameLabel->setText(QApplication::translate("OSProjectPreferencesView", "Target", Q_NULLPTR));
        removeTargetDependenceButton->setText(QApplication::translate("OSProjectPreferencesView", "\357\200\224", Q_NULLPTR));
        targetTabView->setTabText(targetTabView->indexOf(targetDependenciesView), QApplication::translate("OSProjectPreferencesView", "Dependencies", Q_NULLPTR));
        targetTabView->setTabText(targetTabView->indexOf(targetBuildingStepsView), QApplication::translate("OSProjectPreferencesView", "Building Steps", Q_NULLPTR));
        targetTabView->setTabText(targetTabView->indexOf(installingStepsTabView), QApplication::translate("OSProjectPreferencesView", "Installing Steps", Q_NULLPTR));
        targetRunLabel->setText(QApplication::translate("OSProjectPreferencesView", "Run", Q_NULLPTR));
        targetRunApplicationLabel->setText(QApplication::translate("OSProjectPreferencesView", "Application", Q_NULLPTR));
        targetRunArgumentsLabel->setText(QApplication::translate("OSProjectPreferencesView", "Arguments", Q_NULLPTR));
        targetTabView->setTabText(targetTabView->indexOf(runningStepsTabView), QApplication::translate("OSProjectPreferencesView", "Running Step", Q_NULLPTR));
        targetTabView->setTabText(targetTabView->indexOf(targetSettingsTabView), QApplication::translate("OSProjectPreferencesView", "Settings", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(targetsTab), QApplication::translate("OSProjectPreferencesView", "Targets", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("OSProjectPreferencesView", "Settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OSProjectPreferencesView: public Ui_OSProjectPreferencesView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSPROJECTPREFERENCESVIEW_H
