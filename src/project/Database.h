#pragma once
#include "core/CommonTypes.h"
#include <QMap>
#include <QScopedPointer>

namespace Norm {
    class Token;
}

class ProjectManager;
class QDataStream;

class Database {
public:
    using Table = QMap<Norm::Id, Norm::Token*>;

    Database(ProjectManager* projectManager);
    ~Database();

    void serialize(QDataStream& stream);
    void deserialize(QDataStream& stream);

    void addToken(Norm::Token* token);
    void removeToken(Norm::Token* token);
    Norm::Token* token(Norm::Code code, Norm::Id id);

private:
    ProjectManager* projectManager = nullptr;
    QMap<Norm::Code, Table> tables;
};
