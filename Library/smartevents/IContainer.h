//#pragma once
#ifndef __ICONTAINER_H
#define __ICONTAINER_H
#include "IArguments.h"

namespace smartevents
{
	class IContainer
	{
	public:
		virtual ~IContainer() {} // Деструктор
		virtual void Call(IArguments *) = 0;
	};
}
#endif // #ifndef __ICONTAINER_H