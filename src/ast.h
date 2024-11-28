#pragma once

#include "lexer.h"

#include <string>
#include <vector>
#include <memory>
#include <optional>

class ASTNode {
public:
    ASTNode();
    virtual ~ASTNode() = default;

    void setLeft(std::unique_ptr<ASTNode> left);
    void setRight(std::unique_ptr<ASTNode> right);
    ASTNode* left() const;
    ASTNode* right() const;

    std::optional<Lexer::Token> type() const;

protected:
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
    std::optional<Lexer::Token> type_;
};

class ASTExpression : public ASTNode {
public:
    virtual ~ASTExpression() = default;
};

class ASTExpressionNumber : public ASTExpression {
public:
    explicit ASTExpressionNumber(double value);
    double value() const;

protected:
    double value_;
};

class ASTExpressionVariable : public ASTExpression {
public:
    explicit ASTExpressionVariable(const std::string& name);
    const std::string& name() const;

protected:
    std::string name_;
};

class ASTExpressionAssignment : public ASTExpression {
public:
    ASTExpressionAssignment(const std::string& variableName, std::unique_ptr<ASTExpression> value);
    const std::string& variableName() const;
    const ASTExpression* value() const;

protected:
    std::string variableName_;
    std::unique_ptr<ASTExpression> value_;
};

class ASTExpressionReturn : public ASTExpression {
public:
    ASTExpressionReturn(std::unique_ptr<ASTExpression> value);
    const ASTExpression* value() const;

protected:
    std::unique_ptr<ASTExpression> value_;
};

class ASTExpressionBinary : public ASTExpression {
public:
    ASTExpressionBinary(const std::string& binaryOperator, 
                        std::unique_ptr<ASTExpression> left, 
                        std::unique_ptr<ASTExpression> right);
    const std::string& binaryOperator() const;

protected:
    std::string operator_;
};

// function call
class ASTExpressionCall : public ASTExpression {
public:
    ASTExpressionCall(const std::string& callee, std::vector<std::unique_ptr<ASTExpression>> args);
    const std::string& callee() const;
    const std::vector<std::unique_ptr<ASTExpression>>& args() const;

protected:
    std::string callee_;
    std::vector<std::unique_ptr<ASTExpression>> args_;
};

// Function signature
class ASTPrototype : public ASTNode {
public:
    ASTPrototype(const std::string& name, const std::vector<std::string>& args);
    const std::string& name() const;
    const std::vector<std::string>& args() const;

protected:
    std::string name_;
    std::vector<std::string> args_;
};

class ASTFunction : public ASTNode {
public:
    ASTFunction(std::unique_ptr<ASTPrototype> proto, std::unique_ptr<ASTExpression> body);
    const ASTPrototype* proto() const;
    const ASTExpression* body() const;

protected:
    std::unique_ptr<ASTPrototype> proto_;
    std::unique_ptr<ASTExpression> body_;
};
