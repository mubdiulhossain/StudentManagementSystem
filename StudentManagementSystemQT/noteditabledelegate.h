#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H
#include<QItemDelegate>
#include<QModelIndex>
#include<QObject>
#include<QSize>
#include<QComboBox>

//this class is created only for to add no editable cell in some tables such as edit course for academicians

class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate(QObject *parent = 0);
protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};
#endif // NOTEDITABLEDELEGATE_H
