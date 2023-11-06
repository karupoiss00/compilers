#include <memory>
#include <catch2/catch.hpp>

template <typename T>
class IBaseExpectationWithBoolResult
{
public:
	virtual bool toEqualImpl(T value) const = 0;

	virtual ~IBaseExpectationWithBoolResult(){};
};

template <typename T>
class IBaseExpectationWithAssertion
{
public:
	virtual void toEqual(T value) const = 0;

	virtual ~IBaseExpectationWithAssertion(){};
};

template <typename T>
class InvertedExpectation : protected IBaseExpectationWithBoolResult<T>
	, public IBaseExpectationWithAssertion<T>
{
public:
	InvertedExpectation(IBaseExpectationWithBoolResult<T>* _invertable)
		: invertable(_invertable)
	{
	}

	void toEqual(T value) const override
	{
		REQUIRE(toEqualImpl(value));
	}

protected:
	bool toEqualImpl(T value) const override
	{
		return !invertable->toEqualImpl(value);
	}

private:
	IBaseExpectationWithBoolResult<T>* invertable;
};

template <typename T>
class Expectation : protected IBaseExpectationWithBoolResult<T>
	, public IBaseExpectationWithAssertion<T>
{

public:
	Expectation(T value)
		: m_value(value)
		, isNot(nullptr)
	{
		isNot = new InvertedExpectation(this);
	}

	~Expectation()
	{
		delete isNot;
	}

	void toEqual(T value) const
	{
		REQUIRE(toEqualImpl(value));
	}

	IBaseExpectationWithAssertion<T>* isNot;

protected:
	virtual bool toEqualImpl(T value) const override
	{
		return value == m_value;
	}

	T m_value;
};

template <typename T>
std::shared_ptr<Expectation<T>> expect(T value)
{
	return std::make_shared<Expectation<T>>(value);
}