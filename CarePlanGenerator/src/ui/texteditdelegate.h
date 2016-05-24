#ifndef TEXTEDITDELEGATE_H
#define TEXTEDITDELEGATE_H

#include <QStyledItemDelegate>

class TextEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TextEditDelegate (QObject *parent = 0) noexcept;

    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData (QWidget *editor, const QModelIndex &index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry (QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TEXTEDITDELEGATE_H
