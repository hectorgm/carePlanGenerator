#include "issue.h"

Issue::Issue() noexcept
    : name()
    , description()
{
}

Issue::Issue(QString name, QString description) noexcept
    : name (name)
    , description (description)
{
}

bool Issue::operator == (Issue issue) noexcept
{
  return (getName() == issue.getName())
          && (getDescription() == issue.getDescription());
}

QString Issue::getName() const noexcept
{
    return name;
}

QString Issue::getDescription() const noexcept
{
    return description;
}

void Issue::setName(const QString &value) noexcept
{
    name = value;
}

void Issue::setDescription(const QString &value) noexcept
{
    description = value;
}

