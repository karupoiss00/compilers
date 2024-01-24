#pragma once
#include "IExpression.h"

class BinaryExpression : public IExpression
{
public:
	BinaryExpression(IExpressionPtr lhs, IExpressionPtr rhs, char operatorCh);

	double Eval() override;

private:
	IExpressionPtr m_rhs;
	IExpressionPtr m_lhs;
	char m_operator;
};