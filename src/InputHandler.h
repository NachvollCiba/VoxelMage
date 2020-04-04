#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>


class IKeyHandler {
	public:
		virtual void whilePressed() {};
		virtual void whileReleased() {};

		virtual void onJustPressed() {};
		virtual void onJustReleased() {};
};

class IMouseMoveHandler {
	public: 
		virtual void onMouseMoved(int deltaX, int deltaY) {};
};


class InputHandler {

	private:
		GLFWwindow& _window;

		// Key Handlers
		IKeyHandler* _keyHandlers[GLFW_KEY_LAST];
		bool _prevKeyState[GLFW_KEY_LAST];
		std::vector<int> _registeredKeys;

		// Mouse Handlers
		std::vector<IMouseMoveHandler*> _mouseMovementHandlers;

		bool _isKeyPressed(int key);

	public:
		InputHandler(GLFWwindow& window);

		void update();
		void registerKeyHandler(int key, IKeyHandler* handler);
		void unregisterKeyHandler(int key);

		void registerMouseMovementHandler(IMouseMoveHandler* handler);
		void unregisterMouseMovementHandler(IMouseMoveHandler* handler);
};



