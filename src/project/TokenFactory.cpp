#include "TokenFactory.h"
#include "norm/project/Project.h"
#include "norm/project/Version.h"
#include "norm/function/Function.h"
#include "norm/function/Parameter.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/literal/StringLiteral.h"
#include "norm/expression/literal/NumberLiteral.h"
#include "norm/expression/literal/BooleanLiteral.h"
#include "norm/Name.h"
#include "norm/Module.h"
#include "core/Constants.h"

TokenFactory::TokenFactory() {
    creators.insert(Const::Norm::Token::Project, [] { return new Norm::Project; });
    creators.insert(Const::Norm::Token::Version, [] { return new Norm::Version; });
    creators.insert(Const::Norm::Token::Name, [] { return new Norm::Name; });
    creators.insert(Const::Norm::Token::Module, [] { return new Norm::Module; });
    creators.insert(Const::Norm::Token::Function, [] { return new Norm::Function; });
    creators.insert(Const::Norm::Token::Parameter, [] { return new Norm::Parameter; });
    creators.insert(Const::Norm::Token::Math, [] { return new Norm::Math; });
    creators.insert(Const::Norm::Token::StringLiteral, [] { return new Norm::StringLiteral; });
    creators.insert(Const::Norm::Token::NumberLiteral, [] { return new Norm::NumberLiteral; });
    creators.insert(Const::Norm::Token::BooleanLiteral, [] { return new Norm::BooleanLiteral; });
}

Norm::Token* TokenFactory::create(Norm::Code code) {
    if (!creators.contains(code)) {
        throw std::runtime_error(QString("Token creator not found for code %1").arg(code).toStdString());
    }

    return creators[code]();
}
