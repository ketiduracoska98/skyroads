#include "Tema2.h"
#include "Transform3D.h"
#include "Platform.h"
#include "FuelBar.h"

using namespace std;
Tema2::Tema2() {
}
Tema2::~Tema2() {
}

void Tema2::Init() {

	Tema2::SetCamera();
	Tema2::CreateMeshes();
	Tema2::CreateShaders();
	Tema2::CreatePlatforms();
}

void Tema2::FrameStart() {
	// clears the color buffer 
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds) {

	glm::mat4 modelMatrix;
	Tema2::CheckFuel();
	Tema2::Falling();
	Tema2::FastMode();
	Tema2::DrawSphere(modelMatrix);
	if (cameraType == 1) {
		Tema2::DrawFuelBar(modelMatrix);
	}

	int size = platform1_vector.size() - (int)one;
	int length = platform.length + len;
	
	for (int i = 0; i < platform1_vector.size(); i++) {
		/*
		* rend only the platforms between lower and upper bound 
		* check on what platform is sphere 
		* change the color of that platform to purple
		* and do the "task" for that platform: red - stop the game,
		* yellow - dicrease fuel, green - increase fuel, orange - 
		* enter the fast mode
		*/
		if (platform1_vector[i].pos_z <= length) {	
			if (i < platform1_vector[i].lower_bound || i > platform1_vector[i].upper_bound) {
				if (sphere_x > platform1_pos_x / two && jump <= one) {
					if (platform1_vector[i].pos_z > -platform.length / two && platform1_vector[i].pos_z < platform.length / two) {
						/*
						* change the color to purple
						*/
						Tema2::DrawPlarform(modelMatrix, platform1_vector, platform.purple, i);

						if (platform1_vector[i].color == platform.red) {
							Tema2::RedPlatform();
						}
						if (platform1_vector[i].color == platform.yellow) {
							Tema2::YellowPlatform(deltaTimeSeconds);
						}
						if (platform1_vector[i].color == platform.green) {
							Tema2::GreenPlatform(deltaTimeSeconds);
						}
						if (platform1_vector[i].color == platform.orange) {
							 begin = clock();
							 ornage_platform = true;
						}
					}
					else {
						/*
						* don't change the color to purple
						*/
						Tema2::DrawPlarform(modelMatrix, platform1_vector, platform1_vector[i].color, i);
					}
				}
				/*
				* sphere is not on the current platform
				*/
				else {
					Tema2::DrawPlarform(modelMatrix, platform1_vector, platform1_vector[i].color, i);
				}
			}
			else {
				/*
				* the sphere has fall
				*/
				if (platform1_vector[i].pos_z > -platform.length / two + falling_distance && platform1_vector[i].pos_z < platform.length / two) {
					if (sphere_x > platform1_pos_x / two && jump <= one) {
						speed = stop_speed;
					}
				}
			}
		}
		else {
			/*
			* create new platforms
			*/
			platform1_vector[i].pos_z = platform1_vector[size].pos_z - platform.length * (i + (int)one);
			platform1_vector[i].color = platform.platform_color(platform.random_color());
		}
		
		if (platform2_vector[i].pos_z <= length) {
			if (i < platform2_vector[i].lower_bound || i >  platform2_vector[i].upper_bound) {
				if (sphere_x < platform1_pos_x / two && sphere_x > platform3_pos_x / two && jump <= one) {
					if (platform1_vector[i].pos_z > -platform.length / two && platform2_vector[i].pos_z < platform.length / two) {

						Tema2::DrawPlarform(modelMatrix, platform2_vector, platform.purple, i);

						if (platform2_vector[i].color == platform.red) {
							Tema2::RedPlatform();
						}
						if (platform2_vector[i].color == platform.yellow) {
							Tema2::YellowPlatform(deltaTimeSeconds);
						}
						if (platform2_vector[i].color == platform.green) {
							Tema2::GreenPlatform(deltaTimeSeconds);
						}
						if (platform2_vector[i].color == platform.orange) {
							Tema2::OrangePlatform();
						}
					}
					else {
						Tema2::DrawPlarform(modelMatrix, platform2_vector, platform2_vector[i].color, i);
					}
				}
				else {
					Tema2::DrawPlarform(modelMatrix, platform2_vector, platform2_vector[i].color, i);
				}
			}
			else {
				if (platform1_vector[i].pos_z > -platform.length / two + falling_distance && platform2_vector[i].pos_z < platform.length / two) {
					if (sphere_x < platform1_pos_x / two && sphere_x > platform3_pos_x / two && jump <= one) {
						speed = stop_speed;
					}
				}
			}
		}
		else {
			platform2_vector[i].pos_z = platform2_vector[size].pos_z - platform.length * (i + (int)one);
			platform2_vector[i].color = platform.platform_color(platform.random_color());
		}
		if (platform3_vector[i].pos_z <= length) {
			if (i < platform3_vector[i].lower_bound || i > platform3_vector[i].upper_bound) {
				if (sphere_x < platform3_pos_x / two && jump <= one) {
					if (platform3_vector[i].pos_z > -platform.length / two && platform3_vector[i].pos_z < platform.length / two) {

						Tema2::DrawPlarform(modelMatrix, platform3_vector, platform.purple, i);
						if (platform3_vector[i].color == platform.red) {
							Tema2::RedPlatform();
						}
						if (platform3_vector[i].color == platform.yellow) {
							Tema2::YellowPlatform(deltaTimeSeconds);
						}
						if (platform3_vector[i].color == platform.green) {
							Tema2::GreenPlatform(deltaTimeSeconds);
						}
						if (platform3_vector[i].color == platform.orange) {
							Tema2::OrangePlatform();
						}
					}
					else {
						Tema2::DrawPlarform(modelMatrix, platform3_vector, platform3_vector[i].color, i);
					}
				}
				else {
					Tema2::DrawPlarform(modelMatrix, platform3_vector, platform3_vector[i].color, i);
				}
			}
			else {
				if (platform3_vector[i].pos_z > -platform.length / two + falling_distance && platform3_vector[i].pos_z < platform.length / two) {
					if (sphere_x < platform3_pos_x / two && jump <= one) {
						speed = stop_speed;
					}
				}
			}
		}
		else {
			platform3_vector[i].pos_z = platform3_vector[size].pos_z - platform.length * (i + (int)one);
			platform3_vector[i].color = platform.platform_color(platform.random_color());
		}
		platform1_vector[i].pos_z += deltaTimeSeconds * speed * 10;
		platform2_vector[i].pos_z += deltaTimeSeconds * speed * 10;
		platform3_vector[i].pos_z += deltaTimeSeconds * speed * 10;
		scale_bar -= fuel_minus * deltaTimeSeconds * speed;
	} 
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color_vector, bool orange_platform)
{
	if (!mesh || !shader || !shader->program) 
		return;

	glUseProgram(shader->program);
	/*
	*  get the locations of Model, View, Projection matrix of the color
	*  of the sphere or platform
	*/
	int location = glGetUniformLocation(shader->program, "Model");

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	location = glGetUniformLocation(shader->program, "View");

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	location = glGetUniformLocation(shader->program, "Projection");

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	location = glGetUniformLocation(shader->program, "our_color");
	glUniform3fv(location, 1, glm::value_ptr(color_vector));
	/*
	* the sphere was on the orange platform, the game is in fast mode
	* and the texture is changed
	*/
	if (orange_platform) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (speed != stop_speed) {
		/*
		*	while A is being hold move to the left
		*/
		if (window->KeyHold(GLFW_KEY_A)) {
			sphere_x -= x_move * deltaTime;
		}

		/*
		*	while W is being hold and speed is less than
		*	max speed, increase it
		*/
		if (window->KeyHold(GLFW_KEY_W)) {
			if (ornage_platform == false) {
				if (speed < max_speed) {
					speed += speed_plus * deltaTime;
					x_move += speed_plus * deltaTime;
				}
			}
		}

		/*
		*  while S is being hold and speed is bigger than
		*	min speed decrease it
		*/
		if (window->KeyHold(GLFW_KEY_S)) {
			if (ornage_platform == false) {
				if (speed > min_speed) {
					speed -= speed_munis * deltaTime;
					x_move -= speed_munis * deltaTime;
				}
			}
		}
		/*
		*	move the sphere to the right
		*/
		if (window->KeyHold(GLFW_KEY_D)) {
			sphere_x += x_move * deltaTime;
		}
		/*
		* sphere jumped and now has to fall back to the platforms
		*/
		if (jump > one) {
			jump -= falling_speed;
		}
		else {
			space_pressed = false;
		}
	}	
}

