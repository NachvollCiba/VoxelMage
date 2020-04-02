#pragma once

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
		IKeyHandler* _handlers[GLFW_KEY_LAST];
		bool _prevState[GLFW_KEY_LAST];
		std::vector<int> _registered;

		bool _isKeyPressed(int key);

	public:
		InputHandler(GLFWwindow& window);

		void update();
		void registerKeyHandler(int key, IKeyHandler* handler);
		void unregisterKeyHandler(int key);
};



