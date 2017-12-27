#include "Light.h"
#include "Game.h"
#include "shader.h"
#include <iostream>

Light::Light(vector<glm::vec3> vertices, vector<unsigned int> indices)
{
	m_numIndices = indices.size();
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	//positions buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//indexes buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Light::~Light()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Light::InitComposite()
{
	Color = glm::vec3(1.0, 1.0, 0.5);
	transform->GetPos()->x = 1.2;
	transform->GetPos()->y = 1.0;
	transform->GetPos()->z = -2.0;
	transform->GetScale()->x = 0.5;
	transform->GetScale()->y = 0.5;
	transform->GetScale()->z = 0.5;
	transform->UpdateModelMatrix();
}

void Light::UpdateComposite()
{
	static float counter = 0.0f;
	float sinCounter = sinf(counter);
	float absSinCounter = abs(sinCounter);
	transform->GetPos()->z = sinCounter * Game::DeltaTime() * 100;
	transform->UpdateModelMatrix();
	counter += 0.01f;
}

void Light::RenderComposite(glm::mat4 modelMatrix)
{
	m_shader->use();

	m_shader->setMat4("model", transform->GetModelMatrix());
	m_shader->setMat4("view", Game::camera->GetViewMatrix());
	m_shader->setMat4("projection", Game::camera->GetProjectionMatrix());

	glBindVertexArray(m_vertexArrayObject);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
}

void Light::SetShader(Shader * shader)
{
	m_shader = shader;
}


