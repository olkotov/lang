// Oleg Kotov

#pragma once

#include "token.h"
#include "expression.h"
#include <vector>

class Parser
{
public:

	Parser( const std::vector<Token>& tokens )
		: m_tokens( tokens )
	{}

public:

	Expression* parse()
	{
		return expression();
	}

private:

	Expression* expression()
	{
		return equality();
	}

	// !=, ==
	Expression* equality()
	{
		Expression* expr = comparison();

		while ( match( BANG_EQUAL, EQUAL_EQUAL ) )
		{
			Token op = previous();
			Expression* right = comparison();
			expr = new BinaryExpr( expr, op, right );
		}

		return expr;
	}

	// >, >=, <, <=
	Expression* comparison()
	{
		Expression* expr = term();

		while ( match( GREATER, GREATER_EQUAL, LESS, LESS_EQUAL ) )
		{
			Token op = previous();
			Expression* right = term();
			expr = new BinaryExpr( expr, op, right );
		}

		return expr;
	}

	// -, +
	Expression* term()
	{
		Expression* expr = factor();

		while ( match( MINUS, PLUS ) )
		{
			Token op = previous();
			Expression* right = factor();
			expr = new BinaryExpr( expr, op, right );
		}

		return expr;
	}

	// /, *
	Expression* factor()
	{
		Expression* expr = unary();

		while ( match( SLASH, STAR ) )
		{
			Token op = previous();
			Expression* right = unary();
			expr = new BinaryExpr( expr, op, right );
		}

		return expr;
	}

	// !, -
	Expression* unary()
	{
		if ( match( BANG, MINUS ) )
		{
			Token op = previous();
			Expression* right = unary();
			return new UnaryExpr( op, right );
		}

		return primary();
	}

	// true, false, nullptr, literal, (group)
	Expression* primary()
	{
		if ( match( KEYWORD_FALSE ) ) return new LiteralExpr( false );
		if ( match( KEYWORD_TRUE ) ) return new LiteralExpr( true );
		if ( match( KEYWORD_NULL ) ) return new LiteralExpr( nullptr );

		if ( match( NUMBER, STRING ) )
		{
			return new LiteralExpr( previous().m_literal );
		}

		if ( match( OPEN_PAREN ) ) 
		{
			Expression* expr = expression();
			consume( CLOSE_PAREN, "Expect ')' after expression.");
			return new GroupingExpr( expr );
		}
	}

	// ?
	template<typename... Types>
	bool match( Types... types )
	{
		bool result = false;

		( ( result = result || check( types ) ), ... );
		
		if ( result ) advance();

		return result;
	}

	bool check( TokenType type )
	{
		if ( isAtEnd() ) return false;
		return peek().type == type;
	}

	Token advance()
	{
		if ( !isAtEnd() ) m_current++;
		return previous();
	}

	bool isAtEnd()
	{
		return peek().type == TOKEN_EOF;
	}

	Token peek()
	{
		return m_tokens[m_current];
	}

	Token previous()
	{
		return m_tokens[m_current - 1];
	}

	Token consume( TokenType type, const std::string& message )
	{
		if ( check( type ) ) return advance();
	}

private:

	std::vector<Token> m_tokens;
	size_t m_current = 0;
};

