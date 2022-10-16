#include "Database.h"
#include "ProjectManager.h"
#include "norm/Token.h"
#include <QDataStream>

Database::Database(ProjectManager* projectManager) : projectManager(projectManager) {

}

Database::~Database() {

}

void Database::serialize(QDataStream& stream) {
    for (auto tableIt = tables.cbegin(); tableIt != tables.cend(); tableIt++) {
        for (auto tokenIt = tableIt.value().cbegin(); tokenIt != tableIt.value().cend(); tokenIt++) {
            stream << tableIt.key(); // Token code
            tokenIt.value()->serialize(stream);
        }
    }
}

void Database::deserialize(QDataStream& stream) {
    while (!stream.atEnd()) {
        Norm::Code code;
        stream >> code;

        Norm::Token* token = projectManager->createToken(code);
        token->deserialize(stream);
    }
}

void Database::addToken(Norm::Token* token) {
    if (!token->id()) {
        Norm::Id lastId = sequences[token->code()];
        lastId++;
        sequences[token->code()] = lastId;
        token->setId(lastId);
    } else {
        sequences[token->code()] = qMax(token->id(), sequences[token->code()]);
    }

    tables[token->code()].insert(token->id(), token);
}

void Database::removeToken(Norm::Token* token) {
    if (tables.contains(token->code())) {
        Table& table = tables[token->code()];

        if (table.contains(token->id())) {
            table.remove(token->id());
            delete token;
        }
    }
}

Norm::Token* Database::token(Norm::Code code, Norm::Id id) {
    if (!tables.contains(code)) return nullptr;

    Table& table = tables[code];
    return table.contains(id) ? table[id] : nullptr;
}
