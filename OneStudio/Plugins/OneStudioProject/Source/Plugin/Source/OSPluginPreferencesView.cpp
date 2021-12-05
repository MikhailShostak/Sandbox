#include "OSPluginPreferencesView.h"
//#include "ui_OSPluginPreferencesView.h"

#include "Main.h"

OSPluginPreferencesView::OSPluginPreferencesView()// :
    //QWidget(parent),
    //ui(new Ui::OSPluginPreferencesView)
{
    /*ui->setupUi(this);
    connect(ui->listView, &QListWidget::currentTextChanged, [this](const QString &text) {
        ui->settingsView->setData(ProjectContext->getSettings().at(text.toUtf8().data()));
    });*/
}

OSPluginPreferencesView::~OSPluginPreferencesView()
{
    //delete ui;
}

void OSPluginPreferencesView::accept()
{
    /*for(auto &pair : ProjectContext->getSettings())
    {
        pair.second->getFileData()->save();
    }
    close();*/
}

/*void OSPluginPreferencesView::showEvent(QShowEvent *event)
{
    for(auto &pair : ProjectContext->getSettings())
    {
        ui->listView->addItem(pair.first.toUtf8().data());
    }
    ui->listView->setCurrentRow(0);
}*/
