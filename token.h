// Oleg Kotov

#pragma once

#include "token_type.h"

#include <string>
#include <any>
#include <sstream>
#include <iomanip>

struct Token
{
	Token( TokenType type, const std::string& lexeme, const std::any& a_literal, size_t line )
		: type( type )
		, lexeme( lexeme )
		, m_literal( a_literal )
		, line( line )
	{}

	std::string toString() const
	{
		std::stringstream ss;

		ss << "[" << std::to_string( line ) << "] ";
		ss << std::left << std::setw( 25 ) << std::setfill( ' ' ) << lexeme;
		ss << tokenTypeStrings[type];

		return ss.str();
	}

	TokenType type;
	std::string lexeme;
	std::any m_literal;
	size_t line;
};

