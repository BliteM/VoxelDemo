#ifndef BLOCK_H
#define BLOCK_H

#include "Mesh.h"

struct Block {
	unsigned int block_type;
};

enum BlockFaceIndex {
	BACK_FACE = 0, FRONT_FACE, LEFT_FACE, RIGHT_FACE, BOTTOM_FACE, TOP_FACE
};

//Vertice of face of cube contain Position Color and Texture Coordinate
Vertex block_faces[6][6] = {
	{   // Back face    Z-
		{{-0.5f, -0.5f, -0.5f},{0.9f,0.9f,0.9f},{0.0f, 0.0f}}, // Bottom-left
		{{ 0.5f,  0.5f, -0.5f},{0.9f,0.9f,0.9f},{1.0f, 1.0f}}, // top-right
		{{ 0.5f, -0.5f, -0.5f},{0.9f,0.9f,0.9f},{1.0f, 0.0f}}, // bottom-right
		{{ 0.5f,  0.5f, -0.5f},{0.9f,0.9f,0.9f},{1.0f, 1.0f}}, // top-right
		{{-0.5f, -0.5f, -0.5f},{0.9f,0.9f,0.9f},{0.0f, 0.0f}}, // bottom-left
		{{-0.5f,  0.5f, -0.5f},{0.9f,0.9f,0.9f},{0.0f, 1.0f}}  // top-left
	},

	{   // Front face   Z+
		{{-0.5f, -0.5f,  0.5f},{0.9f,0.9f,0.9f},{0.0f, 0.0f}}, // Bottom-left
		{{ 0.5f, -0.5f,  0.5f},{0.9f,0.9f,0.9f},{1.0f, 0.0f}}, // top-right
		{{ 0.5f,  0.5f,  0.5f},{0.9f,0.9f,0.9f},{1.0f, 1.0f}}, // bottom-right
		{{ 0.5f,  0.5f,  0.5f},{0.9f,0.9f,0.9f},{1.0f, 1.0f}}, // top-right
		{{-0.5f,  0.5f,  0.5f},{0.9f,0.9f,0.9f},{0.0f, 1.0f}}, // bottom-left
		{{-0.5f, -0.5f,  0.5f},{0.9f,0.9f,0.9f},{0.0f, 0.0f}}  // top-left
	},

	{   // Left face    X-
		{{-0.5f,  0.5f,  0.5f},{0.8f,0.8f,0.8f},{1.0f, 0.0f}}, // Bottom-left
		{{-0.5f,  0.5f, -0.5f},{0.8f,0.8f,0.8f},{1.0f, 1.0f}}, // top-right
		{{-0.5f, -0.5f, -0.5f},{0.8f,0.8f,0.8f},{0.0f, 1.0f}}, // bottom-right
		{{-0.5f, -0.5f, -0.5f},{0.8f,0.8f,0.8f},{0.0f, 1.0f}}, // top-right
		{{-0.5f, -0.5f,  0.5f},{0.8f,0.8f,0.8f},{0.0f, 0.0f}}, // bottom-left
		{{-0.5f,  0.5f,  0.5f},{0.8f,0.8f,0.8f},{1.0f, 0.0f}}  // top-left
	},

	{   // Right face   X+
		{{ 0.5f,  0.5f,  0.5f},{0.8f,0.8f,0.8f},{1.0f, 0.0f}}, // Bottom-left
		{{ 0.5f, -0.5f, -0.5f},{0.8f,0.8f,0.8f},{0.0f, 1.0f}}, // top-right
		{{ 0.5f,  0.5f, -0.5f},{0.8f,0.8f,0.8f},{1.0f, 1.0f}}, // bottom-right
		{{ 0.5f, -0.5f, -0.5f},{0.8f,0.8f,0.8f},{0.0f, 1.0f}}, // top-right
		{{ 0.5f,  0.5f,  0.5f},{0.8f,0.8f,0.8f},{1.0f, 0.0f}}, // bottom-left
		{{ 0.5f, -0.5f,  0.5f},{0.8f,0.8f,0.8f},{0.0f, 0.0f}}  // top-left
	},

	{   // Bottom face  Y-
		{{-0.5f, -0.5f, -0.5f},{1.0f,1.0f,1.0f},{0.0f, 1.0f}}, // Bottom-left
		{{ 0.5f, -0.5f, -0.5f},{1.0f,1.0f,1.0f},{1.0f, 1.0f}}, // top-right
		{{ 0.5f, -0.5f,  0.5f},{1.0f,1.0f,1.0f},{1.0f, 0.0f}}, // bottom-right
		{{ 0.5f, -0.5f,  0.5f},{1.0f,1.0f,1.0f},{1.0f, 0.0f}}, // top-right
		{{-0.5f, -0.5f,  0.5f},{1.0f,1.0f,1.0f},{0.0f, 0.0f}}, // bottom-left
		{{-0.5f, -0.5f, -0.5f},{1.0f,1.0f,1.0f},{0.0f, 1.0f}}  // top-left
	},

	{   // Top face     Y+
		{{-0.5f,  0.5f, -0.5f},{1.0f,1.0f,1.0f},{0.0f, 1.0f}}, // Bottom-left
		{{ 0.5f,  0.5f,  0.5f},{1.0f,1.0f,1.0f},{1.0f, 0.0f}}, // top-right
		{{ 0.5f,  0.5f, -0.5f},{1.0f,1.0f,1.0f},{1.0f, 1.0f}}, // bottom-right
		{{ 0.5f,  0.5f,  0.5f},{1.0f,1.0f,1.0f},{1.0f, 0.0f}}, // top-right
		{{-0.5f,  0.5f, -0.5f},{1.0f,1.0f,1.0f},{0.0f, 1.0f}}, // bottom-left
		{{-0.5f,  0.5f,  0.5f},{1.0f,1.0f,1.0f},{0.0f, 0.0f}} // top-left
	}
};

#endif
