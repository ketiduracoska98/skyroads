#pragma once
#include "FuelBar.h"
Mesh* FuelBar::CreateBackground()
{
	Mesh* background = nullptr;
	/*
	*	Create vertex and index for a background of the fuel bar
	*/
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
		VertexFormat(glm::vec3(3.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
		VertexFormat(glm::vec3(3.f, .5f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
		VertexFormat(glm::vec3(0.f, .5f, 0.f), glm::vec3(1.f, 1.f, 1.f)),
	};
	std::vector<GLushort> indices ={ 0, 1, 2, 0, 2, 3};
	background = CreateMesh("background", vertices, indices);
	return background;
}

Mesh* FuelBar::CreateFuelBar()
{
	Mesh* fuel_bar = nullptr;
	/*
	*	Create the vertex and index for a fuel bar
	*/
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.5f, 0.f)),
		VertexFormat(glm::vec3(3.f, 0.f, 0.f), glm::vec3(0.f, 0.5f, 0.f)),
		VertexFormat(glm::vec3(3.f, .5f, 0.f), glm::vec3(0.f, 0.5f, 0.f)),
		VertexFormat(glm::vec3(0.f, .5f, 0.f), glm::vec3(0.f, 0.5f, 0.f)),
	};

	std::vector<GLushort> indices = { 0, 1, 2, 0, 2, 3};
	fuel_bar = CreateMesh("fuel_bar", vertices, indices);
	return fuel_bar;
}

Mesh* FuelBar::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<GLushort>& indices)
{
	unsigned int VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);

	CheckOpenGLError();

	Mesh* mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<GLushort>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;

	return mesh;
}

