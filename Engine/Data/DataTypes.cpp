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
}

Transform::~Transform()
{
	delete &Location;
	delete &Rotation;
	delete &Scale;
	if(Owner) delete &Owner; // the owner cannot exist without its transform
}

void Transform::SetOwner(Actor* NewOwner)
{
	if (Owner)	Owner = NewOwner;
	else
	{
		LOG("Trying to set a new owner but the given reference is null..." FUNCTIONNAME " " FILENAME, 3);
	}
}

Vector Transform::GetWorldLocation()
{
	if(!IsRelative) return Location;

	//return reinterpret_cast<Actor*>(Owner)->GetTransform()->Location + this->Location;
	return Owner->GetTransform()->Location + this->Location;
}

Vector Transform::GetWorldRotation()
{
	if (!IsRelative) return Rotation;

	return Owner->GetTransform()->Rotation+ this->Rotation;
}

Vector Transform::GetWorldScale()
{
	if (!IsRelative) return Scale;

	return Owner->GetTransform()->Scale+ this->Scale;
}

Vector Transform::GetRelativeLocation()
{
	//if its relative the value is location
	//if its not relative the value is still the same (relative to the world AKA world location)
	return Location;
}

Vector Transform::GetRelativeRotation()
{
	return Rotation;
}

Vector Transform::GetRelativeScale()
{
	return Scale;
}
