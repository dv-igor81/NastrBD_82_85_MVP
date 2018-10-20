//#pragma once
#ifndef __ACTION_DEBUG_SETTINGS_H
#define __ACTION_DEBUG_SETTINGS_H

#include "ActionObjectBase.h"
#include "IContainer.h"

#define SELF 1
#define EVENT 2

namespace smartevents
{
	class ActionDebugSettings : public ActionObjectBase
	{
	public:
		template<class TC, class M> ActionDebugSettings(TC * i_class, M i_method);

		~ActionDebugSettings();
		void display(char * text);
		int DebugFunkActionEvent();
		void DebugFunkActionSelfError(char * Message);
		void DebugFunkActionEventError(char * Message);
		void ErrorMessageShortString(int iVal); // virtual
		void displayCtor(
			const char * m_methodName,
			const char * m_templateName,
			int TypeAction);
		void displayDestr(
			const char * m_methodName,
			const char * m_templateName,
			int TypeAction);
		void displayDeleteLink( // Удаление ссылки
			const char * m_methodName,
			const char * m_templateName,
			int TypeDel,
			int TypeAction);
		void displayFunktor(
			const char * m_methodName,
			const char * m_templateName);
		void displayFunktorError(
			const char * m_methodName,
			const char * m_templateName);
		void displayNewValLink(
			const char * m_methodName,
			const char * m_templateName);
		void displayNewValPtr(
			const char * m_methodName,
			const char * m_templateName);
		void displayNewValError(
			const char * m_methodName,
			const char * m_templateName);
		void displayCall(
			const char * m_methodName,
			const char * m_templateName);
		void displayCallError(
			const char * m_methodName,
			const char * m_templateName);
		void displaySetLink(
			const char * m_methodName,
			const char * m_templateName);
		void displaySetLinkError(
			const char * m_methodName,
			const char * m_templateName);
		void displayDeleteLink(
			const char * m_methodName,
			const char * m_templateName);
		void SetDisplayEvent(int iVar);
	private:
		IContainer * m_caller;
		char * m_Message;
		int m_DebugEvent;
	};
}
#endif // #ifndef __ACTION_DEBUG_SETTINGS_H