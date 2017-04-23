#ifndef ExampleApp_h
#define ExampleApp_h

#include "BaseApp.h"
#include "PenguinHead.h"
#include <string.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "config.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace basicgraphics {

	class ExampleApp : public BaseApp {
		public:
			ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
			~ExampleApp();

		private:
//			std::unique_ptr<Mesh> _mesh;
//            std::vector< std::shared_ptr<Texture> > textures;
        
            std::shared_ptr<PenguinHead> penguinHead;
        
//            std::unique_ptr<Sphere> _head;
//            std::unique_ptr<Cone> _beak;
//            std::unique_ptr<Sphere> _left_eye;
//            std::unique_ptr<Sphere> _right_eye;
			float _angle;

            void drawSphere(float angle, float dist, float radius, vec4 color);
			void onRenderGraphics() override;
			void onEvent(std::shared_ptr<Event> event) override;
            void drawHead(float radius);
	};
}

#endif
