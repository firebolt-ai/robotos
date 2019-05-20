#include "vol.h"
#include "../coordinates.h"


VolumeCoordinate::VolumeCoordinate()
	:Coordinate::Coordinate()
{
	this->_z = 0;
}

VolumeCoordinate::VolumeCoordinate( float x, float y, float z )
	:Coordinate::Coordinate( x, y )
{
	this->_z = z;
}

float
VolumeCoordinate::z()
{
	return this->_z;
}

std::ostream & operator << ( std::ostream & output, const VolumeCoordinate & vc )
{
	output << (Coordinate) vc << "," << vc._z;
	return output;
}