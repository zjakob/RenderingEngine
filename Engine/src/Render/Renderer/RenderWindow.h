#ifndef SAG_RENDER_WINDOW_H
#define SAG_RENDER_WINDOW_H


namespace sag
{

class RenderWindow
{
public:
	virtual ~RenderWindow() {};

	virtual void swapBuffer() = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;

private:

};

} // namespace sag


#endif // SAG_RENDER_WINDOW_H
