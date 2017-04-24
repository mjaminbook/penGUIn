#pragma once

// Fin header file for penGUIn project
//
// Created by Connor Valenti on 4/20/2017

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>

#include "Mesh.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace basicgraphics {
	class Fin {
	public:
		virtual void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);

	protected:
		std::unique_ptr<Mesh> _mesh;

	};
}