//#pragma once
#ifndef __ACTION_SELF_BASE_H
#define __ACTION_SELF_BASE_H

#include "ActionAllBase.h"

namespace smarteventsMin
{
	class ActionEventBase; // ��������������� ����������
	class ActionSelfBase // ����� ����������/����������� �������
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
		ActionEventBase * LinkEventArray[MAX_SIZE_LINK_EVENT]; // ������, �������� �������, ��� ������� �������� ���������/����������
		IContainer * m_container;
		friend class ActionEventBase;
	};
}
#endif // #ifndef __ACTION_SELF_BASE_H