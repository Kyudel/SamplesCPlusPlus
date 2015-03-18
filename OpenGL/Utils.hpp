/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <SFML\System\Vector3.hpp>

using sf::Vector3f;

namespace GraphicLibrary
{
	/**
	* Retrieves the cross product of the specified vectors to get a perpendicular vector.
	* @param vec1 - specified vectorA
	* @param vec2 - specified vectorB
	* @return Cross product of the specified vectors
	*/
	Vector3f CrossProduct( Vector3f vec1, Vector3f vec2 )
	{
		return Vector3f(vec1.y*vec2.z - vec1.z*vec2.y,
						vec1.z*vec2.x - vec1.x*vec2.z,
						vec1.x*vec2.y - vec1.y*vec2.x);
	}
	
	/**
	* Retrieves the length of the vector.
	* @param vec - specified vectorA
	* @return length of the specified vector.
	*/
	float Magnitude( Vector3f vec )
	{
		return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	}

	/**
	* Retrieves a specified vector with a magnitude of 1.
	* @param vec1 - specified vector
	* @return normalized vector
	*/
	Vector3f Normalize( Vector3f vec )
	{
		float magnitude = Magnitude(vec);

		vec.x /= magnitude;
		vec.y /= magnitude;
		vec.z /= magnitude;

		return vec;
	}
}

#endif