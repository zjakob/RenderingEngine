#ifndef SAG_GEOMETRY_H
#define SAG_GEOMETRY_H


namespace sag
{

class Geometry
{
public:
	virtual void draw() = 0;

	virtual ~Geometry() {}

private:

};

} // namespace sag


#endif // SAG_GEOMETRY_H
