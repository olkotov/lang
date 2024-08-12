// Oleg kotov

#pragma once

#include "token_type.h"
#include "token.h"

#include <unordered_map>
#include <string>

std::unordered_map<std::string, TokenType> keywords = {

	{ "var",   KEYWORD_VAR   },
	{ "print", KEYWORD_PRINT },
	{ "true",  KEYWORD_TRUE  },
	{ "false", KEYWORD_FALSE },
	{ "nil",   KEYWORD_NULL  }
};

class Scanner
{
public:

	Scanner( const std::string& input ) 
		: m_input( input )
		, m_start( 0 )
		, m_current( 0 )
		, m_line( 1 )
	{}

	std::vector<Token> tokenize()
	{
		while ( !isAtEnd() )
		{
			m_start = m_current;
			scanToken();
		}

		m_tokens.push_back( Token( TOKEN_EOF, "", nullptr, m_line ) );
		return m_tokens;
	}

private:

	void scanToken()
	{
		char c = advance();

		switch ( c )
		{
			case '(': addToken( OPEN_PAREN ); break;
			case ')': addToken( CLOSE_PAREN ); break;
			// case '-': addToken( MINUS ); break; // not here, because -- comment
			case '+': addToken( PLUS ); break;
			case '*': addToken( STAR ); break;
			case '/': addToken( SLASH ); break;

			case '!':
				addToken( match( '=' ) ? BANG_EQUAL : BANG );
				break;
			case '=':
				addToken( match( '=' ) ? EQUAL_EQUAL : EQUAL );
				break;
			case '<':
				addToken( match( '=' ) ? LESS_EQUAL : LESS );
				break;
			case '>':
				addToken( match( '=' ) ? GREATER_EQUAL : GREATER );
				break;
			case '-':
				if ( match( '-' ) )
				{
					// A comment goes until the end of the line.
					while ( peek() != '\n' && !isAtEnd() ) advance();
				}
				else
				{
					addToken( MINUS );
				}

			// ignore whitespace
			case ' ':
			case '\r':
			case '\t':
				break;

			case '\n':
				m_line++;
				break;

			case '\'': string(); break;
			case '"': string(); break;

			default:
				
				if ( isDigit( c ) )
				{
					number();
				}
				else if ( isLetter( c ) )
				{
					identifier();
				}
				else
				{
					// unexpected character
				}

				break;
		}
	}

	void addToken( TokenType type, const std::any& a_literal )
	{
		std::string text = m_input.substr( m_start, m_current - m_start );
		m_tokens.push_back( Token( type, text, a_literal, m_line ) );
	}

	void addToken( TokenType type )
	{
		addToken( type, nullptr );
	}

	// checkers

	bool isAtEnd()
	{
		return m_current >= m_input.length();
	}

	bool isWhitespace( char c )
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}

	bool isLetter( char c )
	{
		return ( c >= 'a' && c <= 'z' ) || 
			   ( c >= 'A' && c <= 'Z' ) || 
			     c == '_';
	}

	bool isDigit( char c )
	{
		return c >= '0' && c <= '9';
	}

	bool isLetterOrNumeric( char c )
	{
		return isLetter( c ) || isDigit( c );
	}

	// utils

	char advance()
	{
		return m_input[m_current++];
	}

	bool match( char expected )
	{
		if ( isAtEnd() ) return false;
		if ( m_input[m_current] != expected ) return false;

		m_current++;
		return true;
	}

	char peek()
	{
		if ( isAtEnd() ) return '\0';
		return m_input[m_current];
	}

	char peekNext()
	{
		if ( m_current + 1 >= m_input.length() ) return '\0';
		return m_input[m_current + 1];
	}

	// readers

	void string()
	{
		while ( peek() != '"' && peek() != '\'' && !isAtEnd() )
		{
			if ( peek() == '\n' ) m_line++;
			advance();
		}

		if ( isAtEnd() )
		{
			printf( "unterminated string\n" );
			return;
		}

		// The closing ".
		advance();

		// Trim the surrounding quotes.
		std::string value = m_input.substr( m_start + 1, m_current - m_start - 2 ); // 2?
		addToken( STRING, value );
	}

	void number()
	{
		while ( isDigit( peek() ) ) advance();

		// Look for a fractional part.
		if ( peek() == '.' && isDigit( peekNext() ) )
		{
			// Consume the "."
			advance();

			while ( isDigit( peek() ) ) advance();
		}

		addToken( NUMBER, std::stof( m_input.substr( m_start, m_current - m_start ) ) );
	}

	void identifier()
	{
		while ( isLetterOrNumeric( peek() ) ) advance();

		std::string text = m_input.substr( m_start, m_current - m_start );
		auto it = keywords.find( text );
		TokenType type = ( it != keywords.end() ) ? it->second : IDENTIFIER;
		addToken( type );
	}

	std::string readIdentifier()
	{
		size_t start = m_current;

		while ( m_current < m_input.length() && ( isLetter( m_input[m_current] ) || isDigit( m_input[m_current] ) ) )
		{
			m_current++;
		}

		return m_input.substr( start, m_current - start );
	}

	std::string readNumber()
	{
		size_t start = m_current;

		while ( m_current < m_input.length() && isDigit( m_input[m_current] ) )
		{
			m_current++;
		}

		return m_input.substr( start, m_current - start );
	}

private:

	std::vector<Token> m_tokens;

	std::string m_input;
	
	size_t m_start;
	size_t m_current;
	size_t m_line;
};

