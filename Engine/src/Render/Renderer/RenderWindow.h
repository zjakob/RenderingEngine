#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H


class RenderWindow
{
public:
	virtual ~RenderWindow() {};

	virtual void swapBuffer() = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;

private:

};

#endif // RENDER_WINDOW_H
