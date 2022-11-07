#include <iostream>

#include "Camera.h"
#include "window.h"
#include "input.h"
#include "Mesh.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "resource.h"
#include <cstdlib>
#include <string>

Camera camera(glm::vec3(24.0f, 16.0f, 24.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLFWwindow* window;

int main()
{
	windowInit();
	setBlockTexture("assets/cobblestone.png");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	ChunkManager chunk_manager;
	chunk_manager.reloadChunks(camera.Position.x, camera.Position.z);

	Shader ourShader("shaders/camera.vs", "shaders/camera.fs");
	ourShader.use();

	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		string title = "VoxelDemo by BliteM | FPS:";
		title.append(to_string(1 / deltaTime));
		glfwSetWindowTitle(window, title.c_str());
		// input
		processInput(window);

		// render
		glClearColor(142.0f / 255.0f, 206.0f / 255.0f, 255.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		ourShader.use();

		//Projection matrix for 3D;
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

		glm::mat4 matrix = projection * view * model;
		ourShader.setMat4("matrix", matrix);

		chunk_manager.updateChunks(camera.Position.x, camera.Position.z);
		if (Qsignal == true) {
			chunk_manager.reloadChunks(camera.Position.x, camera.Position.z);
		}
		chunk_manager.drawChunks(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
