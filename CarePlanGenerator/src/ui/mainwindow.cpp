#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QListView>
#include <QMessageBox>
#include <QClipboard>
#include <QCloseEvent>

#include "texteditdelegate.h"
#include "issue.h"
#include "issueeditor.h"

MainWindow::MainWindow (QWidget *parent) :
    QMainWindow (parent),
    ui (new Ui::MainWindow),
    issuesFile ("carePlanIssues.json"),
    carePlanGenerator (issuesFile)
{
    ui->setupUi (this);

    populateIssueLists();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onIssuesListWidgetItemChanged (QListWidgetItem *listWidgetItem)
{
    auto listViewModel = dynamic_cast<QStandardItemModel*> (ui->listView->model());
    if (listViewModel == nullptr)
        return;

    if (listWidgetItem->checkState() == Qt::Checked)
    {
        auto issue = carePlanGenerator.getIssue (listWidgetItem->text());
        auto listViewItem = new QStandardItem (issue.getDescription());

        listViewItem->setDragEnabled (true);
        listViewItem->setDropEnabled (false);
        listViewItem->setData (QVariant (listWidgetItem->text()));
        listViewModel->appendRow (listViewItem);
    }
    else
    {
        for (auto rowNum = 0; rowNum < listViewModel->rowCount(); ++rowNum)
        {
            auto listViewItem = listViewModel->item(rowNum);
            if (listViewItem->data().toString().compare (listWidgetItem->text()) == 0)
            {
                listViewModel->removeRow (rowNum);
            }
        }
    }
}

void MainWindow::populateIssueLists()
{
    auto issueList = carePlanGenerator.getIssueList();

    auto itemModel = new QStandardItemModel (this);
    auto textEditDelegate = new TextEditDelegate(this);
    ui->listView->setDragDropMode (QListView::InternalMove);

    for (auto issue : issueList)
    {
        auto listWidgetItem = new QListWidgetItem (issue.getName());
        listWidgetItem->setCheckState (Qt::Unchecked);
        ui->issuesListWidget->insertItem (ui->issuesListWidget->count(), listWidgetItem);
    }

    ui->listView->setModel (itemModel);
    ui->listView->setItemDelegate (textEditDelegate);
}

void MainWindow::onAddPushButtonClicked()
{
    IssueEditor issueEditor (carePlanGenerator.getIssueNameList(), this);
    connect (&issueEditor, &IssueEditor::accepted, this, &onIssueEditorAccepted);
    issueEditor.exec();
}

void MainWindow::onDeletePushButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText ("Are you sure you want to delete the selected issues?");
    msgBox.setStandardButtons (QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton (QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        auto selectedItems = ui->issuesListWidget->selectedItems();
        for (auto selectedItem : selectedItems)
        {
            carePlanGenerator.deleteIssue (selectedItem->text());
            ui->issuesListWidget->takeItem (ui->issuesListWidget->row (selectedItem));

            auto listViewModel = dynamic_cast<QStandardItemModel *> (ui->listView->model());
            for (auto rowNum = 0; rowNum < listViewModel->rowCount(); ++rowNum)
            {
                auto listViewItem = listViewModel->item (rowNum);
                if (listViewItem->data().toString().compare (selectedItem->text()) == 0)
                {
                    listViewModel->removeRow (rowNum);
                    break;
                }
            }
        }
    }
}

void MainWindow::onCopyPushButtonClicked()
{
    QClipboard *clipboard {QApplication::clipboard()};
    clipboard->clear();
    auto listViewModel = dynamic_cast<QStandardItemModel *> (ui->listView->model());
    for (auto rowNum = 0; rowNum < listViewModel->rowCount(); ++rowNum)
    {
        auto listViewItem = listViewModel->item (rowNum);
        clipboard->setText (clipboard->text() + listViewItem->text() + "\n");
    }
}

void MainWindow::onIssueEditorAccepted (QString issueName, QString issueDescription)
{
    if (carePlanGenerator.containsIssue (issueName))
    {
        carePlanGenerator.updateIssue (issueName, issueName, issueDescription);
    }
    else
    {
        carePlanGenerator.addIssue(issueName, issueDescription);

        auto listWidgetItem = new QListWidgetItem (issueName);
        listWidgetItem->setCheckState (Qt::Checked);
        ui->issuesListWidget->insertItem (ui->issuesListWidget->count(), listWidgetItem);

        QStandardItem *listViewItem = new QStandardItem(issueDescription);
        auto listViewModel = dynamic_cast<QStandardItemModel*> (ui->listView->model());

        listViewItem->setDragEnabled (true);
        listViewItem->setDropEnabled (false);
        listViewItem->setData (QVariant (issueName));
        listViewModel->insertRow (listViewModel->rowCount(), listViewItem);
    }
}

void MainWindow::onIssuesListWidgetItemDoubleClick (QListWidgetItem *item)
{
    auto issue = carePlanGenerator.getIssue (item->text());
    IssueEditor issueEditor (issue.getName(),
                             issue.getDescription(),
                             carePlanGenerator.getIssueNameList(),
                             this);

    connect (&issueEditor, &IssueEditor::accepted, this, &onIssueEditorAccepted);
    issueEditor.exec();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    carePlanGenerator.issueListToFile (issuesFile);

    event->accept();
}
