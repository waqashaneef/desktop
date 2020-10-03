/*
 * Copyright (C) by Camila <hello@camila.codes>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef USERSTATUS_H
#define USERSTATUS_H

#include <QObject>
#include <QPointer>
#include <QVariant>

namespace OCC {
class AccountState;
class JsonApiJob;

class UserStatus : public QObject
{
    Q_OBJECT
public:
    explicit UserStatus(AccountState *accountState, QObject *parent = nullptr);
    QString currentStatus() const;
    void fetchCurrentStatus();

private slots:
    void slotFetchedCurrentStatus(const QJsonDocument &json);
    void slotRequestFailed();

signals:
    void fetchedCurrentStatus(UserStatus *userStatus);

private:
    QPointer<AccountState> _accountState;
    QPointer<JsonApiJob> _job; // the currently running job
    QString _currentStatus;
};


} // namespace OCC

#endif //USERSTATUS_H
