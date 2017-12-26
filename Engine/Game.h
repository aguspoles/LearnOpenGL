#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Composite.h"
#include "Light.h"
#include "display.h"
class Mesh;
class Shader;
class Texture;

class Game
{
public:
	Game();
	~Game();
	static const int DISPLAY_WIDTH = 800;
	static const int DISPLAY_HEIGHT = 600;
	static Camera* camera;
	static Display* display;

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void Run();
	void HandleEvents();
	static bool isRunning;

	static float TimeMs();
	static void ManageTime();
	static float DeltaTime();
	static void SetFPSCapped(bool value);

	void AddMesh(Mesh* mesh);
	void AddTexture(Texture* texture);
	void AddShader(Shader* shader);

	static Light* light;
protected:
	Composite Root;
private:
	static float _lastFrameMs;
	static float _currentFrameMs;
	static float _timePerFrameCap;
	static float _timeSinceLastUpdate;
	static float _deltaTime;
	static bool _fpsCapped;

	std::vector<Mesh*> m_meshes;
	std::vector<Shader*> m_shaders;
	std::vector<Texture*> m_textures;


};

#endif
