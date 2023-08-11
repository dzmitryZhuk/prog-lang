#ifndef _COMPILLER_AST_H_
#define _COMPILLER_AST_H_

#include <string>
#include <vector>
#include <memory>

// AST expression
class ASTExpr {
public:
    virtual ~ASTExpr() = default;
};

// Expression class for for numeric literals
class ASTExprNumber : public ASTExpr {
    double m_value;
public:
    ASTExprNumber(double value) : m_value(value) {}
};

// Expression class for referencing a variable, like "val".
class ASTExprVariable : ASTExpr {
    std::string m_name;
public:
    ASTExprVariable(const std::string& name) : m_name(name) {}
};

/// Expression class for a binary operator.
class ASTExprBinary : public ASTExpr {
  char m_operator;
  std::unique_ptr<ASTExpr> m_leftOperand, m_rightOperand;

public:
  ASTExprBinary(char operator_, std::unique_ptr<ASTExpr> left, std::unique_ptr<ASTExpr> right)
    : m_operator(operator_), m_leftOperand(std::move(left)), m_rightOperand(std::move(right)) {}
};

/// Expression class for function calls
class ASTExprCall : public ASTExpr {
  std::string m_callee;
  std::vector<std::unique_ptr<ASTExpr>> m_args;

public:
  ASTExprCall(const std::string &callee, std::vector<std::unique_ptr<ASTExpr>> args)
    : m_callee(callee), m_args(std::move(args)) {}
};

#endif