#include "OSTargetView.h"
//#include "ui_OSTargetView.h"

OSTargetView::OSTargetView(/*QWidget *parent*/)/* :
    QWidget(parent),
    ui(new Ui::OSTargetView)*/
{
    /*ui->setupUi(this);
    connect(ui->targetsComboBox, (void(QComboBox::*)(int))&QComboBox::currentIndexChanged, [this](int index){
        currentTargetInfo = targetInfos[index];
    });*/
}

OSTargetView::~OSTargetView()
{
    //delete ui;
}

void OSTargetView::update()
{
    /*ui->targetsComboBox->clear();
    for(auto targetInfo : targetInfos)
    {
        ui->targetsComboBox->addItem(targetInfo->getName().toUtf8().data());
    }
    if(targetInfos)
    {
        currentTargetInfo = targetInfos.first();
    }*/
}
