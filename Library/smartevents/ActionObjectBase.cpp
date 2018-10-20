#include "ActionObjectBase.h"

namespace smartevents
{
	ActionObjectBase::ActionObjectBase(int l_maxLen)
		: _MaxLength(l_maxLen){}

	ActionObjectBase::~ActionObjectBase(){}

	int ActionObjectBase::GetMaxLength()
	{
		return _MaxLength;
	}

	int ActionObjectBase::GetLengText(const char * ptrText)
	{
		if (ptrText == 0)
		{
			return 0;
		}
		int retVal = -1;
		for (int i = 0; i <= _MaxLength; i++)
		{
			if (ptrText[i] == 0)
			{
				retVal = i;
				break;
			}
		}
		return retVal;
	}

	char * ActionObjectBase::CreateText(int size)
	{
		char * text;
		if (size <= 0)
		{
			text = 0;
		}
		else if (size >= _MaxLength)
		{ // Ограничение в _MaxLength
			text = new char[_MaxLength + 1];
		}
		else
		{
			text = new char[size + 1];
		}
		return text;
	}

	void ActionObjectBase::DeleteText(const char * ptrText)
	{
		if (ptrText != 0)
		{
			delete[] ptrText;
		}
	}

	void ActionObjectBase::ClearText(char * ptrText)
	{
		for (int i = 0; i <= _MaxLength; i++)
		{
			ptrText[i] = 0;
		}
	}

	void ActionObjectBase::SpaseText(char * ptrText)
	{
		for (int i = 0; i < _MaxLength; i++)
		{
			ptrText[i] = ' ';
		}
		ptrText[_MaxLength] = 0;
	}

	int ActionObjectBase::AddText(
		char * ptrTo, 
		const char * ptrFrom, 
		int lenTo)
	{
		if (lenTo < 0)
		{
			ErrorMessageShortString(1);
			return -1;
		}
		int lenFrom = GetLengText(ptrFrom);
		if (lenFrom == 0)
		{
			ErrorMessageShortString(2);
			return -1;
		}
		int lenSum = lenTo + lenFrom;
		if (lenSum > GetMaxLength())
		{
			ErrorMessageShortString(3);
			return -1;
		}
		int i, j;
		for (i = lenTo, j = 0; i < lenSum; i++, j++)
		{
			ptrTo[i] = ptrFrom[j];
		}
		ptrTo[i] = 0;
		return lenSum;
	}

	void ActionObjectBase::CopyText(
		char * ptrTo,
		const char * ptrFrom)
	{
		AddText(ptrTo, ptrFrom, 0);
	}

	char * ActionObjectBase::CloneText(const char * ptrText)
	{
		int len = GetLengText(ptrText);
		char * text = CreateText(len);
		CopyText(text, ptrText);
		return text;
	}
}