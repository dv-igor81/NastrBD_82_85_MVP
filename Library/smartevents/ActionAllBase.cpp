#include "ActionAllBase.h"

namespace smartevents
{
	ActionAllBase::ActionAllBase(
		ActionDebugSettings * l_Debug,
		int l_maxLen,
		const char * l_methodName,
		const char * l_templateName) 
		: ActionObjectBase(l_maxLen),
		m_Debug(l_Debug),
		m_methodName(CloneText(l_methodName)),
		m_templateName(CloneText(l_templateName))
	{}

	ActionAllBase::~ActionAllBase()
	{
		DeleteText(m_methodName);
		DeleteText(m_templateName);
	}

	void ActionAllBase::ErrorMessageShortString(int iVal)
	{
		if (m_Debug == 0)
		{
			return;
		}
		switch (iVal)
		{
		case 1:
			m_Debug->DebugFunkActionSelfError("Ошибка! ActionEventBase::CloneText(ptrText): ptrText > Max");
			break;
		default:
			m_Debug->display("Ошибка! int ActionEventBase: неизвестная ошибка");
			break;
		}
	}
}