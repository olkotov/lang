// Oleg Kotov

#pragma once

#include "token.h"
#include "utils.h"

#include <any>
#include <string>
#include <stdio.h>

bool isTruthy( const std::any& object );
bool isEqual( const std::any& a, const std::any& b );

// i can use Visitor pattern to separate data and logic here

class Expression
{
public:

	virtual ~Expression() {}
	virtual std::any evaluate() const = 0;
};

class LiteralExpr : public Expression
{
public:

	LiteralExpr( const std::any& value )
		: value( value )
	{
		printf( "literal_expr created: " );
		debugPrintAny( value );
	}

	std::any evaluate() const override
	{
		return value;
	}

	std::any value;
};

class GroupingExpr : public Expression
{
public:

	GroupingExpr( Expression* value )
		: value( value )
	{
		printf( "grouping_expr created\n" );
	}

	std::any evaluate() const override
	{
		return value->evaluate();
	}

	Expression* value;
};

// 'not' and 'negation' operators
class UnaryExpr : public Expression
{
public:

	UnaryExpr( Token op, Expression* right )
		: op( op )
		, right( right )
	{
		printf( "unary_expr created\n" );
	}

	std::any evaluate() const override
	{
		std::any rightValue = right->evaluate();

		switch ( op.type )
		{
			case BANG: return !isTruthy( rightValue );
			case MINUS: return -std::any_cast<float>( rightValue );
		}

		return nullptr;
	}

	Token op;
	Expression* right;
};

// the arithmetic ( +, -, *, / ) and logic ( ==, !=, <, <=, >, >= ) operators
class BinaryExpr : public Expression
{
public:

	BinaryExpr( Expression* left, Token op, Expression* right )
		: left( left )
		, op( op )
		, right( right )
	{
		printf( "binary_expr created: %s\n", op.lexeme.c_str() );
	}

	std::any evaluate() const override
	{
		std::any leftValue = left->evaluate();
		std::any rightValue = right->evaluate();

		printf( "left: " );
		debugPrintAny( leftValue );

		printf( "right: " );
		debugPrintAny( rightValue );

		std::any result;

		switch ( op.type )
		{
			// arithmetic

			case PLUS:

				if ( leftValue.type() == typeid( float ) && rightValue.type() == typeid( float ) )
				{
					result = std::any_cast<float>( leftValue ) + std::any_cast<float>( rightValue );
					printf( "result: " );
					debugPrintAny( result );
					return result;
				}

				if ( leftValue.type() == typeid( int ) && rightValue.type() == typeid( int ) )
				{
					result = std::any_cast<int>( leftValue ) + std::any_cast<int>( rightValue );
					printf( "result: " );
					debugPrintAny( result );
					return result;
				}

				if ( leftValue.type() == typeid( std::string ) && rightValue.type() == typeid( std::string ) )
				{
					result = std::any_cast<std::string>( leftValue ) + std::any_cast<std::string>( rightValue );
					printf( "result: " );
					debugPrintAny( result );
					return result;
				}

				break;

			case MINUS:
				result = std::any_cast<float>( leftValue ) - std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case STAR:
				result = std::any_cast<float>( leftValue ) * std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case SLASH: 
				result = std::any_cast<float>( leftValue ) / std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			// logic

			case EQUAL_EQUAL:
				result = isEqual( leftValue, rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case BANG_EQUAL:
				result = !isEqual( leftValue, rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case LESS:
				result = std::any_cast<float>( leftValue ) < std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case LESS_EQUAL:
				result = std::any_cast<float>( leftValue ) <= std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case GREATER:
				result = std::any_cast<float>( leftValue ) > std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;

			case GREATER_EQUAL:
				result = std::any_cast<float>( leftValue ) >= std::any_cast<float>( rightValue );
				printf( "result: " );
				debugPrintAny( result );
				return result;
		}

		return nullptr;
	}

	Expression* left;
	Token op;
	Expression* right;
};

