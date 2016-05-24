#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "careplangenerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent (QCloseEvent *event) override;

private slots:
    void onAddPushButtonClicked();
    void onDeletePushButtonClicked();
    void onCopyPushButtonClicked();
    void onIssueEditorAccepted (QString issueName, QString issueDescription);
    void onIssuesListWidgetItemChanged (QListWidgetItem *item);
    void onIssuesListWidgetItemDoubleClick (QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    QString issuesFile;

    CarePlanGenerator carePlanGenerator;

    void populateIssueLists();

    void listViewTest();
};

#endif // MAINWINDOW_H
