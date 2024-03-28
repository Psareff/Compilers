
// Generated from expr.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "exprParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by exprParser.
 */
class  exprListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterExpr(exprParser::ExprContext *ctx) = 0;
  virtual void exitExpr(exprParser::ExprContext *ctx) = 0;


};

