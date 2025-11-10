#include "Precompiled.h"
using namespace GER::DDD;

void Mesh::CalculateBounds()
{
	_SphereBound = Sphere(_Vertices);
	_BoxBound = Box(_Vertices);
}
