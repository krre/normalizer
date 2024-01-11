#pragma once
#include "core/async/Task.h"
#include <QUrlQuery>
#include <QVariant>

class RestApi {
public:
    virtual Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery()) = 0;
    virtual Async::Task<QVariant> deleteResource(const QString& endpoint) = 0;
    virtual Async::Task<QVariant> post(const QString& endpoint, const QVariant& data = QVariant()) = 0;
    virtual Async::Task<QVariant> put(const QString& endpoint, const QVariant& data = QVariant()) = 0;
};
