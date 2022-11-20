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
	delete &_Location;
	delete &_Rotation;
	delete &_Scale;
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

Vector Transform::GetRelativeLocation()
{
	//if its relative the value is location
	//if its not relative the value is still the same (relative to the world AKA world location)
	return _Location;
}

Vector Transform::GetRelativeRotation()
{
	return _Rotation;
}

Vector Transform::GetRelativeScale()
{
	return _Scale;
}
