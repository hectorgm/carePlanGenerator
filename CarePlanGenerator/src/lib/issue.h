#ifndef ISSUE_H
#define ISSUE_H

#include <QString>

class Issue
{
public:
    Issue() noexcept;
    Issue (QString name, QString description) noexcept;

    ~Issue() = default;

    bool operator == (Issue issue) noexcept;

    QString getName() const noexcept;
    QString getDescription() const noexcept;

    void setName (const QString &value) noexcept;
    void setDescription (const QString &value) noexcept;


private:
    QString name;
    QString description;
};

#endif // ISSUE_H
