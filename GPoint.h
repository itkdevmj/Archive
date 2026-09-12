//////////////////////////////////////////////////////////
//////////  Point 좌표(공통적인 좌표값) : 백남수  ////////
//////////////////////////////////////////////////////////
//---------------------------------------------------------------------------

#ifndef GPointH
#define GPointH
#include <vcl.h>
#include <math.h>
//---------------------------------------------------------------------------
class GPoint  
{  
public:
        //GPoint에서 갖는 기본 속성값(좌표)
	double x;
	double y;
public:
	GPoint(const TPoint& _pt):x(_pt.x), y(_pt.y){};
	GPoint(double _x, double _y):x(_x), y(_y){};
	GPoint(const GPoint& _pt):x(_pt.x), y(_pt.y){};
	GPoint():x(0.),y(0.){};

	GPoint& operator= (const GPoint& _pt);
	GPoint& operator-=(const GPoint& _pt);
	GPoint& operator+=(const GPoint& _pt);

	bool operator==(const GPoint& _pt);
	bool operator!=(const GPoint& _pt);

	double dist2Point(const GPoint& _pt);
	virtual ~GPoint();
};
#endif
