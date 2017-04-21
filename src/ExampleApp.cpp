#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
	ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
	{
//        _head.reset(new Sphere(vec3(0,0,0), 0.5, vec4(0,0,0,1)));
        _beak.reset(new Cone(vec3(0,0,0.5), vec3(0,0,0.8), 0.1, vec4(1,1,0,1)));
        _left_eye.reset(new Sphere(vec3(0.1,0.5 * sin(radians(15.0f)),0.5 * cos(radians(15.0f))), 0.1, vec4(0,0.2,0.5,1)));
        _right_eye.reset(new Sphere(vec3(-0.1,0.5 * sin(radians(15.0f)),0.5 * cos(radians(15.0f))), 0.1, vec4(0,0.2,0.5,1)));
        drawHead(0.5);
	}

	ExampleApp::~ExampleApp() {}
    
    void ExampleApp::drawHead(float radius) {
        const int STACKS = 10;
        const int SLICES = 20;
        
        std::vector<Mesh::Vertex> vertexArray;
        std::vector<int> indexArray;
        
        const float stackAngle = glm::pi<float>() / STACKS;
        const float sliceAngle = 2.0 * glm::pi<float>() / SLICES;
        
        std::vector<vec3> topVerts;
        std::vector<vec3> bottomVerts;
        float stackTopY;
        float stackBottomY;
        float stackTopRadius;
        float stackBottomRadius;
        
        vec3 prevTop;
        vec3 prevBottom;
        vec3 nextTop;
        vec3 nextBottom;
        
        // Draw top cone of head
        stackTopY = radius;
        stackBottomY = radius * cos(stackAngle);
        stackBottomRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
        nextTop = vec3(0, stackTopY, 0);
        nextBottom = vec3(0, stackBottomY, stackBottomRadius);
        
        for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
            prevBottom = nextBottom;
            bottomVerts.push_back(prevBottom);
            nextBottom = vec3(stackBottomRadius * sin(sliceAngle * (slIndex + 1)), stackBottomY, stackBottomRadius * cos(sliceAngle * (slIndex + 1)));
            
            Mesh::Vertex vert1;
            vert1.position = nextTop;
            vert1.normal = normalize(nextTop);
//            vert1.texCoord0 = vec2(slIndex * texSliceWidth, 1);
            vertexArray.push_back(vert1);
            indexArray.push_back(slIndex * 3);
            
            Mesh::Vertex vert2;
            vert2.position = prevBottom;
            vert2.normal = normalize(prevBottom);
//            vert2.texCoord0 = vec2(slIndex * texSliceWidth, SPHERE_RADIUS - texStackHeight);
            vertexArray.push_back(vert2);
            indexArray.push_back(slIndex * 3 + 1);
            
            Mesh::Vertex vert3;
            vert3.position = nextBottom;
            vert3.normal = normalize(nextBottom);
//            vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, SPHERE_RADIUS - texStackHeight);
            vertexArray.push_back(vert3);
            indexArray.push_back(slIndex * 3 + 2);
        }
        
        // Draw body of head
        for (int stIndex = 0; stIndex < STACKS - 2; stIndex++) {
            stackTopY = stackBottomY;
            stackBottomY = radius * cos(stackAngle * (stIndex + 2));
            stackTopRadius = stackBottomRadius;
            stackBottomRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
            
            topVerts = bottomVerts;
            bottomVerts.clear();
            nextTop = topVerts[0];
            nextBottom = vec3(0, stackBottomY, stackBottomRadius);
            
            int VBOIndex = vertexArray.size();
            
            for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
                prevTop = nextTop;
                nextTop = topVerts[slIndex + 1];
                prevBottom = nextBottom;
                nextBottom = vec3(stackBottomRadius * sin(sliceAngle * (slIndex + 1)), stackBottomY, stackBottomRadius * cos(sliceAngle * (slIndex + 1)));
                bottomVerts.push_back(prevBottom);
                
                Mesh::Vertex vert1;
                vert1.position = prevTop;
                vert1.normal = normalize(prevTop);
//                vert1.texCoord0 = vec2(slIndex * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert1);
                indexArray.push_back(slIndex * 6 + VBOIndex);
                
                Mesh::Vertex vert2;
                vert2.position = prevBottom;
                vert2.normal = normalize(prevBottom);
//                vert2.texCoord0 = vec2(slIndex * texSliceWidth, 1 - (stIndex + 2) * texStackHeight);
                vertexArray.push_back(vert2);
                indexArray.push_back(slIndex * 6 + 1 + VBOIndex);
                
                Mesh::Vertex vert3;
                vert3.position = nextBottom;
                vert3.normal = normalize(nextBottom);
//                vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - (stIndex + 2) * texStackHeight);
                vertexArray.push_back(vert3);
                indexArray.push_back(slIndex * 6 + 2 + VBOIndex);
                
                Mesh::Vertex vert4;
                vert4.position = prevTop;
                vert4.normal = normalize(prevTop);
//                vert4.texCoord0 = vec2(slIndex * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert4);
                indexArray.push_back(slIndex * 6 + 3 + VBOIndex);
                
                Mesh::Vertex vert5;
                vert5.position = nextBottom;
                vert5.normal = normalize(nextBottom);
//                vert5.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - (stIndex + 2) * texStackHeight);
                vertexArray.push_back(vert5);
                indexArray.push_back(slIndex * 6 + 4 + VBOIndex);
                
                Mesh::Vertex vert6;
                vert6.position = nextTop;
                vert6.normal = normalize(nextTop);
//                vert6.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert6);
                indexArray.push_back(slIndex * 6 + 5 + VBOIndex);
            }
        }
        
        // Create bottom cone of head
        stackTopY = stackBottomY;
        stackBottomY = -radius;
        stackTopRadius = stackBottomRadius;
        topVerts = bottomVerts;
        
        nextTop = topVerts[0];
        nextBottom = vec3(0, stackBottomY, 0);
        int VBOIndex = vertexArray.size();
        
        for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
            // Set the triangle points
            prevTop = nextTop;
            nextTop = topVerts[slIndex + 1];
            
            Mesh::Vertex vert1;
            vert1.position = prevTop;
            vert1.normal = normalize(prevTop);
