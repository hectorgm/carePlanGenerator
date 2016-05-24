#ifndef ISSUEEDITOR_H
#define ISSUEEDITOR_H

#include <QDialog>

namespace Ui {
class IssueEditor;
}

class IssueEditor : public QDialog
{
    Q_OBJECT

public:
    explicit IssueEditor (QWidget *parent = 0);
    explicit IssueEditor (QList<QString> invalidNames, QWidget *parent = 0);
    explicit IssueEditor (QString issueName, QString issueDescription, QList<QString> invalidNames, QWidget *parent = 0);
    ~IssueEditor();

    QString getIssueName() noexcept;

    QString getIssueDescription() noexcept;

signals:
    void accepted (QString issueName, QString issueDescription);

private slots:
    void onNameLineEditEdited();
    void onSavePushButtonClicked();

private:
    Ui::IssueEditor *ui;

    QList<QString> existingNames;
};

#endif // ISSUEEDITOR_H