void Tema2::OnKeyPress(int key, int mods) {
	if (speed != stop_speed) {
		/*
		* if space is pressed increase the jump variable
		* and create the jump effect
		*/
		if (key == GLFW_KEY_SPACE) {
			if (space_pressed == false) {
				jump += max_jump;
				space_pressed = true;
			}
		}
	}

	/*
	* if C is preesed change camere between first and third person  
	*/
	if (key == GLFW_KEY_C) {
		if (cameraType == 1) {
			cameraType = 0;
			camera->Set(
				glm::vec3(0.f, 2.f, 2.f),
				glm::vec3(0.f, 1.7f, 0.f),
				glm::vec3(0.f, 1.0f, 0.f)
			);
		}
		else {
			cameraType = 1;
			camera->Set(
				glm::vec3(0, 3, 10.f), 
				glm::vec3(0, 1, 0), 
				glm::vec3(0, 1, 0));
		}
	}
}

void Tema2::SetCamera() {
	/*
	*	Set the camera
	*/
	camera = new Cam::Camera();
	camera->Set(glm::vec3(0, 3, 10.f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	cameraType = 1;
}

void Tema2::CreateMeshes() {
	/*
	*	create box mesh
	*/
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	/*
	*	create sphere mesh
	*/
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	/*
	*	 create fuel bar mesh
	*/
	{
		Mesh* background = FuelBar::CreateBackground();
		AddMeshToList(background);
	}
	{
		Mesh* fuel_bar = FuelBar::CreateFuelBar();
		AddMeshToList(fuel_bar);
	}
}

void Tema2::CreateShaders() {
	/*
	*	create shaders
	*/
	{
		Shader* shader = new Shader("MyShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SphereVertex.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SphereFragment.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader_s = new Shader("Shader_s");
		shader_s->AddShader("Source/Laboratoare/Tema2/Shaders/VertexS.glsl", GL_VERTEX_SHADER);
		shader_s->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentS.glsl", GL_FRAGMENT_SHADER);
		shader_s->CreateAndLink();
		shaders[shader_s->GetName()] = shader_s;
		/*
		*	new texture
		*/
		texture = new Texture2D();
		texture->Load2D("Source/Laboratoare/Tema2/Texture/sphere.png");
	}
}

void Tema2::CreatePlatforms() {
	/*
	*	Create 3 new platforms and set it constant values
	*/
	Platform platform1, platform2, platform3;
	platform1.pos_x = platform1_pos_x;
	platform2.pos_x = platform2_pos_x;
	platform3.pos_x = platform3_pos_x;
	/*
	* set the constants for lower and upper bound
	* between which the platforms are rend
	*/
	platform1.lower_bound = 11;
	platform1.upper_bound = 15;

	platform2.lower_bound = 16;
	platform2.upper_bound = 18;

	platform3.lower_bound = 9;
	platform3.upper_bound = 12;

	/*
	* set the random values of the platform: position on
	* z-axis and color of the platform
	*/
	for (int i = 0; i < nr_of_platforms; i++) {
		platform2.pos_z = -i * (platform.length);
		platform1.pos_z = -i * (platform.length);
		platform3.pos_z = -i * (platform.length);

		platform1.color = platform1.platform_color(platform.random_color());
		platform2.color = platform2.platform_color(platform.random_color());
		platform3.color = platform3.platform_color(platform.random_color());

		platform1_vector.push_back(platform1);
		platform2_vector.push_back(platform2);
		platform3_vector.push_back(platform3);
	}
	/*
	* left the right end of the platforms on x-axis
	*/
	left_end = platform3.pos_x / two - platform.width;
	right_end = platform1.pos_x / two + platform.width;

	/*
	* the game can't start with red or orange platform
	* because it will be lost or in "fast" mode from
	* the very start
	*/
	while (platform2_vector[0].color == platform.red || platform2_vector[0].color == platform.orange) {
		platform2_vector[0].color = platform2.platform_color(platform.random_color());
	}
	while (platform2_vector[1].color == platform.red || platform2_vector[1].color == platform.orange) {
		platform2_vector[1].color = platform2.platform_color(platform.random_color());
	}
}

void Tema2::CheckFuel() {
	/*
	*	no fuel
	*	set the speed to stop speed but don't fall
	*/
	if (scale_bar <= no_fuel) {
		speed = stop_speed;
		fall = false;
	}
}

void Tema2::FastMode() {
	/*
	* the sphere is on the orange platform, the game is
	* on fast mode
	*/
	if (ornage_platform == true) {
		end = clock();
		diff = (float)end - (float)begin;
		if (diff < max_diff - one) {
			if (speed > stop_speed) {
				speed = max_speed;
			}
		}
		/*
		* set the speed to nedium value
		*/
		else {
			diff = max_diff;
			if (speed > stop_speed) {
				speed = med_speed;
				ornage_platform = false;
			}
		}
	}
}

void Tema2::DrawSphere(glm::mat4 modelMatrix) {
	
	if (ornage_platform == false) {
		/*
		* game is on normal mode the sphere doesn't hase a texture
		*/
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(sphere_x, sphere_y * jump, sphere_z);
		modelMatrix *= Transform3D::Scale(sphere_radius, 1.0f, 1.0f);
		RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], modelMatrix, cyan, ornage_platform);
	}
	else {
		/*
		* fast mode = sphere hase a new texture
		*/
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(sphere_x, sphere_y * jump, sphere_z);
		modelMatrix *= Transform3D::Scale(sphere_radius, 1.0f, 1.0f);
		RenderSimpleMesh(meshes["sphere"], shaders["Shader_s"], modelMatrix, cyan, ornage_platform);
	}
}

void Tema2::DrawFuelBar(glm::mat4 modelMatrix) {

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuel_x, fuel_y, 0);
	modelMatrix *= Transform3D::Scale(scale_bar, 1.0f, 1.0f);
	RenderSimpleMesh(meshes["fuel_bar"], shaders["VertexColor"], modelMatrix, glm::vec3(), ornage_platform);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(fuel_x, fuel_y, 0);
	RenderSimpleMesh(meshes["background"], shaders["VertexColor"], modelMatrix, glm::vec3(), ornage_platform);
}

