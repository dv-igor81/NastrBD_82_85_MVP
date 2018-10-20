//#pragma once
#ifndef __ACTION_SELF_H
#define __ACTION_SELF_H

#include "ActionSelfBase.h"
#include "ContainerAS.h"
#include "NIL.h"

namespace smartevents
{
	template<class T1 = NIL, class T2 = NIL, class T3 = NIL, class T4 = NIL, class T5 = NIL, class T6 = NIL, class T7 = NIL, class T8 = NIL, class T9 = NIL, class T10 = NIL>
	class ActionEvent; // ѕредварительное объ€вление

	// "”казатель" на нестатическую функцию-член класса, имеющую 10 входных параметров
	// и возвращающую void
	template<class T1 = NIL, class T2 = NIL, class T3 = NIL, class T4 = NIL, class T5 = NIL, class T6 = NIL, class T7 = NIL, class T8 = NIL, class T9 = NIL, class T10 = NIL>
	class ActionSelf : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T10)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8, T9 i_arg9, T10 i_arg10)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8, i_arg9, i_arg10));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 9 входных параметров
	// и возвращающую void
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	class ActionSelf <T1, T2, T3, T4, T5, T6, T7, T8, T9> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5, T6, T7, T8, T9>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T9)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8, T9 i_arg9)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8, T9>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8, i_arg9));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5, T6, T7, T8, T9>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 8 входных параметров
	// и возвращающую void
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	class ActionSelf <T1, T2, T3, T4, T5, T6, T7, T8> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5, T6, T7, T8>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T8)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5, T6, T7, T8>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 7 входных параметров
	// и возвращающую void
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	class ActionSelf <T1, T2, T3, T4, T5, T6, T7> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5, T6, T7>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T7)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5, T6, T7>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 6 входных параметров
	// и возвращающую void
	template<class T1, class T2, class T3, class T4, class T5, class T6>
	class ActionSelf <T1, T2, T3, T4, T5, T6> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5, T6>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T6)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5, T6>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5, T6>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 5 входных параметров
	// и возвращающую void
	template<class T1, class T2, class T3, class T4, class T5>
	class ActionSelf <T1, T2, T3, T4, T5> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4, T5>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T5)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4, T5>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5));
		}
		friend class ActionEvent<T1, T2, T3, T4, T5>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 4 входных параметра
	// и возвращающую void
	template<class T1, class T2, class T3, class T4>
	class ActionSelf <T1, T2, T3, T4> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3, T4>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T4)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4)
		{
			Call(&ArgumentsAS<T1, T2, T3, T4>(i_arg1, i_arg2, i_arg3, i_arg4));
		}
		friend class ActionEvent<T1, T2, T3, T4>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 3 входных параметра
	// и возвращающую void
	template<class T1, class T2, class T3>
	class ActionSelf <T1, T2, T3> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2, T3>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1 ... T3)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3)
		{
			Call(&ArgumentsAS<T1, T2, T3>(i_arg1, i_arg2, i_arg3));
		}
		friend class ActionEvent<T1, T2, T3>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 2 входных параметра
	// и возвращающую void
	template<class T1, class T2>
	class ActionSelf <T1, T2> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1, T2>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1, T2)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1, T2 i_arg2)
		{
			Call(&ArgumentsAS<T1, T2>(i_arg1, i_arg2));
		}
		friend class ActionEvent<T1, T2>;
	};

	// "”казатель" на нестатическую функцию-член класса, имеющую 1 входной параметр
	// и возвращающую void
	template<class T1>
	class ActionSelf <T1> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M, T1>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(T1)")
		{}
		~ActionSelf(){}
		void operator()(T1 i_arg1)
		{
			Call(&ArgumentsAS<T1>(i_arg1));
		}
		friend class ActionEvent<T1>;
	};

	
	// "”казатель" на нестатическую функцию-член класса, имеющую 0 входных параметров
	// и возвращающую void
	template<>
	class ActionSelf <> : public ActionSelfBase
	{
	public:
		template<class TC, class M>
		ActionSelf(TC * i_class, M i_method, ActionDebugSettings * l_Debug = 0, char * l_methodName = 0) :
			ActionSelfBase(new ContainerAS<TC, M>(i_class, i_method),
				l_Debug, MAX_SIZE_FOR_ACTION_TEXT_LENGTH, l_methodName, "(void)")
		{}
		~ActionSelf(){}
		void operator()()
		{
			Call(0);
		}
		friend class ActionEvent<>;
	};
	
}

#endif // #ifndef __ACTION_SELF_H