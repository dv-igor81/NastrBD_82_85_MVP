#include "ActionDebugSettings.h"
#include "ArgumentsAS.h"

#define MAX_SIZE_FOR_DEBUG_SETTINGS_LENGTH 250

namespace smartevents
{
	template<class TC, class M>
	ActionDebugSettings::ActionDebugSettings(TC * i_class, M i_method) :
		ActionDebugSettingsBase(MAX_SIZE_FOR_DEBUG_SETTINGS_LENGTH)
		, m_Message(CreateText())
		, m_DebugEvent(0)
	{
		typedef void (TC::*M)(char *);
		m_caller = new ContainerAS<TC, M, char *>(i_class, i_method);
	}

	ActionDebugSettings::~ActionDebugSettings()
	{
		DeleteText(m_Message);
	}

	void ActionDebugSettings::display(char * text)
	{
		m_caller->Call(&ArgumentsAS<char *>(text));
	}

	int ActionDebugSettings::DebugFunkActionEvent()
	{
		return m_DebugEvent;
	}

	void ActionDebugSettings::DebugFunkActionSelfError(char * Message)
	{
		display(Message);
	}

	void ActionDebugSettings::DebugFunkActionEventError(char * Message)
	{
		display(Message);
	}

	void ActionDebugSettings::ErrorMessageShortString(int iVal)
	{
		switch (iVal)
		{
		case 1:
			display("ќшибка! int ActionDebugSettingsBase::AddText(ptrTo, ptrFrom): ptrTo > Max");
			break;
		case 2:
			display("ќшибка! int ActionDebugSettingsBase::AddText(ptrTo, ptrFrom): ptrFrom > Max");
			break;
		case 3:
			display("ќшибка! int ActionDebugSettingsBase::AddText(ptrTo, ptrFrom): ptrTo + ptrFrom > Max");
			break;
		default:
			display("ќшибка! int ActionDebugSettingsBase: неизвестна€ ошибка");
			break;
		}
	}

	void ActionDebugSettings::displayCtor(
		const char * m_methodName,
		const char * m_templateName,
		int TypeAction)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = GetLengText(m_Message);// 0
		const char * strTypeAction = 0;
		switch (TypeAction)
		{
		case SELF:
			strTypeAction = "ActionSelf";
			break;
		case EVENT:
			strTypeAction = "ActionEvent";
			break;
		}
		pos = AddText(m_Message, strTypeAction, pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - конструктор; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayDestr(
		const char * m_methodName,
		const char * m_templateName,
		int TypeAction)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = GetLengText(m_Message);// 0
		const char * strTypeAction = 0;
		switch (TypeAction)
		{
		case SELF:
			strTypeAction = "ActionSelf";
			break;
		case EVENT:
			strTypeAction = "ActionEvent";
			break;
		}
		pos = AddText(m_Message, "~", pos);
		pos = AddText(m_Message, strTypeAction, pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - деструктор; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayDeleteLink(
		const char * m_methodName,
		const char * m_templateName,
		int TypeDel,
		int TypeAction)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		if (TypeAction == EVENT)
		{
			pos = AddText(m_Message, "ActionEvent", pos);
			pos = AddText(m_Message, m_templateName, pos);
			switch (TypeDel)
			{
			case 0:
				pos = AddText(m_Message, ": удал€ю ссылку на себ€ (причина - деструктор); ", pos);
				break;
			case 1:
				pos = AddText(m_Message, ": удал€ю ссылку на себ€ (причина - присвоение нул€); ", pos);
				break;
			case 2:
				pos = AddText(m_Message, ": удал€ю ссылку на себ€ (причина - присвоение по указателю); ", pos);
				break;
			case 3:
				pos = AddText(m_Message, ": удал€ю ссылку на себ€ (причина - присвоение по ссылке); ", pos);
				break;
			case 4:
				pos = AddText(m_Message, ": ќбъект ActionSelf уничтожаетс€; ", pos);
				break;
			default:
				pos = AddText(m_Message, ": удал€ю ссылку на себ€ (???  ак мы вообще сюда попали ???); ", pos);
				break;
			}
			pos = AddText(m_Message, m_methodName, pos);
		}
		display(m_Message);
	}

	void ActionDebugSettings::displayFunktor(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "ActionEvent - void operator()", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, "; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayFunktorError(
		const char * m_methodName,
		const char * m_templateName)
	{
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "ќшибка: ActionEvent - void operator()", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, "; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayNewValLink(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "ActionEvent", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, ": новое значение ActionSelf присвоено (= &); ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayNewValPtr(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "ActionEvent", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, ": новое значение ActionSelf присвоено (= *); ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayNewValError(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "ќшибка ActionEvent", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, "! - не удалось получить ActionSelf; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayCall(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "          ActionSelf - void operator()", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, "; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayCallError(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "          ActionSelf - void operator()", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - ќЎ»Ѕ ј; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displaySetLink(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "          ActionSelf", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - присвоен метод; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displaySetLinkError(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "          ActionSelf", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - ошибка присвоени€: нет места дл€ ссылки; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::displayDeleteLink(
		const char * m_methodName,
		const char * m_templateName)
	{
		if (m_DebugEvent == 0)
		{
			return;
		}
		ClearText(m_Message);
		int pos = 0;
		pos = AddText(m_Message, "          ActionSelf", pos);
		pos = AddText(m_Message, m_templateName, pos);
		pos = AddText(m_Message, " - разрываю св€сь с методом; ", pos);
		pos = AddText(m_Message, m_methodName, pos);
		display(m_Message);
	}

	void ActionDebugSettings::SetDisplayEvent(int iVar)
	{
		m_DebugEvent = iVar;
	}
}