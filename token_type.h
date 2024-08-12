// Oleg Kotov

#pragma once

#include <unordered_map>
#include <string>

enum TokenType
{
	// keywords
	KEYWORD_VAR,
	KEYWORD_PRINT,
	KEYWORD_TRUE,
	KEYWORD_FALSE,
	KEYWORD_NULL,

	// literals
	IDENTIFIER,
	NUMBER,
	STRING,

	// symbols
	BANG,                    // !
	BANG_EQUAL,              // !=
	EQUAL_EQUAL,             // ==
	GREATER,                 // >
	GREATER_EQUAL,           // >=
	LESS,                    // <
	LESS_EQUAL,              // <=

	EQUAL,                   // "="
	OPEN_PAREN,              // "("
	CLOSE_PAREN,             // ")"
	PLUS,                    // "+"
	MINUS,                   // "-"
	STAR,                    // "*"
	SLASH,                   // "/"

	QUOTE_DOUBLE,            // "
	QUOTE_SINGLE,            // '

	// other
	TOKEN_EOF,
	UNKNOWN
};

extern std::unordered_map<TokenType, std::string> tokenTypeStrings;

