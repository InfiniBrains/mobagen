#pragma once
// todo: crate vector2, 3 and 4 as template
/*
#include <cstdint>

template<typename containerType, size_t size>
struct Vector
{
private:
	containerType data_[size];
public:
	// todo: derived classes must implement specialized constructors and set functions

	Vector<containerType, size>() = default;

	// data element
	virtual containerType & operator [](uint32_t i);
	virtual containerType & operator [](int32_t i);

	// accept
	virtual Vector<containerType, size> operator = (const Vector<containerType, size>& other) const;

	// math
	virtual Vector<containerType, size> operator + (const Vector<containerType, size>& other) const;
	virtual Vector<containerType, size> operator - (const Vector<containerType, size>& other) const;
	virtual Vector<containerType, size> operator * (const containerType& a, const Vector<containerType, size>& b) const;
	virtual Vector<containerType, size> operator * (const Vector<containerType, size>& a, const containerType& b) const;
	virtual Vector<containerType, size> operator / (const containerType& other) const;

	// operator attrib
	virtual Vector<containerType, size> operator += (const Vector<containerType, size>& other) const;
	virtual Vector<containerType, size> operator -= (const Vector<containerType, size>& other) const;
	virtual Vector<containerType, size> operator *= (const containerType& other) const;
	virtual Vector<containerType, size> operator /= (const containerType& other) const;

	// operator equals
	virtual Vector<containerType, size> operator == (const Vector<containerType, size>& other) const;
	virtual Vector<containerType, size> operator != (const Vector<containerType, size>& other) const;

	// properties
	virtual Vector<containerType, size> Magnitude();
	virtual Vector<containerType, size> Normalized();
	virtual Vector<containerType, size> SqrMagnitude();

	// static methods
	static containerType Angle(Vector<containerType, size> from, Vector<containerType, size> to);
	static containerType SignedAngle(Vector<containerType, size> from, Vector<containerType, size> to, Vector<containerType, size> axis);
	static Vector<containerType, size> ClampMagnitude(Vector<containerType, size> vector, containerType maxLength);
	static Vector<containerType, size> Cross(Vector<containerType, size> other);
	//virtual Vector<containerType, size> Distance(Vector<containerType, size> other);
	//virtual containerType Dot(Vector<containerType, size> other);
	//virtual Vector<containerType, size> Lerp(Vector<containerType, size> other, containerType interpolant);
	//virtual Vector<containerType, size> LerpUnclamped(Vector<containerType, size> other, containerType interpolant);
	//virtual Vector<containerType, size> Max(Vector<containerType, size> other);
	//virtual Vector<containerType, size> Min(Vector<containerType, size> other);
	//virtual Vector<containerType, size> MoveTowards(Vector<containerType, size> target, containerType maxDistanceDelta);

	//virtual Vector<containerType, size> Normalize();
	static Vector<containerType, size> OrthoNormalize(Vector<containerType, size> * normal, Vector<containerType, size> * tangent);
	static Vector<containerType, size> OrthoNormalize(Vector<containerType, size> * normal, Vector<containerType, size> * tangent, Vector<containerType, size> * binormal);
};

*/