#include <stdexcept>
#include <format>
#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(IExpressionPtr lhs, IExpressionPtr rhs, char operatorCh)
	: m_rhs(rhs)
	, m_lhs(lhs)
	, m_operator(operatorCh)
{

}

double BinaryExpression::Eval() 
{
	double leftValue = m_lhs->Eval();
	double rightValue = m_rhs->Eval();

	switch (m_operator)
	{
	case '+':
		return leftValue + rightValue;
	case '-':
		return leftValue - rightValue;
	case '*':
		return leftValue * rightValue;
	case '/':
		if (rightValue == 0)
		{
			throw std::logic_error("division by zero");
		}
		return leftValue / rightValue;
	default:
		auto msg = std::format("unknown binary operator \'{}\'", m_operator);
		throw std::invalid_argument(msg);
	}
}