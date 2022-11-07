#ifndef CHUNK_MANAGER
#define CHUNK_MANAGER

#include "Chunk.h"
#include "resource.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <glm/gtx/hash.hpp>


const int chunk_view = 8;
int load_limit_each_frame = 4;

using namespace std;

class ChunkManager {
public:
	ChunkManager() {
		seed = rand() % 65536;
	}

	unordered_map<glm::ivec2, Chunk*> chunk_map;
	int seed;
	void addChunk(int chunk_coordinate_x, int chunk_coordinate_z);
	void drawChunks(Shader& shader);
	void updateChunks(float player_position_x, float player_position_z);
	void reloadChunks(float player_position_x, float player_position_z);
};

void ChunkManager::addChunk(int chunk_coordinate_x, int chunk_coordinate_z) {
	Chunk* c = new Chunk(chunk_coordinate_x, chunk_coordinate_z);
	c->generateTerrain(seed);
	c->buildMesh();
	glm::ivec2 key = glm::ivec2(chunk_coordinate_x, chunk_coordinate_z);
	chunk_map[key] = c;
}

void ChunkManager::drawChunks(Shader& shader) {
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, block_texture);

	unordered_map<glm::ivec2, Chunk*>::iterator it = chunk_map.begin();

	while (it != chunk_map.end()) {
		if (it->second->built_mesh == true) {
			it->second->drawChunk(shader);
		}
		it++;
	}
}

void ChunkManager::updateChunks(float player_position_x, float player_position_z) {
	int player_chunk_position_x = ((int)player_position_x) / 16;
	int player_chunk_position_z = ((int)player_position_z) / 16;

	int origin_x = player_chunk_position_x - chunk_view;
	int origin_z = player_chunk_position_z - chunk_view;

	int end_x = player_chunk_position_x + chunk_view;
	int end_z = player_chunk_position_z + chunk_view;

	unordered_map<glm::ivec2, Chunk*>::iterator c = chunk_map.begin();
	while (c != chunk_map.end()) {
		if (c->second->chunk_coordinate_x < origin_x ||
			c->second->chunk_coordinate_z < origin_z ||
			c->second->chunk_coordinate_x > end_x ||
			c->second->chunk_coordinate_z > end_z)
		{
			delete c->second;
			chunk_map.erase(c);
		}
		c++;
	}
	int loaded_chunks = 0;
	for (int torigin_x = origin_x; torigin_x <= end_x; torigin_x++) {
		for (int torigin_z = origin_z; torigin_z <= end_z; torigin_z++) {
			unordered_map<glm::ivec2, Chunk*>::iterator c = chunk_map.find(glm::ivec2(torigin_x, torigin_z));
			if (c == chunk_map.end()) {
				addChunk(torigin_x, torigin_z);
				loaded_chunks++;
			}
			if (loaded_chunks >= load_limit_each_frame) { break; }
		}
		if (loaded_chunks >= load_limit_each_frame) { break; }
	}
}

void ChunkManager::reloadChunks(float player_position_x, float player_position_z) {
	int player_chunk_position_x = ((int)player_position_x) / 16;
	int player_chunk_position_z = ((int)player_position_z) / 16;

	int origin_x = player_chunk_position_x - chunk_view;
	int origin_z = player_chunk_position_z - chunk_view;

	int end_x = player_chunk_position_x + chunk_view;
	int end_z = player_chunk_position_z + chunk_view;

	unordered_map<glm::ivec2, Chunk*>::iterator c = chunk_map.begin();
	while (c != chunk_map.end()) { delete c->second; c++; }
	chunk_map.clear();

	for (int torigin_x = origin_x; torigin_x <= end_x; torigin_x++) {
		for (int torigin_z = origin_z; torigin_z <= end_z; torigin_z++) {
			addChunk(torigin_x, torigin_z);
		}
	}
}
#endif
