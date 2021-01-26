#ifndef DELEGATECOMBOBOX_H
#define DELEGATECOMBOBOX_H
#include<QItemDelegate>
#include<QModelIndex>
#include<QObject>
#include<QSize>
#include<QComboBox>

//this extra class is created to add a combo box which contains open or close to select these item from course edit status table

class DelegateComboBox : public QItemDelegate
{
   Q_OBJECT
public:
    explicit DelegateComboBox(QObject* parent=0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const; //delegate editor (your custom widget)
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const; //transfer editor data to model
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // DELEGATECOMBOBOX_H
