#include "ProjectTemplate.h"
#include "ProjectManager.h"
#include "core/Constants.h"
#include "norm/Name.h"
#include "norm/function/Function.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/literal/NumberLiteral.h"

ProjectTemplate::ProjectTemplate(ProjectManager* projectManager) : projectManager(projectManager) {

}

void ProjectTemplate::createApp() {
    auto name = static_cast<Norm::Name*>(projectManager->createToken(Const::Norm::Token::Name));
    name->setName("Main");

    auto entryFunc = static_cast<Norm::Function*>(projectManager->createToken(Const::Norm::Token::Function));
    entryFunc->setNameId(name->id());

    auto expression = createExpression();
    expression->setFunctionId(entryFunc->id());
}

void ProjectTemplate::createLib() {
    auto name = static_cast<Norm::Name*>(projectManager->createToken(Const::Norm::Token::Name));
    name->setName("Add");

    auto addFunc = static_cast<Norm::Function*>(projectManager->createToken(Const::Norm::Token::Function));
    addFunc->setNameId(name->id());

    auto expression = createExpression();
    expression->setFunctionId(addFunc->id());
}

Norm::Expression* ProjectTemplate::createExpression() {
    auto math = static_cast<Norm::Math*>(projectManager->createToken(Const::Norm::Token::Math));
    math->setOperation(Norm::Math::Operation::Addition);

    auto num1 = static_cast<Norm::NumberLiteral*>(projectManager->createToken(Const::Norm::Token::NumberLiteral));
    num1->setLiteral(3);

    auto num2 = static_cast<Norm::NumberLiteral*>(projectManager->createToken(Const::Norm::Token::NumberLiteral));
    num2->setLiteral(2);

    return math;
}