//            vert1.texCoord0 = vec2(slIndex * texSliceWidth, texStackHeight);
            vertexArray.push_back(vert1);
            indexArray.push_back(slIndex * 3 + VBOIndex);
            
            Mesh::Vertex vert2;
            vert2.position = nextBottom;
            vert2.normal = normalize(nextBottom);
//            vert2.texCoord0 = vec2(slIndex * texSliceWidth, 0);
            vertexArray.push_back(vert2);
            indexArray.push_back(slIndex * 3 + 1 + VBOIndex);
            
            Mesh::Vertex vert3;
            vert3.position = nextTop;
            vert3.normal = normalize(nextTop);
//            vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, texStackHeight);
            vertexArray.push_back(vert3);
            indexArray.push_back(slIndex * 3 + 2 + VBOIndex);
        }
        

        
        
        
        const int numVertices = vertexArray.size();
        const int vertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int indexByteSize = sizeof(int) * indexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, vertexByteSize, indexByteSize, 0,vertexArray, indexArray.size(), indexByteSize, &indexArray[0]));

    }

	void ExampleApp::onRenderGraphics() {
		// Setup the view matrix to set where the camera is located
		glm::vec3 eye_world = glm::vec3(0,0,5);
		glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0,0,0), glm::vec3(0,1,0));
		
		// Setup the projection matrix so that things are rendered in perspective
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
		// Setup the model matrix
		glm::mat4 model = glm::mat4(1.0);

		glm::mat4 rotate = glm::toMat4(glm::angleAxis(_angle, vec3(0, 1, 0))) * glm::toMat4(glm::angleAxis((float)radians(20.0), vec3(1.0, 0.0, 0.0)));
		_angle += radians(1.0);
//		model = rotate * model;

		// Update shader variables
		_shader.setUniform("view_mat", view);
		_shader.setUniform("projection_mat", projection);
		_shader.setUniform("model_mat", model);
		_shader.setUniform("eye_world", eye_world);

//        _head->draw(_shader, model);
        _beak->draw(_shader, model);
        _left_eye->draw(_shader, model);
        _right_eye->draw(_shader,model);
        _mesh->draw(_shader);
	}
    
    void ExampleApp::drawSphere(float angle, float dist, float radius, vec4 color) {
//        _line.reset(new Line(vec3(0, 0, 0), vec3(dist * cos(angle), dist * sin(angle), 0), vec3(0,0,1), 0.1, color));
//        _sphere.reset(new Sphere(vec3(dist * cos(angle), dist * sin(angle), 0), radius, color));
    }

	void ExampleApp::onEvent(shared_ptr<Event> event) {
		string name = event->getName();
		if (name == "kbd_ESC_down") {
			glfwSetWindowShouldClose(_window, 1);
		}
		else {
			cout << name << endl;
		}
	}
}
