#include <QTextEdit>

#include "texteditdelegate.h"

TextEditDelegate::TextEditDelegate (QObject *parent) noexcept
    : QStyledItemDelegate(parent)
{
}

QWidget *TextEditDelegate::createEditor (QWidget *parent,
                                         const QStyleOptionViewItem &/* option */,
                                         const QModelIndex &/* index */) const
{
    auto editor = new QTextEdit (parent);

    return editor;
}

void TextEditDelegate::setEditorData (QWidget *editor,
                                      const QModelIndex &index) const
{
    auto value = index.model()->data (index, Qt::EditRole).toString();

    auto textEdit = static_cast<QTextEdit *> (editor);
    textEdit->setText (value);
}

void TextEditDelegate::setModelData (QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    auto textEdit = static_cast<QTextEdit *> (editor);
    auto value = textEdit->toPlainText();

    model->setData (index, value, Qt::EditRole);
}

void TextEditDelegate::updateEditorGeometry (QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &/* index */) const
{
    editor->setGeometry (option.rect);
}
