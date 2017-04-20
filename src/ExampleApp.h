
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
			float _angle;

            void drawSphere(float angle, float dist, float radius, vec4 color);
			void onRenderGraphics() override;
			void onEvent(std::shared_ptr<Event> event) override;
	};
}
