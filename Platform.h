#pragma once
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>

class Platform {
public:
	 Platform();
	 ~Platform();

	 float width = 4.0f;
	 float length = 10.0f;
	 float pos_y = 0.0f;
	 float pos_x = 0.0f;
	 float pos_z = 0.0f;
	 int upper_bound = 0.0f;
	 int lower_bound = 0.0f;
	 glm::vec3 color = {};

	 static int random_color();
	 glm::vec3 platform_color(int random_color);

	 const glm::vec3 blue = { 0, 0, 1 };
	 const glm::vec3 red = { 1, 0, 0 };
	 const glm::vec3 yellow = { 1, 1, 0 };
	 const glm::vec3 orange = { 1, 0.5, 0 };
	 const glm::vec3 green = { 0, 1, 0 };
	 const glm::vec3 purple = {0.33, 0.09, 0.30};

};
