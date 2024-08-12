// Oleg Kotov

#pragma once

#include <any>

class Expression;

void debugPrintAny( const std::any& result );
void debugPrintAST( Expression* expr, int8_t indent = 0 );