void Tema2::Falling() {
	/*
	* sphere is out of right or left end so is falling
	*/
	if ((sphere_x > right_end || sphere_x < left_end) && jump <= one) {
		speed = stop_speed;
	}

	/*
	* creating the falling effect
	*/
	if (speed == stop_speed && fall == true) {
		if (jump > sphere_fall) {
			jump -= falling_speed;
		}
	}
}

void Tema2::DrawPlarform(glm::mat4 modelMatrix, std::vector<Platform> platform_vector, glm::vec3 color, int i) {
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(platform_vector[i].pos_x, platform.pos_y, platform_vector[i].pos_z);
	modelMatrix *= Transform3D::Scale(platform.width, platform.pos_y, platform.length);
	RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, color, ornage_platform);
}

void Tema2::RedPlatform() {
	speed = stop_speed;
	fall = false;
}

void Tema2::YellowPlatform(float deltaTimeSeconds) {
	scale_bar -= scale_bar_const * deltaTimeSeconds * speed;
	if (diff > max_diff - one) {
		ornage_platform = false;
	}
}

void Tema2::GreenPlatform(float deltaTimeSeconds) {
	if (scale_bar < one) {
		scale_bar += scale_bar_const * deltaTimeSeconds * speed;
		if (diff > max_diff - one) {
			ornage_platform = false;
		}
	}
}

void Tema2::OrangePlatform() {
	begin = clock();
	ornage_platform = true;
}

