#include "Elipsoid.h"

namespace basicgraphics {
	Elipsoid::Elipsoid(float height, float width, glm::vec3 bodyCenter)
	{
		// Note: TEXTURE_PATH is set in config.h
		/**shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
		tex->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
		tex->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
		tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		textures.push_back(tex);**/
		_localMat = mat4(1.0);
		_localMat[3] = vec4(bodyCenter, 0);
		setupGeometry(height, width);
	}

	void Elipsoid::setupGeometry(float height, float width) {

		float PI = glm::pi<float>();
		float cycle = 2 * PI;

		const int STACKS = 20;
		const int SLICES = 40;

		std::vector<Mesh::Vertex> cpuVertexArray;
		std::vector<int> cpuIndexArray;
		Mesh::Vertex vert;
		int counter = 0;

		float phiStep = cycle / STACKS;
		float thetaStep = cycle / SLICES;

		float phi = phiStep;

		for (float phi = 0; phi <= PI; phi += phiStep) {

			for (float theta = 0; theta <= cycle + thetaStep; theta += thetaStep) {
				//First half of square
				vert.position = vec3(width*sin(phi) * sin(theta), height*cos(phi), width*sin(phi)*cos(theta));
				vert.normal = vert.position;
				//xMapping = fmod((theta / cycle) + equatorMapping , 1.0);
				//yMapping = fmod((phi / PI) + meridianMapping, 1.0);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

				vert.position = vec3(width*sin(phi + phiStep) * sin(theta), height*cos(phi + phiStep), width*sin(phi + phiStep)*cos(theta));
				vert.normal = vert.position;
				//vert.texCoord0 = glm::vec2(theta/cycle, (phi + phiStep)/PI);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

				vert.position = vec3(width*sin(phi)*sin(theta + thetaStep), height*cos(phi), width*sin(phi)*cos(theta + thetaStep));
				vert.normal = vert.position;
				//vert.texCoord0 = glm::vec2((theta + thetaStep)/cycle, phi/PI);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

				//Second half of square
				vert.position = vec3(width*sin(phi + phiStep) * sin(theta), height*cos(phi + phiStep), width*sin(phi + phiStep)*cos(theta));
				vert.normal = vert.position;
				//vert.texCoord0 = glm::vec2(theta/cycle, (phi + phiStep)/PI);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

				vert.position = vec3(width*sin(phi)*sin(theta + thetaStep), height*cos(phi), width*sin(phi)*cos(theta + thetaStep));
				vert.normal = vert.position;
				//vert.texCoord0 = glm::vec2((theta + thetaStep)/cycle, phi/PI);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

				vert.position = vec3(width*sin(phi + phiStep) * sin(theta + thetaStep), height*cos(phi + phiStep), width*sin(phi + phiStep) * cos(theta + thetaStep));
				vert.normal = vert.position;
				//vert.texCoord0 = glm::vec2((theta + thetaStep)/cycle, (phi + phiStep)/PI);
				cpuVertexArray.push_back(vert);
				cpuIndexArray.push_back(counter);
				counter++;

			}
		}

		int numVertices = cpuVertexArray.size();
		int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
		int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
		_mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW,
			cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray,
			cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));

	}

	Elipsoid::~Elipsoid()
	{
	}

	void Elipsoid::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
		// TODO: Draw your mesh.
		mat4 model = modelMatrix * _localMat;
		shader.setUniform("model_mat", model);
		_mesh->draw(shader);
	}
};
