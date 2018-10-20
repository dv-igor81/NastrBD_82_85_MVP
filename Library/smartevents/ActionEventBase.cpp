#include "ActionEventBase.h"
#include "ActionSelfBase.h"

namespace smartevents
{
	ActionEventBase::ActionEventBase(
		ActionDebugSettings * l_Debug,
		int l_maxLen,
		char * l_methodName,
		char * l_templateName)
		: ActionAllBase(l_Debug, l_maxLen, l_methodName, l_templateName)
	{
		if (m_Debug != 0)
		{
			m_Debug->displayCtor(m_methodName, m_templateName, EVENT);
		}
		ClearLinkSelfArray();
	}

	ActionEventBase::~ActionEventBase()
	{
		Uvedomleniya();
	}

	void ActionEventBase::Uvedomleniya()
	{
		for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
		{
			if (LinkSelfArray[i] != 0)
			{   // Удалить ссылку на объект ActionEventBase
				LinkSelfArray[i]->DeleteActionEventLink(this);
			}
		}
	}

	void ActionEventBase::oper_PlusRavno_Link(ActionSelfBase & AS)
	{
		oper_PlusRavno_Ptr(&AS);
	}

	void ActionEventBase::oper_PlusRavno_Ptr(ActionSelfBase * AS)
	{
		if (AS == 0)
		{
			return;
		}
		ActionSelfBase * self = AS->GetThis();
		int freeIndex = GetFreeSelfIndex();
		if (self != 0 && freeIndex != -1)
		{
			if (m_Debug != 0)
			{
				m_Debug->displayNewValPtr(m_methodName, m_templateName);
			}
			AS->SetLinkActionEven(this);
			SetLinkActionSelf(self);
		}
		else
		{
			if (m_Debug != 0)
			{
				m_Debug->displayNewValError(m_methodName, m_templateName);
			}
		}
	}

	void ActionEventBase::oper_Functor(IArguments * i_args)
	{
		if (GetNotEmptySelfIndex() == -1)
		{
			if (m_Debug != 0)
			{
				m_Debug->displayFunktorError(m_methodName, m_templateName);
			}
			return;
		}
		if (m_Debug != 0)
		{
			for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
			{
				if (LinkSelfArray[i] != 0)
				{
					m_Debug->displayFunktor(m_methodName, m_templateName);
					LinkSelfArray[i]->Call(i_args); // Запускаем всех обработчиков событий
				}
			}
		}
		else
		{
			for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
			{
				if (LinkSelfArray[i] != 0)
				{
					LinkSelfArray[i]->Call(i_args); // Запускаем всех обработчиков событий
				}
			}
		}
	}

	void ActionEventBase::oper_MinusRavno_Link(ActionSelfBase & AS)
	{
		oper_MinusRavno_Ptr(&AS);
	}

	void ActionEventBase::oper_MinusRavno_Ptr(ActionSelfBase * AS)
	{
		if (AS == 0)
		{
			return;
		}
		ActionSelfBase * self = AS->GetThis();
		int selfIndex = GetSelfIndex(AS);
		if (self != 0 && selfIndex != -1)
		{
			self->DeleteActionEventLink(this); // Удалить ссылку на сябя (из обработчика событий)
			LinkSelfArray[selfIndex] = 0; // Удалить ссылку на обработчик события
		}
	}

	void ActionEventBase::DeleteActionSelfLink(ActionSelfBase * remoteSelf, int tip)
	{  // Удалить ссылку на объект ActionSelfBase
		int index = GetSelfIndex(remoteSelf);
		if (index >= 0)
		{
			if (m_Debug != 0)
			{
				m_Debug->displayDeleteLink(m_methodName, m_templateName);
			}
			LinkSelfArray[index] = 0;
		}
	}

	int ActionEventBase::GetSelfIndex(ActionSelfBase * remote)
	{
		for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
		{
			if (LinkSelfArray[i] == remote)
			{
				return i;
			}
		}
		return -1;
	}

	bool ActionEventBase::SetLinkActionSelf(ActionSelfBase * SelfLink)
	{
		int index = GetFreeSelfIndex();
		if (index == -1)
		{
			if (m_Debug != 0)
			{
				m_Debug->displaySetLinkError(m_methodName, m_templateName);
			}
			return false;
		}
		if (m_Debug != 0)
		{
			m_Debug->displaySetLink(m_methodName, m_templateName);
		}
		LinkSelfArray[index] = SelfLink;
		return true;
	}

	void ActionEventBase::ClearLinkSelfArray()
	{
		for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
		{
			LinkSelfArray[i] = 0;
		}
	}

	int ActionEventBase::GetFreeSelfIndex()
	{
		for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
		{
			if (LinkSelfArray[i] == 0)
			{
				return i;
			}
		}
		return -1;
	}

	int ActionEventBase::GetNotEmptySelfIndex()
	{
		for (int i = 0; i < MAX_SIZE_LINK_SELF; i++)
		{
			if (LinkSelfArray[i] != 0)
			{
				return i;
			}
		}
		return -1;
	}
}