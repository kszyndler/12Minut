#include "StdAfx.h"
#include "SceneObject.h"

// Uniwersalny konstruktor, ustawia podstawowe rzeczy.
CSceneObject::CSceneObject(void)
{
	Position.Set(0.0f, 0.0f, 0.0f);
	Rotation.Set(0.0f, 0.0f, 0.0f);
	Name = "unnamedObject";
}

// Destruktor - sprz¹tamy po sobie.
CSceneObject::~CSceneObject(void)
{
}
