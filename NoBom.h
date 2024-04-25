#ifndef NO_BOM_H
#define NO_BOM_H


#include "BaseObject.h"
#include "CommonFunc.h"
  
class NoBom : public BaseObject
{
public:
	NoBom();

	int get_no_time() { return no_time; }
	void set_no_time(int time) { no_time = time; }

private:
	int no_time;

};

#endif 
