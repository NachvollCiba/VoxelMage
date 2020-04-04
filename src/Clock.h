class Clock {

	private:
		double _lastFrameTime;
		double _deltaFrameTime;

	public:
		Clock();

		void update();
		double getDeltaFrameTime();
};
