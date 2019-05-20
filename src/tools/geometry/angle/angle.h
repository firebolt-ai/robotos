#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>

class Angle {
    public: Angle();
	Angle( float phi, bool degrees = false );
	float phi();
	void setPhi( float phi );
	float degrees();
	void reverse();
	Angle deltaAngle( Angle phi );
	friend std::ostream & operator << ( std::ostream & output, const Angle & a );

 private:
	float
		_phi;
};

#endif
