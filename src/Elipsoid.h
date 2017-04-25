#ifndef Elipsoid_h
#define Elipsoid_h

#include <stdio.h>
#include "GLSLProgram.h"
#include "Texture.h"
#include "Mesh.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include "glm/glm/gtx/orthonormalize.hpp"
#include "glm/glm/gtx/quaternion.hpp"
#include <glm/glm/gtx/vector_angle.hpp>
#include <cmath>

namespace basicgraphics {
	class Elipsoid
	{
	public:
		Elipsoid(const float height, const float width, const glm::vec3 bodyCenter);
		~Elipsoid();

		// Calculate and set up the buffers to render to screen
		void setupGeometry(const float height, const float width);
		void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);

	protected:
		// Stores the earth texture data
		std::vector< std::shared_ptr<Texture> > textures;
		std::unique_ptr<Mesh> _mesh;
		glm::mat4 _localMat;
	};
}

#endif