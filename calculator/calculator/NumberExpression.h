#pragma once
#include "IExpression.h"

class NumberExpression : public IExpression
{
public:
	NumberExpression(double value)
		: m_value(value)
	{
	}

	double Eval() override
	{
		return m_value;
	}

private:
	double m_value;
};
