// Oleg Kotov

#include "utils.h"
#include "expression.h"

#include <string>
#include <iostream>

void debugPrintAny( const std::any& result )
{
	if ( result.has_value() )
	{
		if ( result.type() == typeid( bool ) )
		{
			bool boolResult = std::any_cast<bool>( result );
			std::cout << "(bool): " << ( boolResult ? "true" : "false" ) << std::endl;
		}
		else if ( result.type() == typeid( std::string ) )
		{
			std::string stringResult = std::any_cast<std::string>( result );
			std::cout << "(string): " << stringResult << std::endl;
		}
		else if ( result.type() == typeid( int ) )
		{
			int intResult = std::any_cast<int>( result );
			std::cout << "(int): " << intResult << std::endl;
		}
		else if ( result.type() == typeid( float ) )
		{
			float floatResult = std::any_cast<float>( result );
			std::cout << "(float): " << floatResult << std::endl;
		}
		else if ( result.type() == typeid( std::nullptr_t ) )
		{
			std::cout << "(nullptr)" << std::endl;
		}
	}
	else
	{
		std::cout << "has not value" << std::endl;
	}
}

void debugPrintAST( Expression* expr, int8_t indent /* = 0 */ )
{
	if ( !expr ) return;

	for ( int8_t i = 0; i < indent; ++i )
	{
		printf( "  " );
	}

	// print node info
	if ( LiteralExpr* literal = dynamic_cast<LiteralExpr*>( expr ) )
	{
		printf( "Literal: " );
		debugPrintAny( literal->value );
	}
	else if ( BinaryExpr* binary = dynamic_cast<BinaryExpr*>( expr ) )
	{
		printf( "Binary: %s\n", binary->op.toString().c_str() );

		// recursive call for left and right operand
		debugPrintAST( binary->left, indent + 1 );
		debugPrintAST( binary->right, indent + 1 );
	}
	else if ( GroupingExpr* grouping = dynamic_cast<GroupingExpr*>( expr ) )
	{
		printf( "Grouping\n" );

		// recursive call for internal expression
		debugPrintAST( grouping->value, indent + 1 );
	}
}

