#include "DataTypes.h"

Vector::Vector()
{

}

Vector::~Vector()
{

}

Vector Vector::UpVector(bool ApplyToSelf)
{
	if(!ApplyToSelf) return Vector::CreateVector(0,0,1);

	*this = Vector::CreateVector(0,0,1);
	return *this;
}

Vector Vector::ForwardVector(bool ApplyToSelf)
{
	if (!ApplyToSelf) return Vector::CreateVector(0, 1, 0);

	*this = Vector::CreateVector(0, 1, 0);
	return *this;
}

Vector Vector::RighVector(bool ApplyToSelf)
{
	if (!ApplyToSelf) return Vector::CreateVector(1, 0, 0);

	*this = Vector::CreateVector(1, 0, 0);
	return *this;
}

Vector Vector::Zero(bool ApplyToSelf)
{
	if (!ApplyToSelf) return Vector::CreateVector(0, 0, 0);

	*this = Vector::CreateVector(0, 0, 0);
	return *this;
}

void Vector::Fill(float Payload)
{
	*this = Payload;
}
