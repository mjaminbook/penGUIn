#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
	ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
	{

//        _head.reset(new Sphere(vec3(0,0,0), 0.5, vec4(0,0,0,1)));
//        _beak.reset(new Cone(vec3(0,0,0.5), vec3(0,0,0.8), 0.1, vec4(1,1,0,1)));
//        _left_eye.reset(new Sphere(vec3(0.1,0.5 * sin(radians(15.0f)),0.5 * cos(radians(15.0f))), 0.05, vec4(0,0.2,0.5,1)));
//        _right_eye.reset(new Sphere(vec3(-0.1,0.5 * sin(radians(15.0f)),0.5 * cos(radians(15.0f))), 0.05, vec4(0,0.2,0.5,1)));
        penguinHead.reset(new PenguinHead());
        _angle = 1.0;
	}

	ExampleApp::~ExampleApp() {}
    


	void ExampleApp::onRenderGraphics() {
		// Setup the view matrix to set where the camera is located
		glm::vec3 eye_world = glm::vec3(0,0,5);
		glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0,0,0), glm::vec3(0,1,0));
		
		// Setup the projection matrix so that things are rendered in perspective
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
		// Setup the model matrix
		glm::mat4 model = glm::mat4(1.0);

//        glm::mat4 rotate = toMat4(angleAxis((float)radians(_angle), vec3(0, 1, 0))) * toMat4(angleAxis((float)radians(_angle), vec3(1, 0, 0)));
        glm::mat4 rotate = toMat4(angleAxis((float)radians(_angle), vec3(1, 0, 0)));
		_angle += radians(10.0);
		model = rotate * model;

		// Update shader variables
		_shader.setUniform("view_mat", view);
		_shader.setUniform("projection_mat", projection);
		_shader.setUniform("model_mat", model);
		_shader.setUniform("eye_world", eye_world);

//        _head->draw(_shader, model);
//        _beak->draw(_shader, model);
//        _left_eye->draw(_shader, model);
//        _right_eye->draw(_shader,model);
        penguinHead->draw(_shader);
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
