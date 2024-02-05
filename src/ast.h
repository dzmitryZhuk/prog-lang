#pragma once

#include <string>
#include <vector>
#include <memory>

// AST expression
class ASTExpression {
    // TODO: add type of expression like number, string, etc.
    public:
        virtual ~ASTExpression() = default;
};

// Expression class for for numeric literals
class ASTExpressionNumber : public ASTExpression {
    public:
        ASTExpressionNumber(const double &value);
    private:
        double value_;
};

// Expression class for referencing a variable, like "val".
class ASTExpressionVariable : public ASTExpression {
    public:
        ASTExpressionVariable(const std::string& name);
    private:
        std::string name_;
};

// Expression class for a binary operator.
class ASTExpressionBinary : public ASTExpression {
    public:
        ASTExpressionBinary(const char &binaryOperator,
                          std::unique_ptr<ASTExpression> left,
                          std::unique_ptr<ASTExpression> right);
    private:
        char operator_;
        std::unique_ptr<ASTExpression> leftOperand_, rightOperand_;
};

// Expression class for function calls
class ASTExpressionCall : public ASTExpression {
    public:
        ASTExpressionCall(const std::string &callee,
                          std::vector<std::unique_ptr<ASTExpression>> args);
    private:
          std::string callee_;
          std::vector<std::unique_ptr<ASTExpression>> args_;
};

// This class represents the "prototype" for a function, which captures its name, and its argument names
class ASTPrototype {
    public:
        ASTPrototype(const std::string &name, const std::vector<std::string> &args);
        const std::string &name() const;
    private:
          std::string name_;
          std::vector<std::string> args_;
};

// This class represents a function definition itself
class ASTFunction {
    public:
        ASTFunction(std::unique_ptr<ASTPrototype> proto, std::unique_ptr<ASTExpression> body);
    private:
        std::unique_ptr<ASTPrototype> proto_;
        std::unique_ptr<ASTExpression> body_;
};
