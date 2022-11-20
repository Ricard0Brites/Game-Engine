#pragma once
#include "..\Object\Actor.h"
#include "..\Logger\Logger.h"

class Actor;

class Vector
{
public:
	Vector();
	~Vector();

	float X = 0,
		  Y = 0,
	 	  Z = 0;

	//Returns a copy of an up vector (0,0,1) and , optionally, applies to self
	Vector UpVector(bool ApplyToSelf);
	//Returns a copy of a forward vector (0,1,0) and , optionally, applies to self
	Vector ForwardVector(bool ApplyToSelf);
	//Returns a copy of a right vector (1,0,0) and , optionally, applies to self
	Vector RighVector(bool ApplyToSelf);
	//Returns a copy of a zero vector (0,0,0) and , optionally, applies to self
	Vector Zero(bool ApplyToSelf);
	//Fills the vector with the provided float
	void Fill(float Payload);
	// Returns a copy of a custom made Vector
	static Vector CreateVector(float PayloadX, float PayloadY, float PayloadZ) { Vector* temp = new Vector; temp->X = PayloadX; temp->Y = PayloadY; temp->Z = PayloadZ; return *temp; };

	//operators ----------------------------

	//vector
	Vector operator=(const Vector a){ X = a.X, Y = a.Y, Z = a.Z; return *this; };

	Vector operator+=(const Vector a){ X+=a.X, Y+=a.Y, Z+=a.Z; return *this; };
	Vector operator-=(const Vector a){ X-=a.X, Y-=a.Y, Z-=a.Z; return *this; };
	Vector operator*=(const Vector a){ X*=a.X, Y*=a.Y, Z*=a.Z; return *this; };
	Vector operator/=(const Vector a){ X/=a.X, Y/=a.Y, Z/=a.Z; return *this; };
	
	Vector operator+(const Vector a) { Vector temp; temp.X = X + a.X, temp.Y = Y + a.Y, temp.Z = Z + a.Z; return temp;};
	Vector operator-(const Vector a) { Vector temp; temp.X = X - a.X, temp.Y = Y - a.Y, temp.Z = Z - a.Z; return temp; };
	Vector operator*(const Vector a) { Vector temp; temp.X = X * a.X, temp.Y = Y * a.Y, temp.Z = Z * a.Z; return temp; };
	Vector operator/(const Vector a) { Vector temp; temp.X = X / a.X, temp.Y = Y / a.Y, temp.Z = Z / a.Z; return temp; };

	//float
	Vector operator=(float a) { X = a, Y = a, Z = a; return *this; };

	Vector operator+=(float a) { X += a, Y += a, Z += a; return *this; };
	Vector operator-=(float a) { X -= a, Y -= a, Z -= a; return *this; };
	Vector operator*=(float a){ X*=a, Y*=a, Z*=a; return *this; };
	Vector operator/=(float a){ X/=a, Y/=a, Z/=a; return *this; };

	Vector operator+(float a){ Vector temp;  temp.X = X + a, temp.Y = Y + a, temp.Z = Z + a; return temp; };
	Vector operator-(float a) { Vector temp;  temp.X = X - a, temp.Y = Y - a, temp.Z = Z - a; return temp; };
	Vector operator*(float a) { Vector temp;  temp.X = X * a, temp.Y = Y * a, temp.Z = Z * a; return temp; };
	Vector operator/(float a) { Vector temp;  temp.X = X / a, temp.Y = Y / a, temp.Z = Z / a; return temp; };

	//bool
	bool operator==(const Vector a){ if( Y == a.Y && Z == a.Z && X == a.X ) return true; return false; }
	bool operator!=(const Vector a){ if( Y != a.Y || Z != a.Z || X != a.X ) return true; return false; }

};

class Transform
{
public:
	Transform();
	~Transform();

	// whether this transform is relative to a parent or not
	bool IsRelative = false;

	void SetLocation(Vector NewLocation) {_Location = NewLocation; }
	void SetRotation(Vector NewRotation) { _Rotation = NewRotation; }
	void SetScale(Vector NewScale) { _Scale = NewScale; }

// World --------------------------
	// Returns a copy of World location
	Vector GetLocation();
	// Returns a copy of World rotation
	Vector GetRotation();
	// Returns a copy of World Scale
	Vector GetScale();

// Relative --------------------------
	// Returns a copy of Relativelocation
	Vector GetRelativeLocation();
	// Returns a copy of Relative rotation
	Vector GetRelativeRotation();
	// Returns a copy of Relative Scale
	Vector GetRelativeScale();

	//Dirtyness
	bool GetIsLocationMarkedDirty() { return _IsLocationDirty; }
	bool GetIsRotationMarkedDirty() { return _IsRotationDirty; }
	bool GetIsScaleMarkedDirty() { return _IsScaleDirty; }

	void MarkLocationDirty(bool isDirty) { _IsLocationDirty = isDirty; }
	void MarkRotationDirty(bool isDirty) { _IsRotationDirty = isDirty; }
	void MarkScaleDirty(bool isDirty) { _IsScaleDirty = isDirty; }

private:
	Vector _Location, _Rotation, _Scale;
	bool _IsLocationDirty, _IsRotationDirty, _IsScaleDirty;

	Transform operator=(const Transform a) { _Location = a._Location, _Rotation = a._Rotation, _Scale = a._Scale, IsRelative = a.IsRelative; return *this; };
};