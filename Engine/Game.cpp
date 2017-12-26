#include "Game.h"
#include "camera.h"
#include "display.h"
#include "Player.h"
#include "InputHandler.h"
#include "Model.h"

float Game::_deltaTime = 0;
float Game::_timePerFrameCap = 1.0f / 60.0f; //60 fps
bool Game::_fpsCapped = true;
float Game::_timeSinceLastUpdate = 0;
float Game::_currentFrameMs = 0;
float Game::_lastFrameMs = 0;
bool Game::isRunning = true;
Light* Game::light = NULL;
Display* Game::display = NULL;
Camera* Game::camera = NULL;

Game::Game()
{

}

Game::~Game()
{
	delete camera;
	for each(Mesh* mesh in m_meshes)
	{
		if (mesh)
		{
			delete mesh;
			mesh = NULL;
		}
	}
	for each(Texture* texture in m_textures)
	{
		if (texture)
		{
			delete texture;
			texture = NULL;
		}
	}
	for each(Shader* shader in m_shaders)
	{
		if (shader)
		{
			delete shader;
			shader = NULL;
		}
	}
	m_meshes.clear();
	m_shaders.clear();
	m_textures.clear();
}

void Game::Render()
{
}

void Game::Init()
{
	display = new Display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	vector<unsigned int> lightIndices = { 0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};
	std::vector<glm::vec3> lightVertices = {
		glm::vec3(-1, -1, -1),
		glm::vec3(-1, 1, -1),
		glm::vec3(1, 1, -1),
		glm::vec3(1, -1, -1),

		glm::vec3(-1, -1, 1),
		glm::vec3(-1, 1, 1),
		glm::vec3(1, 1, 1), 
		glm::vec3(1, -1, 1),

		glm::vec3(-1, -1, -1),
		glm::vec3(-1, -1, 1),
		glm::vec3(1, -1, 1),
		glm::vec3(1, -1, -1),

		glm::vec3(-1, 1, -1),
		glm::vec3(-1, 1, 1),
		glm::vec3(1, 1, 1), 
		glm::vec3(1, 1, -1),

		glm::vec3(-1, -1, -1),
		glm::vec3(-1, -1, 1),
		glm::vec3(-1, 1, 1),
		glm::vec3(-1, 1, -1),

		glm::vec3(1, -1, -1),
		glm::vec3(1, -1, 1),
		glm::vec3(1, 1, 1), 
		glm::vec3(1, 1, -1)
	};
	
	Model* nanosuit = new Model("../res/nanosuit/nanosuit.obj");
	Shader* shader = new Shader("../res/lightShader.vs", "../res/lightShader.fs");
	Shader* nano = new Shader("../res/nano.vs", "../res/nano.fs");
	Shader* lightShader = new Shader("../res/lightSource.vs", "../res/lightSource.fs");
	/*Texture* texture1 = new Texture("../res/bricks.jpg");
	Texture* texture2 = new Texture("../res/mini.jpg");*/

	Player* player = new Player;
	player->SetModel(nanosuit);
	player->SetShader(shader);

	light = new Light(lightVertices, lightIndices);
	light->SetShader(lightShader);
	light->Color = glm::vec3(1.0, 0, 0);

	/*AddTexture(texture1);
	AddTexture(texture2);*/
	AddShader(shader);
	AddShader(lightShader);
	AddShader(nano);

	Root.AddComponent(light);
	Root.AddComponent(player);
	Root.Init();
	TheInputHandler::Instance();
}

void Game::Update()
{

}

void Game::Run()
{
	Init();

	_lastFrameMs = TimeMs();

	while (!glfwWindowShouldClose(display->window))
	{
		ManageTime();

		if (_fpsCapped)
		{
			while (_timeSinceLastUpdate > _timePerFrameCap)
			{
				_timeSinceLastUpdate -= _timePerFrameCap;

				HandleEvents();
				Update();
				Root.Update();
			}
		}
		else
		{
			HandleEvents();
			Update();
			Root.Update();
		}
		display->Clear(0.0f, .0f, 0.0f, 1.0f);

		Root.Render();

		display->SwapBuffers();
		glfwPollEvents();
	}
}

void Game::HandleEvents()
{
	TheInputHandler::Instance()->Update();
}


float Game::TimeMs()
{
	return glfwGetTime();
}

void Game::ManageTime()
{
	_currentFrameMs = TimeMs();
	_deltaTime = (_currentFrameMs - _lastFrameMs);
	_lastFrameMs = _currentFrameMs;
	_timeSinceLastUpdate += _deltaTime;
}

float Game::DeltaTime()
{
	if (_fpsCapped)
		return _timePerFrameCap;
	else
		return _deltaTime;
}

void Game::SetFPSCapped(bool value)
{
	_fpsCapped = value;
}

void Game::AddMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}

void Game::AddTexture(Texture * texture)
{
	m_textures.push_back(texture);
}

void Game::AddShader(Shader * shader)
{
	m_shaders.push_back(shader);
}


