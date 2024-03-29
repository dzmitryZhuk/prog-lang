#include "ast.h"

ASTNode::ASTNode()
    : left_(nullptr)
    , right_(nullptr)
{
}

ASTExpressionNumber::ASTExpressionNumber(const double& value)
    : value_(value)
{
    type_ = Lexer::Token::number;
}

const double ASTExpressionNumber::value() const
{
  return value_;
}

ASTExpressionVariable::ASTExpressionVariable(const std::string &name)
    : name_(name)
{
    type_ = Lexer::Token::identifier;
}

const std::string ASTExpressionVariable::name() const
{
  return name_;
}

// ASTExpressionBinary::ASTExpressionBinary(const char &binaryOperator,
//                                          std::unique_ptr<ASTExpression> left,
//                                          std::unique_ptr<ASTExpression> right)
//     : operator_(binaryOperator)
//     , leftOperand_(std::move(left))
//     , rightOperand_(std::move(right))
// {
// }

// ASTExpressionCall::ASTExpressionCall(const std::string &callee,
//                                      std::vector<std::unique_ptr<ASTExpression>> args)
//     : callee_(callee)
//     , args_(std::move(args))
// {
// }

// ASTPrototype::ASTPrototype(const std::string &name, const std::vector<std::string> &args)
//     : name_(name)
//     , args_(std::move(args))
// {
// }

// const std::string &ASTPrototype::name() const
// {
//     return name_;
// }

// ASTFunction::ASTFunction(std::unique_ptr<ASTPrototype> proto, std::unique_ptr<ASTExpression> body)
//     : proto_(std::move(proto))
//     , body_(std::move(body))
// {
// }
