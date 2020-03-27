#pragma once
#include "Object.h"
class EmptySpace :
	public Object
{
public:
	EmptySpace()
		: Object(eObjType::EmptySpace, { 0,0 }, { 0, 0 }) {};
	// These 0's mean nothing as this object is used just to fill the playfield with something.
	void Step(float dt) { };
};

