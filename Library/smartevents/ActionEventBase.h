//#pragma once
#ifndef __ACTION_EVENT_BASE_H
#define __ACTION_EVENT_BASE_H

#include "ActionAllBase.h"

namespace smartevents
{
	class ActionSelfBase; // Предварительное объявление
	class ActionEventBase : public ActionAllBase // Класс событя
	{
	public:
		ActionEventBase(
			ActionDebugSettings * l_Debug,
			int l_maxLen,
			char * l_methodName,
			char * l_templateName);
		~ActionEventBase();
	protected:
		void oper_PlusRavno_Link(ActionSelfBase & AS);
		void oper_PlusRavno_Ptr(ActionSelfBase * AS);
		void oper_Functor(IArguments * i_args);
		void oper_MinusRavno_Link(ActionSelfBase & AS);
		void oper_MinusRavno_Ptr(ActionSelfBase * AS);
	private:
		void Uvedomleniya();
		void DeleteActionSelfLink(ActionSelfBase * self, int tip);
		int GetSelfIndex(ActionSelfBase * remote);
		bool SetLinkActionSelf(ActionSelfBase * SelfLink);
		void ClearLinkSelfArray();
		int GetFreeSelfIndex();
		int GetNotEmptySelfIndex();
		ActionSelfBase * LinkSelfArray[MAX_SIZE_LINK_SELF]; // Массив, хранящий подписчиков/обработчиков события
		friend class ActionSelfBase;
	};
}
#endif // #ifndef __ACTION_EVENT_BASE_H