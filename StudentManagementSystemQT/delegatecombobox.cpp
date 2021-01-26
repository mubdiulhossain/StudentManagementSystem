#include "delegatecombobox.h"

DelegateComboBox::DelegateComboBox(QObject* parent):QItemDelegate (parent)
{

}
QWidget* DelegateComboBox::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *status = new QComboBox(parent);
    status->addItem("Open");
    status->addItem("Close");
    return status;
}
void DelegateComboBox::setEditorData(QWidget *status, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(status);
    QString value = index.model()->data(index, Qt::EditRole).toString();
    comboBox->setCurrentText(value);
}
void DelegateComboBox::setModelData(QWidget *status, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(status);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}
void DelegateComboBox::updateEditorGeometry(QWidget *status, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    status->setGeometry(option.rect);
}

