#ifndef ROB
#define ROB
#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"

#include "RuntimeObjectSystem/IObject.h"
#include "IUpdateable.h"
#include "InterfaceIds.h"
#include <iostream>
#include <AGE_Assert.hpp>

class RuntimeObject01 : public TInterface<IID_IUPDATEABLE, IUpdateable>
{
public:
	virtual bool Update(float deltaTime)
	{
		std::cout << "Runtime Object 01 update called!\n";
		return true;
	}
};

REGISTERCLASS(RuntimeObject01);


#endif // !ROB
