#include "OSTargetSettingsView.h"

OSTargetSettingsView::OSTargetSettingsView()/* :
    QWidget(parent),
    ui(new Ui::OSTargetSettingsView)*/
{
    //ui->setupUi(this);
}

OSTargetSettingsView::~OSTargetSettingsView()
{
    //delete ui;
}

/*class QResizableTableWidget : public QTableWidget
{
public:

    QResizableTableWidget()
    {
        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    }

    QSize sizeHint() const
    {
        QSize size = QTableWidget::sizeHint();
        size.setHeight(verticalHeader()->defaultSectionSize() * rowCount() + 2);
        return size;
    }

};*/

void OSTargetSettingsView::updateData()
{
   /* widgets.clear();

    if(!data)
    {
        return;
    }

    QLayout *layout = this->layout();

    auto groupsCount = data->getGroupsCount();
    widgets.reserve(groupsCount * 8);
    for(auto i = 0; i < groupsCount; ++i)
    {
        auto groupName = data->getGroupTitle(i);
        QLabel *label = createNew<QLabel>(groupName.toUtf8().data());
        QTableWidget *groupView = createNew<QResizableTableWidget>();

        groupView->setColumnCount(2);
        groupView->verticalHeader()->setVisible(false);
        groupView->verticalHeader()->setDefaultSectionSize(20);
        groupView->horizontalHeader()->setVisible(false);
        groupView->horizontalHeader()->setStretchLastSection(true);

        auto propertiesCount = data->getRowsCount(i);
        for(auto j = 0; j < propertiesCount; ++j)
        {
            auto propertyName = data->getItem(i, j, 0);
            auto propertyValue = data->getItem(i, j, 1);
            auto propertyValuePlaceholder = data->getItemPlaceholder(i, j, 1);
            auto nextRowIndex = groupView->rowCount();
            groupView->insertRow(nextRowIndex);
            QTableWidgetItem *item = createNew<QTableWidgetItem>(propertyName.toUtf8().data());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            groupView->setItem(nextRowIndex, 0, item);
            QLineEdit *valueWidget = new QLineEdit(propertyValue.toUtf8().data(), groupView);
            valueWidget->setFrame(false);
            valueWidget->setPlaceholderText(propertyValuePlaceholder.toUtf8().data());
            connect(valueWidget, &QLineEdit::textEdited, [this, i, j](const QString &text){
                data->onItemChange(i, j, 1, text.toUtf8().data());
            });
            groupView->setCellWidget(nextRowIndex, 1, valueWidget);
            widgets.append(valueWidget);
        }

        layout->addWidget(label);
        layout->addWidget(groupView);
        widgets.append(label);
        widgets.append(groupView);
    }*/
}
