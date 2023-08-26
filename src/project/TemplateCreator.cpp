#include "TemplateCreator.h"
#include <norm/token/target/BinaryTarget.h>
#include <norm/token/target/LibraryTarget.h>
#include <norm/token/item/Function.h>
#include <norm/token/expression/BlockExpression.h>
#include <norm/token/statement/AssignStatement.h>
#include <norm/token/Identifier.h>
#include <norm/token/type/Integer.h>
#include <norm/token/expression/OperatorExpression.h>
#include <norm/token/expression/LiteralExpression.h>
#include <norm/io/FileWriter.h>
#include <QString>

void TemplateCreator::createBinary(const QString& name, const QString& filePath) {
    using namespace Norm;

    BinaryTarget target(name.toStdString());
    target.main()->setBlock(createBlock());

    FileWriter writer;
    writer.write(filePath.toStdString(), &target);
}

void TemplateCreator::createLibrary(const QString& name, const QString& filePath) {
    using namespace Norm;

    auto sum = new Function("sum");
    sum->setBlock(createBlock());

    LibraryTarget target(name.toStdString());
    target.addItem(sum);

    FileWriter writer;
    writer.write(filePath.toStdString(), &target);
}

Norm::BlockExpression* TemplateCreator::createBlock() {
    using namespace Norm;

    auto sumExpr = new SumOperator;
    sumExpr->addExpression(new IntegerLiteral("2"));
    sumExpr->addExpression(new IntegerLiteral("3"));

    auto assign = new AssignStatement;
    assign->setIdentifier(new Identifier("x", new Integer));
    assign->setExpression(sumExpr);

    auto block = new BlockExpression;
    block->addStatement(assign);

    return block;
}
