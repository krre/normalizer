#pragma once

class QDataStream;

class Database {
public:
    Database();

    void serialize(QDataStream& stream);
    void deserialize(QDataStream& stream);
};
