#pragma once

namespace Norm {
    class BlockExpression;
}

class QString;

class TemplateCreator {
public:
    static void createBinary(const QString& name, const QString& filePath);
    static void createLibrary(const QString& name, const QString& filePath);

private:
    static Norm::BlockExpression* createBlock();
};
