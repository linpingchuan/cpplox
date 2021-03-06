#pragma once

// Related header
// C standard headers
// C++ standard headers
#include <memory>
#include <vector>
// Third-party headers
// This project's headers
#include "expression.hpp"
#include "literal.hpp"
#include "token.hpp"

namespace motts { namespace lox {
    struct Binary_expr : Expr {
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        explicit Binary_expr(std::unique_ptr<Expr>&& left, Token&& op, std::unique_ptr<Expr>&& right);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Grouping_expr : Expr {
        std::unique_ptr<Expr> expr;

        explicit Grouping_expr(std::unique_ptr<Expr>&& expr);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Literal_expr : Expr {
        Literal value;

        explicit Literal_expr(Literal&& value);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Unary_expr : Expr {
        Token op;
        std::unique_ptr<Expr> right;

        explicit Unary_expr(Token&& op, std::unique_ptr<Expr>&& right);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Var_expr : Expr {
        Token name;

        explicit Var_expr(Token&& name);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
        Token&& lvalue_name(const Runtime_error& throwable_if_not_lvalue) && override;
    };

    struct Assign_expr : Expr {
        Token name;
        std::unique_ptr<Expr> value;

        explicit Assign_expr(Token&& name, std::unique_ptr<Expr>&& value);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Logical_expr : Expr {
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        explicit Logical_expr(std::unique_ptr<Expr>&& left, Token&& op, std::unique_ptr<Expr>&& right);
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };

    struct Call_expr : Expr {
        std::unique_ptr<Expr> callee;
        Token closing_paren;
        std::vector<std::unique_ptr<Expr>> arguments;

        explicit Call_expr(
            std::unique_ptr<Expr>&& callee,
            Token&& closing_paren,
            std::vector<std::unique_ptr<Expr>>&& arguments
        );
        void accept(Expr_visitor&) const override;
        std::unique_ptr<Expr> clone() const override;
    };
}}
