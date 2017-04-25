
#include "BaseApp.h"

namespace basicgraphics {

	class ExampleApp : public BaseApp {
		public:
			ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
			~ExampleApp();

		private:
			std::unique_ptr<Box> _box;
            std::unique_ptr<Line> _line;
            std::unique_ptr<Sphere> _sphere;
			std::unique_ptr<Feet> _foot;
			std::unique_ptr<Elipsoid> _body;

			float _angle;
			glm::mat4 rotation;
			bool mouseDown;
			glm::vec2 lastMousePos;
			

			void onRenderGraphics() override;
			void onEvent(std::shared_ptr<Event> event) override;
	};
}
