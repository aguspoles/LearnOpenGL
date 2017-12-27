#include "Player.h"
#include "Game.h"
#include "InputHandler.h"

Player::Player() : m_moveLeft(false), m_moveRight(false)
{

}


Player::~Player()
{

}

void Player::UpdateComposite()
{
	HandleInput();
	static float counter = 0.0f;
	float sinCounter = sinf(counter);
	float absSinCounter = abs(sinCounter);

	if(m_moveLeft)
		transform->GetPos()->x -= 5 * Game::DeltaTime();
	if(m_moveRight)
		transform->GetPos()->x += 5 * Game::DeltaTime();

	transform->GetRot()->y = counter * Game::DeltaTime() * 100;
	//GetTransform()->GetRot()->z = counter * Game::DeltaTime() * 50;
	//GetTransform()->GetPos()->z = -10;
	transform->GetPos()->y = -1.0;
	transform->GetScale()->x = 0.15;
	transform->GetScale()->y = 0.15;
	transform->GetScale()->z = 0.15;
	transform->UpdateModelMatrix();

	counter += 0.01f;
}

void Player::InitComposite()
{
	m_shader->use();
	//gold
	/*glUniform3f(glGetUniformLocation(m_shader->ID, "material.ambient"), 0.24725, 0.1995, 0.0745);
	glUniform3f(glGetUniformLocation(m_shader->ID, "material.diffuse"), 0.75164, 0.60648, 0.22648);
	glUniform3f(glGetUniformLocation(m_shader->ID, "material.specular"), 0.628281, 0.555802, 0.366065);*/
	//cyan plastic
	/*glUniform3f(glGetUniformLocation(m_shader->ID, "material.ambient"), 0.0f, 0.1f, 0.06f);
	glUniform3f(glGetUniformLocation(m_shader->ID, "material.diffuse"), 0.0f, 0.50980392f, 0.50980392f);
	glUniform3f(glGetUniformLocation(m_shader->ID, "material.specular"), 0.50196078f, 0.50196078f, 0.50196078f);*/
	//cyan rubber
	//glUniform3f(glGetUniformLocation(m_shader->ID, "material.ambient"), 0.0, 0.05, 0.05);
	//glUniform3f(glGetUniformLocation(m_shader->ID, "material.diffuse"), 0.4, 0.5, 0.5);
	//glUniform3f(glGetUniformLocation(m_shader->ID, "material.specular"), 0.04, 0.7, 0.7);

	glUniform1f(glGetUniformLocation(m_shader->ID, "material.shininess"), 64.0);
	//glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"), 0.2, 0.2, 0.2);
	//glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), 0.5, 0.5, 0.5);
	glUniform3f(glGetUniformLocation(m_shader->ID, "light.ambient"), 1.0, 1.0, 1.0);
	glUniform3f(glGetUniformLocation(m_shader->ID, "light.diffuse"), 1.0, 1.0, 1.0);
	glUniform3f(glGetUniformLocation(m_shader->ID, "light.specular"), 1.0, 1.0, 1.0);
}

void Player::SetShaderProperties()
{
	glm::vec3 lightPos = *Game::light->transform->GetPos();
	glm::vec3 viewPos = Game::camera->Position;

	///light color change over time
	//glm::vec3 lightColor;
	//lightColor.x = sin(Game::TimeMs() * 2.0f);
	//lightColor.y = sin(Game::TimeMs() * 0.7f);
	//lightColor.z = sin(Game::TimeMs()*1.3f);
	//glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
	//glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
	//glUniform3f(glGetUniformLocation(m_shader->ID, "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
	//glUniform3f(glGetUniformLocation(m_shader->ID, "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);

	glUniform3f(glGetUniformLocation(m_shader->ID, "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(m_shader->ID, "viewPos"), viewPos.x, viewPos.y, viewPos.z);
}

void Player::HandleInput()
{
	m_moveLeft = TheInputHandler::Instance()->GetMouseButtonState(LEFT_CLICK);
	m_moveRight = TheInputHandler::Instance()->GetMouseButtonState(RIGHT_CLICK);
}


