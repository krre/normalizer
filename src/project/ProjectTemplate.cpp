#include "ProjectTemplate.h"
#include "ProjectManager.h"
#include "core/Constants.h"
#include "core/Global.h"
#include "norm/project/Version.h"
#include "norm/function/Function.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/Literal.h"

ProjectTemplate::ProjectTemplate(ProjectManager* projectManager) : projectManager(projectManager) {

}

void ProjectTemplate::createApp() {
    createProject(Norm::Project::Target::Application);

    auto entryFunc = static_cast<Norm::Function*>(projectManager->createToken(Const::Norm::Token::Function));
    entryFunc->setName("Main");

    auto expression = createExpression();
    expression->setFunctionId(entryFunc->id());
}

void ProjectTemplate::createLib() {
    createProject(Norm::Project::Target::Library);

    auto addFunc = static_cast<Norm::Function*>(projectManager->createToken(Const::Norm::Token::Function));
    addFunc->setName("Add");

    auto expression = createExpression();
    expression->setFunctionId(addFunc->id());
}

void ProjectTemplate::createProject(Norm::Project::Target target) {
    auto project = static_cast<Norm::Project*>(projectManager->createToken(Const::Norm::Token::Project));
    project->setTarget(target);

    auto projVersion = static_cast<Norm::Version*>(projectManager->createToken(Const::Norm::Token::Version));
    projVersion->setKind(Norm::Version::Kind::Project);
    projVersion->setVersion(QVersionNumber(0, 1));

    auto normVersion = static_cast<Norm::Version*>(projectManager->createToken(Const::Norm::Token::Version));
    normVersion->setKind(Norm::Version::Kind::Norm);
    normVersion->setVersion(Global::Version::language());
}

Norm::Expression* ProjectTemplate::createExpression() {
    auto math = static_cast<Norm::Math*>(projectManager->createToken(Const::Norm::Token::Math));
    math->setOperation(Norm::Math::Operation::Addition);

    auto num1 = static_cast<Norm::NumberLiteral*>(projectManager->createToken(Const::Norm::Token::NumberLiteral));
    num1->setLiteral(3);
    num1->setExpressionId(math->id());

    auto num2 = static_cast<Norm::NumberLiteral*>(projectManager->createToken(Const::Norm::Token::NumberLiteral));
    num2->setLiteral(2);
    num2->setExpressionId(math->id());

    return math;
}
