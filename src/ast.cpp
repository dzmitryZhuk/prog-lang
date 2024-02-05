#include "ast.h"

ASTExpressionNumber::ASTExpressionNumber(const double& value)
    : value_(value)
{
}

ASTExpressionVariable::ASTExpressionVariable(const std::string &name)
    : name_(name)
{
}

ASTExpressionBinary::ASTExpressionBinary(const char &binaryOperator,
                                         std::unique_ptr<ASTExpression> left,
                                         std::unique_ptr<ASTExpression> right)
    : operator_(binaryOperator)
    , leftOperand_(std::move(left))
    , rightOperand_(std::move(right))
{
}

ASTExpressionCall::ASTExpressionCall(const std::string &callee,
                                     std::vector<std::unique_ptr<ASTExpression>> args)
    : callee_(callee)
    , args_(std::move(args))
{
}

ASTPrototype::ASTPrototype(const std::string &name, const std::vector<std::string> &args)
    : name_(name)
    , args_(std::move(args))
{
}

const std::string &ASTPrototype::name() const
{
    return name_;
}

ASTFunction::ASTFunction(std::unique_ptr<ASTPrototype> proto, std::unique_ptr<ASTExpression> body)
    : proto_(std::move(proto))
    , body_(std::move(body))
{
}
