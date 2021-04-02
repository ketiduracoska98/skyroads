#pragma once
#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <include/glm.h>
#include <include/math.h>
#include<ctime>
#include "Camera.h"
#include "Platform.h"


class Tema2 : public SimpleScene {
public:
	Tema2();
	~Tema2();
	void Init() override;
private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color_vector, bool orange_platform);
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void SetCamera();
	void CreateMeshes();
	void CreateShaders();
	void CreatePlatforms();
	void CheckFuel();
	void FastMode();
	void DrawSphere(glm::mat4 modelMatrix);
	void DrawFuelBar(glm::mat4 modelMatrix);
	void Falling();
	void DrawPlarform(glm::mat4 modelMatrix, std::vector<Platform> platform_vector, glm::vec3 color, int i);
	void RedPlatform();
	void YellowPlatform(float deltaTimeSeconds);
	void GreenPlatform(float deltaTimeSeconds);
	void OrangePlatform();


protected:
	Cam::Camera* camera = nullptr;
	glm::mat4 projectionMatrix;
	int cameraType = 1;
	const float one = 1.0f;
	const float two = 2.0f;

	/*
	*	at the beginning, rend 20 platforms at diffrent positions on x-axis
	*/
	int nr_of_platforms = 20;
	float platform1_pos_x = 4.0f;
	float platform2_pos_x = 0.0f;
	float platform3_pos_x = -4.0f;

	float left_end = 0.0f;
	float right_end = 0.0f;

	int len = 3;

	/*
	*	position of the sphere
	*/
	float sphere_x = 0.0f;
	float sphere_y = 0.5f;
	float sphere_z = 1.0f;
	float sphere_radius = 1.5f;
	float sphere_fall = -12.0f;
	float falling_distance = 2.0f;
	float falling_speed = 0.1f;
	bool fall = true;
	glm::vec3 cyan = { 0, 1, 1 };

	/*
	*	speed variables
	*/
	float speed = 1.0f;
	float max_speed = 6.0f; 
	float med_speed = (max_speed + 1) / 2.0f;
	float min_speed = 0.2f;
	float stop_speed = 0.0f;
	float speed_munis = 0.8f;
	float speed_plus = 0.5f;

	/*
	*	jump variables
	*/
	float jump = 1.0f;
	float max_jump = 7.0f;
	bool space_pressed = false;
	float x_move = 4.0f;

	/*
	*	fuel variables
	*/
	float fuel_x = -9.5f;
	float fuel_y = 6.0f;
	float scale_bar = 1.0f;
	float no_fuel = 0.0f;
	float fuel_minus = 0.0001;
	float scale_bar_const = 0.05f;

	/*
	*	measure the time
	*/
	clock_t begin = 0.0f;
	clock_t end = 0.0f;

	bool ornage_platform = false;
	float diff = 501.0f;
	float max_diff = 501.0f;
	/*
	*	Create 3 vectors of platform object
	*/
	Platform platform;
	std::vector<Platform> platform1_vector;
	std::vector<Platform> platform2_vector;
	std::vector<Platform> platform3_vector;
	
	Texture2D *texture = nullptr;
};

