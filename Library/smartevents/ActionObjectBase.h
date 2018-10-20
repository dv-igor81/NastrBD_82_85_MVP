//#pragma once
// ActionSelf.h ---> ActionAllAndActionDebugSettingsBase
#ifndef __ACTION_OBJECT_BASE_H
#define __ACTION_OBJECT_BASE_H
namespace smartevents
{
	class ActionObjectBase
	{
	public:
		ActionObjectBase(int l_maxLen);
		~ActionObjectBase();
		int GetMaxLength(); // Получить максимально-допустимую длинну
		int GetLengText(const char * ptrText); // Получить длинну строки (оканчивающююся нулевым символом)
		char * CreateText(int size = 0); // Выделить память под строку
		void DeleteText(const char * ptrText); // Освободить память, выделенную под строку
		void ClearText(char * ptrText); // Заполнить все символы строки нулями
		void SpaseText(char * ptrText); // Заполнить все символы строки пробелами
		int AddText( // To := To + From
			char * ptrTo, 
			const char * ptrFrom, 
			int lenTo);
		void CopyText( // To := From
			char * ptrTo, 
			const char * ptrFrom); 
		char * CloneText(const char * ptrText);
		virtual void ErrorMessageShortString(int iVal) = 0;
	private:
		int _MaxLength;
	};
}
#endif // #ifndef __ACTION_OBJECT_BASE_H