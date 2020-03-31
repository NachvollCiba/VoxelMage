#include <GLFW/glfw3.h>

class InputHandler {

	private:
		GLFWwindow& window;

	public:
		InputHandler(GLFWwindow& window);
		bool isKeyPressed(int key);
};
