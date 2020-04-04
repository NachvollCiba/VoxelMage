#pragma once 

class Game;

class Clock {

	private:
		double _lastFrameTime;
		double _deltaFrameTime;

		void _update();
		friend class Game;

	public:
		Clock();

		float getDeltaFrameTime() const;
};
