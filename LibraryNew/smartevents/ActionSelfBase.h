//#pragma once
#ifndef __ACTION_SELF_BASE_H
#define __ACTION_SELF_BASE_H

#include "ActionAllBase.h"

namespace smarteventsMin
{
	class ActionEventBase; // Предварительное объявление
	class ActionSelfBase // Класс подписчика/обработчика события
	{
	public:			
		ActionSelfBase(IContainer * container);
		~ActionSelfBase();
	protected:
		ActionSelfBase * GetThis();
		void Call(IArguments * i_args);
	private:		
		void Uvedomleniya();
		void DeleteActionEventLink(ActionEventBase * remote);
		bool SetLinkActionEven(ActionEventBase * EventLink);
		void ClearLinkEventArray();
		int GetEventIndex(ActionEventBase * remote);
		int GetFreeEventIndex();
		ActionEventBase * LinkEventArray[MAX_SIZE_LINK_EVENT]; // Массив, хранящий события, под которые подписан подписчик/обработчик
		IContainer * m_container;
		friend class ActionEventBase;
	};
}
#endif // #ifndef __ACTION_SELF_BASE_H