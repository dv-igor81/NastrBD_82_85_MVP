//#pragma once
#ifndef __ACTION_ALL_BASE_H
#define __ACTION_ALL_BASE_H

#include "ActionObjectBase.h"
#include "ActionDebugSettings.h"

// Максимальное количество ссылок-событий (объектов ActionEventBase) внутри подписчика/обработчика (ActionSelfBase)
#define MAX_SIZE_LINK_EVENT 10

// Максимальное количество ссылок-подписчика/обработчика (объектов ActionSelfBase) внутри события (ActionEventBase)
#define MAX_SIZE_LINK_SELF 10

// Макс. длина сообщений (шаблонные классы ActionSelf и ActionEvent)
#define MAX_SIZE_FOR_ACTION_TEXT_LENGTH 250

namespace smartevents
{
	class ActionAllBase : public ActionObjectBase
	{
	public:
		ActionAllBase(
			ActionDebugSettings * l_Debug, 
			int l_maxLen,
			const char * l_methodName,
			const char * l_templateName);
		~ActionAllBase();

		void ErrorMessageShortString(int iVal);
	protected:
		ActionDebugSettings * m_Debug;
		const char * m_methodName;
		const char * m_templateName;
	};
}
#endif // #ifndef __ACTION_ALL_BASE_H