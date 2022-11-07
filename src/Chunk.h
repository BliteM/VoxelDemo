#ifndef CHUNK_H
#define CHUNK_H
#define FNL_IMPL

#include <FastNoiseLite.h>
#include "Block.h"
#include "Mesh.h"
#include "resource.h"

extern unsigned int block_texture;

const int chunk_maxsize_x = 16;
const int chunk_maxsize_y = 64;
const int chunk_maxsize_z = 16;

void addBlockFace(Mesh& mesh, BlockFaceIndex face, int chunk_x, int chunk_y, int x, int y, int z);

class Chunk {
public:
	int chunk_coordinate_x;
	int chunk_coordinate_z;

	bool built_mesh;

	unsigned int block_data[chunk_maxsize_x][chunk_maxsize_y][chunk_maxsize_z];
	Mesh mesh;

	Chunk(int chunk_coordinate_x, int chunk_coordinate_z);

	void initBlockData();
	void generateTerrain(int seed);
	void buildMesh();
	void drawChunk(Shader& shader);
};

Chunk::Chunk(int chunk_coordinate_x, int chunk_coordinate_z) {
	this->chunk_coordinate_x = chunk_coordinate_x;
	this->chunk_coordinate_z = chunk_coordinate_z;
	initBlockData();
	this->built_mesh = false;
}

void Chunk::initBlockData() {
	int x, y, z;
	for (x = 0; x < chunk_maxsize_x; x++) {
		for (y = 0; y < chunk_maxsize_y; y++) {
			for (z = 0; z < chunk_maxsize_z; z++) {
				block_data[x][y][z] = 0;
			}
		}
	}
}

void Chunk::generateTerrain(int seed) {
	initBlockData();
	fnl_state noise = fnlCreateState();
	noise.seed = seed;
	noise.frequency = 0.025f;
	noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
	int x, y, z;
	for (x = 0; x < chunk_maxsize_x; x++) {
		for (z = 0; z < chunk_maxsize_z; z++) {
			float noise_data = fnlGetNoise2D(&noise, x + chunk_coordinate_x * chunk_maxsize_x, z + chunk_coordinate_z * chunk_maxsize_z);
			noise_data = noise_data * 4;
			int height = (int)(noise_data + 5);
			for (y = 0; y < height; y++) {
				block_data[x][y][z] = 1;
			}
		}
	}
}
void Chunk::buildMesh() {
	mesh.vertices.clear();
	int x, y, z;
	//Cull cube face, Render face in contact with air
	for (x = 0; x < chunk_maxsize_x; x++) {
		for (y = 0; y < chunk_maxsize_y; y++) {
			for (z = 0; z < chunk_maxsize_z; z++) {
				if (block_data[x][y][z] != 0) {
					//Check right side block
					if (x < chunk_maxsize_x - 1) {
						if (block_data[x + 1][y][z] == 0) {
							addBlockFace(mesh, RIGHT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						addBlockFace(mesh, RIGHT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
					}
					//Check left side block
					if (x > 0) {
						if (block_data[x - 1][y][z] == 0) {
							addBlockFace(mesh, LEFT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						addBlockFace(mesh, LEFT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
					}
					//Check top side block
					if (y < chunk_maxsize_y - 1) {
						if (block_data[x][y + 1][z] == 0) {
							addBlockFace(mesh, TOP_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						addBlockFace(mesh, TOP_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);

					}
					//Check bottom side block
					if (y > 0) {
						if (block_data[x][y - 1][z] == 0) {
							addBlockFace(mesh, BOTTOM_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						//addBlockFace(mesh, BOTTOM_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
					}
					//Check front side block
					if (z < chunk_maxsize_z - 1) {
						if (block_data[x][y][z + 1] == 0) {
							addBlockFace(mesh, FRONT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						addBlockFace(mesh, FRONT_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
					}
					//Check back side block
					if (z > 0) {
						if (block_data[x][y][z - 1] == 0) {
							addBlockFace(mesh, BACK_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
						}
					}
					else {
						addBlockFace(mesh, BACK_FACE, chunk_coordinate_x, chunk_coordinate_z, x, y, z);
					}
				}
			}
		}
	}
	mesh.updateMesh();
	built_mesh = true;
}

void Chunk::drawChunk(Shader& shader) {
	if (built_mesh) {
		mesh.Draw(shader);
	}
}

void addBlockFace(Mesh& mesh, BlockFaceIndex face, int chunk_x, int chunk_z, int x, int y, int z) {
	int i;
	for (i = 0; i < 6; i++) {
		mesh.vertices.push_back({
			{block_faces[face][i].Position + glm::vec3((float)chunk_x * (float)chunk_maxsize_x, 0.0f, (float)chunk_z * (float)chunk_maxsize_z) + glm::vec3((float)x, (float)y, (float)z)},
			{block_faces[face][i].Color /* glm::vec3(145.0f/255.0f, 189.0f/255.0f, 89.0f/255.0f)*/},
			{block_faces[face][i].TexCoords}
			});
	}
}


#endif
