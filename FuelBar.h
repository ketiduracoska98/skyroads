#pragma once

#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include "Transform3D.h"

class FuelBar
{
public:

	static Mesh* CreateBackground();
	static Mesh* CreateFuelBar();
	static Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices,
		const std::vector<GLushort>& indices);
};