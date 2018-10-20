#include "ActionSelfBase.h"
#include "ActionEventBase.h"

namespace smartevents
{
	ActionSelfBase::ActionSelfBase(
		IContainer * container,
		ActionDebugSettings * l_Debug,
		int l_maxLen,
		char * l_methodName, 
		char * l_templateName)				
		: ActionAllBase(l_Debug, l_maxLen, l_methodName, l_templateName)
	{
		if (m_Debug != 0)
		{
			m_Debug->displayCtor(m_methodName, m_templateName, SELF);
		}
		m_container = container;
		ClearLinkEventArray();
	}

	ActionSelfBase::~ActionSelfBase()
	{
		if (m_Debug != 0)
		{
			m_Debug->displayDestr(m_methodName, m_templateName, SELF);
		}
		if (m_container != 0)
		{
			delete m_container;
		}
		Uvedomleniya();
	}

	ActionSelfBase * ActionSelfBase::GetThis()
	{
		int index = GetFreeEventIndex();
		if (index == -1)
		{
			return 0;
		}
		return this;
	}

	void ActionSelfBase::Call(IArguments * i_args)
	{
		if (m_container == 0)
		{
			if (m_Debug != 0)
			{
				m_Debug->displayCallError(m_methodName, m_templateName);
			}
		}
		else
		{
			if (m_Debug != 0)
			{
				m_Debug->displayCall(m_methodName, m_templateName);
			}
			m_container->Call(i_args);
		}
	}

	void ActionSelfBase::Uvedomleniya()
	{
		for (int i = 0; i < MAX_SIZE_LINK_EVENT; i++)
		{
			if (LinkEventArray[i] != 0)
			{
				LinkEventArray[i]->DeleteActionSelfLink(this, 4);
			}
		}
	}

	void ActionSelfBase::DeleteActionEventLink(ActionEventBase * remoteEvent)
	{ // Удалить ссылку на объект ActionEventBase
		int index = GetEventIndex(remoteEvent);
		if (index >= 0)
		{
			if (m_Debug != 0)
			{
				m_Debug->displayDeleteLink(m_methodName, m_templateName);
			}
			LinkEventArray[index] = 0;
		}
	}

	bool ActionSelfBase::SetLinkActionEven(ActionEventBase * EventLink)
	{
		int index = GetFreeEventIndex();
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
		LinkEventArray[index] = EventLink;
		return true;
	}

	void ActionSelfBase::ClearLinkEventArray()
	{
		for (int i = 0; i < MAX_SIZE_LINK_EVENT; i++)
		{
			LinkEventArray[i] = 0;
		}
	}

	int ActionSelfBase::GetEventIndex(ActionEventBase * remote)
	{
		for (int i = 0; i < MAX_SIZE_LINK_EVENT; i++)
		{
			if (LinkEventArray[i] == remote)
			{
				return i;
			}
		}
		return -1;
	}

	int ActionSelfBase::GetFreeEventIndex()
	{
		for (int i = 0; i < MAX_SIZE_LINK_EVENT; i++)
		{
			if (LinkEventArray[i] == 0)
			{
				return i;
			}
		}
		return -1;
	}
}
