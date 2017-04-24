// Fin class for penGUIn project
//
// Created by Connor Valenti on 4/20/2017

#include "Fin.h"

namespace basicgraphics {
	Fin::Fin() {
		std::vector<Mesh::Vertex> cpuVertexArray;
		std::vector<int> cpuIndexArray;
		std::vector<std::shared_ptr<Texture>> textures;

		Mesh::Vertex vert;

		// Draws one side of the penguin's fin.
		for (int i = 0; i < 20; i++) {
			float x = cos(i * pi / 10);
			float y = sin(i * pi / 10);
			vert.position = vec3(x, y, 0.15);
			vert.normal = vec3(0, 0, 1);
			vert.texCoord0 = vec2(0, 0);
			cpuVertexArray.push_back(vert);
			cpuIndexArray.push_back(i);
		}

		// Draws the other side of the penguin's fin. 
		for (int i = 0; i < 20; i++) {
			float x = cos(i * pi / 10);
			float y = sin(i * pi / 10);
			vert.position = vec3(x, y, -0.15);
			vert.normal = vec3(0, 0, 1);
			vert.texCoord0 = vec2(0, 0);
			cpuVertexArray.push_back(vert);
			cpuIndexArray.push_back(i + 20);
		}

		const int numVertices = cpuVertexArray.size();
		const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
		const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
		_mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0,
			cpuVertexArray, cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
		_mesh->setMaterialColor(_color);
	}

	Fin::~Fin()
	{
	}

	void Fin::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
		_mesh->draw(shader);
	}
}