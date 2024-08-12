// Oleg Kotov

#include "expression.h"

bool isTruthy( const std::any& object )
{
	if ( object.type() == typeid( std::nullptr_t ) ) return false;
	if ( object.type() == typeid( bool ) ) return std::any_cast<bool>( object );
	return true;
}

bool isEqual( const std::any& a, const std::any& b )
{
	if ( a.has_value() && b.has_value() )
	{
		if ( a.type() == b.type() )
		{
			if ( a.type() == typeid( bool ) )
			{
				return std::any_cast<bool>( a ) == std::any_cast<bool>( b );
			}
			else if ( a.type() == typeid( std::string ) )
			{
				return std::any_cast<std::string>( a ) == std::any_cast<std::string>( b );
			}
			else if ( a.type() == typeid( float ) )
			{
				return std::any_cast<float>( a ) == std::any_cast<float>( b );
			}
		}
	}

	else if ( !a.has_value() && !b.has_value() )
	{
		return true;
	}

	else if ( a.type() == typeid( std::nullptr_t ) && !b.has_value() )
	{
		return true;
	}

	else if ( b.type() == typeid( std::nullptr_t ) && !a.has_value() )
	{
		return true;
	}

	return false;
}

