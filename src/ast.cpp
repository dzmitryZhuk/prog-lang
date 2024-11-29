#include "ast.h"

ASTNode::ASTNode()
{
}

void ASTNode::addChild(std::unique_ptr<ASTNode> child)
{
    children_.push_back(std::move(child));
}

std::optional<Lexer::Token> ASTNode::type() const
{
    return type_;
}

ASTExpressionNumber::ASTExpressionNumber(double value)
    : value_(value)
    // , type_(Lexer::Token::number)
{
    type_ = Lexer::Token::number;
}

double ASTExpressionNumber::value() const
{
    return value_;
}

ASTExpressionVariable::ASTExpressionVariable(const std::string& name)
    : name_(name)
    // , type_(Lexer::Token::identifier)
{
    type_ = Lexer::Token::identifier;
}

const std::string& ASTExpressionVariable::name() const
{
    return name_;
}

ASTExpressionAssignment::ASTExpressionAssignment(const std::string& variableName, 
                                                 std::unique_ptr<ASTExpression> value)
    : variableName_(variableName)
    , value_(std::move(value))
{
    type_ = Lexer::Token::assignment;
}

const std::string& ASTExpressionAssignment::variableName() const
{
    return variableName_;
}

const ASTExpression* ASTExpressionAssignment::value() const
{
    return value_.get();
}

ASTExpressionReturn::ASTExpressionReturn(std::unique_ptr<ASTExpression> value)
    : value_(std::move(value))
{
    type_ = Lexer::Token::returning;
}

const ASTExpression* ASTExpressionReturn::value() const
{
    return value_.get();
}

ASTExpressionBinary::ASTExpressionBinary(const std::string& binaryOperator, 
                                         std::unique_ptr<ASTExpression> left, 
                                         std::unique_ptr<ASTExpression> right)
    : operator_(binaryOperator)
{
    // type_ = Lexer::Token::binary_operator;
}

const std::string& ASTExpressionBinary::binaryOperator() const
{
    return operator_;
}

ASTExpressionCall::ASTExpressionCall(const std::string& callee, 
                                     std::vector<std::unique_ptr<ASTExpression>> args)
    : callee_(callee)
    , args_(std::move(args))
{
    // type_ = Lexer::Token::function_call;
}

const std::string& ASTExpressionCall::callee() const
{
    return callee_;
}

const std::vector<std::unique_ptr<ASTExpression>>& ASTExpressionCall::args() const
{
    return args_;
}

ASTPrototype::ASTPrototype(const std::string& name, const std::vector<std::string>& args)
    : name_(name)
    , args_(args)
{
}

const std::string& ASTPrototype::name() const
{
    return name_;
}

const std::vector<std::string>& ASTPrototype::args() const
{
    return args_;
}

ASTFunction::ASTFunction(std::unique_ptr<ASTPrototype> proto, std::unique_ptr<ASTExpression> body)
    : proto_(std::move(proto))
    , body_(std::move(body))
{
}

const ASTPrototype* ASTFunction::proto() const
{
    return proto_.get();
}

const ASTExpression* ASTFunction::body() const
{
    return body_.get();
}
