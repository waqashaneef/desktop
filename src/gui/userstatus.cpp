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

#include "userstatus.h"
#include "account.h"
#include "accountstate.h"
#include "networkjobs.h"
#include "folderman.h"
#include "creds/abstractcredentials.h"
#include <theme.h>

#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>

namespace OCC {

UserStatus::UserStatus(AccountState *accountState, QObject *parent)
    : QObject(parent)
    , _accountState(accountState)
    , _currentStatus(QStringLiteral("Offline"))
{
    fetchCurrentStatus();
}

void UserStatus::slotRequestFailed()
{
}

void UserStatus::fetchCurrentStatus()
{
    if (_job) {
        // The previous job was not finished?  Then we cancel it!
        _job->deleteLater();
    }

    AccountPtr account = _accountState->account();
    _job = new JsonApiJob(account, QStringLiteral("/ocs/v2.php/apps/user_status/api/v1/user_status"), this);
    _job->setTimeout(20 * 1000);
    connect(_job.data(), &JsonApiJob::jsonReceived, this, &UserStatus::slotFetchedCurrentStatus);
    connect(_job.data(), &AbstractNetworkJob::networkError, this, &UserStatus::slotRequestFailed);
    _job->start();
}

void UserStatus::slotFetchedCurrentStatus(const QJsonDocument &json)
{
    auto objData = json.object().value("ocs").toObject().value("data").toObject();

    //objData.value("id").toString();

    //emit fetchedCurrentStatus(this);
    _currentStatus = QString("Online");
}

QString UserStatus::currentStatus() const
{
    return _currentStatus;
}

} // namespace OCC
