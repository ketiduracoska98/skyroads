#include "Platform.h"

Platform::Platform()
{
}

Platform::~Platform()
{
}

int Platform::random_color()
{

	int color_number = 5;
	return rand() % color_number;
}

glm::vec3 Platform::platform_color(int random_color)
{
	if (random_color == 0) {
		return red;
	}
	if (random_color == 1) {
		return blue;
	}
	if (random_color == 2) {
		return green;
	}
	if (random_color == 3) {
		return orange;
	}
	if (random_color == 4) {
		return yellow;
	}
}
