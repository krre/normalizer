#pragma once
#include "HttpRequestAttributes.h"
#include "external/network/RestApi.h"
#include "core/async/Task.h"
#include "core/async/NetworkAccessManager.h"
#include <QUrlQuery>

class HttpRestApi : public RestApi {
public:
    HttpRestApi(const QUrl& url);

    void setUrl(const QUrl& url);
    void setToken(const QString& token);

    Async::Task<QVariant> get(const QString& endpoint, const QUrlQuery& query = QUrlQuery()) override;
    Async::Task<QVariant> del(const QString& endpoint) override;
    Async::Task<QVariant> post(const QString& endpoint, const QVariant& data = QVariant()) override;
    Async::Task<QVariant> put(const QString& endpoint, const QVariant& data = QVariant()) override;

private:
    Async::NetworkAccessManager m_networkAccessManager;
    HttpRequestAttributes m_requestAttributes;
};
