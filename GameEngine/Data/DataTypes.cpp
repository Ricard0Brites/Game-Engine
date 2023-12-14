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


string Vector::ToString()
{
	string StringToReturn = "";

	StringToReturn += "X=" + to_string(X);
	StringToReturn += "Y=" + to_string(Y);
	StringToReturn += "Z=" + to_string(Z);

	return StringToReturn;
}

// Transform ---------------------------------------------------

Transform::Transform()
{
	_Location = 0;
	_Rotation = 0;
	_Scale = 1;
	_IsLocationDirty = false;
	_IsRotationDirty = false;
	_IsScaleDirty = false;
}

Transform::~Transform()
{
}

Vector Transform::GetLocation()
{	
	return _Location;
}

Vector Transform::GetRotation()
{
	 return _Rotation;
}

Vector Transform::GetScale()
{
	return _Scale;
}