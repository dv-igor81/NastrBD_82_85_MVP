//#pragma once
#ifndef __ACTION_SELF_BASE_H
#define __ACTION_SELF_BASE_H

#include "ActionAllBase.h"

namespace smartevents
{
	class ActionEventBase; // Предварительное объявление
	class ActionSelfBase : public ActionAllBase // Класс подписчика/обработчика события
	{
	public:			
		ActionSelfBase(		
			IContainer * container,				
			ActionDebugSettings * l_Debug,			
			int l_maxLen, 			
			char * l_methodName, 			
			char * l_templateName);
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