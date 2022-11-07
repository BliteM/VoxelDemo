#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
};

class Mesh {
public:
	vector<Vertex>       vertices;
	int vertices_size;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;

	Mesh() { setupMesh(); }

	Mesh(vector<Vertex> vertices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->textures = textures;

		setupMesh();
	}

	void Draw(Shader& shader)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices_size);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}

	void updateMesh() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		vertices_size = vertices.size();
	}

	~Mesh() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
private:
	unsigned int VBO, EBO;

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// vertex Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	}
};
#endif
