#pragma once
#include <memory>

class IExpression
{
public:
	virtual double Eval() = 0;
};

using IExpressionPtr = std::shared_ptr<IExpression>;