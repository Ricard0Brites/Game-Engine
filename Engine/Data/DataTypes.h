#pragma once

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
	Vector CreateVector(float PayloadX, float PayloadY, float PayloadZ) { Vector* temp = new Vector; temp->X = PayloadX; temp->Y = PayloadY; temp->Z = PayloadZ; return *temp; };

	//operators

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

	Vector operator+(float a){ X + a, Y + a, Z + a; return *this; };
	Vector operator-(float a){ X - a, Y - a, Z - a; return *this; };
	Vector operator*(float a){ X * a, Y * a, Z * a; return *this; };
	Vector operator/(float a){ X / a, Y / a, Z / a; return *this; };

	//bool
	bool operator==(Vector a){ if( Y == a.Y && Z == a.Z && X == a.X ) return true; return false; }
	bool operator!=(Vector a){ if( Y != a.Y || Z != a.Z || X != a.X ) return true; return false; }

};