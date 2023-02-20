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
	static Vector CreateVector(float PayloadX, float PayloadY, float PayloadZ) { Vector vec; vec.X = PayloadX; vec.Y = PayloadY; vec.Z = PayloadZ; return vec; };

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


	// Returns a copy of World location
	Vector GetLocation();
	// Returns a copy of World rotation
	Vector GetRotation();
	// Returns a copy of World Scale
	Vector GetScale();

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

enum InputKeyCodes
{
	// Keyboard Buttons
	K_a,
	K_b, 
	K_c, 
	K_d, 
	K_e, 
	K_f, 
	K_g, 
	K_h, 
	K_i, 
	K_j, 
	K_k, 
	K_l, 
	K_m, 
	K_n, 
	K_o, 
	K_p, 
	K_q, 
	K_r, 
	K_s, 
	K_t, 
	K_u, 
	K_v, 
	K_w, 
	K_x, 
	K_y, 
	K_z,
	
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,


	K_0,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,

	K_Num0,
	K_Num1,
	K_Num2,
	K_Num3,
	K_Num4,
	K_Num5,
	K_Num6,
	K_Num7,
	K_Num8,
	K_Num9,

	K_Up,
	K_Left,
	K_Down,
	K_Right,
	K_Space,

	// gamepad buttons
	GamepadFaceRight,
	GamepadFaceLeft,
	GamepadFaceBottom,
	GamepadFaceTop,
	GamepadArrowLeft,
	GamepadArrowRight,
	GamepadArrowBottom,
	GamepadArrowTop,
	GamepadLeftStickPress,
	GamepadRightStickPress,
	GamepadSpecialLeft,
	GamepadSpecialRight,
	GamepadLeftButton,
	GamepadRightButton,

	// axis 
	GamepadLeftTrigger,
	GamepadRightTrigger,
	GamepadStickRight,
	GamepadStickLeft,

	// Null
	Null
};