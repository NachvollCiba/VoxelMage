#include <GLFW/glfw3.h>
#include <vector>


class IKeyHandler {
	public:
		virtual void whilePressed() {};
		virtual void whileReleased() {};

		virtual void onJustPressed() {};
		virtual void onJustReleased() {};
};


class InputHandler {

	private:
		GLFWwindow& _window;
		IKeyHandler* _handlers[1024];
		bool _prevState[1024];
		std::vector<int> _registered;

		bool _isKeyPressed(int key);

	public:
		InputHandler(GLFWwindow& window);

		void update();
		void registerKeyHandler(int key, IKeyHandler* handler);
		void unregisterKeyHandler(int key);
};



