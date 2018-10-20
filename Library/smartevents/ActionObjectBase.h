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
		int GetMaxLength(); // �������� �����������-���������� ������
		int GetLengText(const char * ptrText); // �������� ������ ������ (�������������� ������� ��������)
		char * CreateText(int size = 0); // �������� ������ ��� ������
		void DeleteText(const char * ptrText); // ���������� ������, ���������� ��� ������
		void ClearText(char * ptrText); // ��������� ��� ������� ������ ������
		void SpaseText(char * ptrText); // ��������� ��� ������� ������ ���������
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