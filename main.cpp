// Oleg Kotov

#include "scanner.h"
#include "parser.h"
#include "utils.h"

#include <string>

int main()
{
	std::string source = "( 2.0 + 3.0 ) * ( 12.0 / 2.0 )";
	// source = "2.0 + 3.0 * 12.0 / 2.0";

	printf( "\n" );
	printf( "%s\n", source.c_str() );
	printf( "\n" );

	// source code to token list
	Scanner scanner( source );
	std::vector<Token> tokens = scanner.tokenize();

	for ( const auto& token : tokens )
	{
		printf( "%s\n", token.toString().c_str() );
	}

	printf( "\n" );

	// token list to AST
	Parser parser( tokens );
	Expression* expression = parser.parse();

	printf( "\n" );
	debugPrintAST( expression );
	printf( "\n" );

	// evaluate AST
	std::any result = expression->evaluate();

	printf( "final: " );
	debugPrintAny( result );
	printf( "\n" );

	return 0;
}

