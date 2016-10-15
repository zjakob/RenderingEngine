#ifndef IDENTIFYABLE_OBJECT_H
#define IDENTIFYABLE_OBJECT_H

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

#endif // IDENTIFYABLE_OBJECT_H
