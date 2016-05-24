#include "issueeditor.h"
#include "ui_issueeditor.h"

#include <QMessageBox>

#include "issuenamevalidator.h"

IssueEditor::IssueEditor (QWidget *parent) :
    QDialog (parent),
    ui (new Ui::IssueEditor),
    existingNames()
{
    ui->setupUi(this);

    setWindowTitle("New issue");
}

IssueEditor::IssueEditor (QList<QString> existingNames, QWidget *parent) :
    QDialog (parent),
    ui (new Ui::IssueEditor),
    existingNames (existingNames)
{
    ui->setupUi(this);

    setWindowTitle("New issue");

    IssueNameValidator validator (existingNames, this);
    ui->nameLineEdit->setValidator (&validator);

    connect (ui->nameLineEdit, &ui->nameLineEdit->textEdited, this, &onNameLineEditEdited);
}

IssueEditor::IssueEditor(QString issueName, QString issueDescription, QList<QString> existingNames, QWidget *parent) :
    QDialog (parent),
    ui (new Ui::IssueEditor),
    existingNames (existingNames)
{
    ui->setupUi(this);

    setWindowTitle(issueName);
    ui->nameLineEdit->setText(issueName);
    ui->descriptionTextEdit->setText(issueDescription);
}

IssueEditor::~IssueEditor()
{
    delete ui;
}

QString IssueEditor::getIssueName() noexcept
{
    return ui->nameLineEdit->text();
}

QString IssueEditor::getIssueDescription() noexcept
{
    return ui->descriptionTextEdit->toPlainText();
}

void IssueEditor::onSavePushButtonClicked()
{
    if (existingNames.contains(ui->nameLineEdit->text()))
    {
        QMessageBox msgBox;
        msgBox.setText(ui->nameLineEdit->text() + " already exists.");
        msgBox.setInformativeText("Do you want to overwrite it?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Cancel)
            return;
    }

    emit accepted(ui->nameLineEdit->text(),
                  ui->descriptionTextEdit->toPlainText());
    close();
}

void IssueEditor::onNameLineEditEdited()
{
    if (ui->nameLineEdit->hasAcceptableInput() == false)
    {
        ui->savePushButton->setEnabled(false);
    }
    else
    {
        ui->savePushButton->setEnabled(true);
    }
}
