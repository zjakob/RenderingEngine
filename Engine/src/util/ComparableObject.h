#ifndef SAG_IDENTIFYABLE_OBJECT_H
#define SAG_IDENTIFYABLE_OBJECT_H


namespace sag
{

class ComparableObject
{
public:
	ComparableObject();

	friend bool operator== (const ComparableObject &c1, const ComparableObject &c2);
	friend bool operator!= (const ComparableObject &c1, const ComparableObject &c2);

private:

	static unsigned int idCnt;
	const unsigned int id;

};

} // namespace sag


#endif // SAG_IDENTIFYABLE_OBJECT_H
