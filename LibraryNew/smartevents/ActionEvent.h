//#pragma once
#ifndef __ACTION_EVENT_H
#define __ACTION_EVENT_H

#include "ActionEventBase.h"
#include "ArgumentsAS.h"
#include "ActionSelf.h"

namespace smarteventsMin
{
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
	class ActionEvent : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8, T9 i_arg9, T10 i_arg10) 
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8, i_arg9, i_arg10));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>;
	};

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	class ActionEvent <T1, T2, T3, T4, T5, T6, T7, T8, T9> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8, T9 i_arg9)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8, T9>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8, i_arg9));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8, T9>;
	};

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	class ActionEvent <T1, T2, T3, T4, T5, T6, T7, T8> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7, T8 i_arg8)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7, T8>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7, i_arg8));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5, T6, T7, T8>;
	};

	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	class ActionEvent <T1, T2, T3, T4, T5, T6, T7> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6, T7 i_arg7)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5, T6, T7>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6, i_arg7));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6, T7> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6, T7> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5, T6, T7>;
	};

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	class ActionEvent <T1, T2, T3, T4, T5, T6> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5, T6 i_arg6)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5, T6>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5, i_arg6));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5, T6> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5, T6> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5, T6>;
	};

	template<class T1, class T2, class T3, class T4, class T5>
	class ActionEvent <T1, T2, T3, T4, T5> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4, T5 i_arg5)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4, T5>(i_arg1, i_arg2, i_arg3, i_arg4, i_arg5));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4, T5> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4, T5> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4, T5>;
	};

	template<class T1, class T2, class T3, class T4>
	class ActionEvent <T1, T2, T3, T4> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3, T4 i_arg4)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3, T4>(i_arg1, i_arg2, i_arg3, i_arg4));
		}
		void operator+=(ActionSelf<T1, T2, T3, T4> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3, T4> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3, T4> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3, T4>;
	};

	template<class T1, class T2, class T3>
	class ActionEvent <T1, T2, T3> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2, T3 i_arg3)
		{
			oper_Functor(&ArgumentsAS<T1, T2, T3>(i_arg1, i_arg2, i_arg3));
		}
		void operator+=(ActionSelf<T1, T2, T3> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2, T3> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2, T3> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2, T3>;
	};

	template<class T1, class T2>
	class ActionEvent <T1, T2> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1, T2 i_arg2)
		{
			oper_Functor(&ArgumentsAS<T1, T2>(i_arg1, i_arg2));
		}
		void operator+=(ActionSelf<T1, T2> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1, T2> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1, T2> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1, T2> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1, T2>;
	};

	template<class T1>
	class ActionEvent <T1> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(T1 i_arg1)
		{
			oper_Functor(&ArgumentsAS<T1>(i_arg1));
		}
		void operator+=(ActionSelf<T1> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<T1> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<T1> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<T1> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<T1>;
	};

	
	template<>
	class ActionEvent <> : public ActionEventBase
	{
	public:
		ActionEvent(){} // Конструктор
		~ActionEvent(){} // Деструктор
		void operator()(void)
		{
			oper_Functor(0);
		}
		void operator+=(ActionSelf<> & AS)
		{
			oper_PlusRavno_Link(AS);
		}
		void operator+=(ActionSelf<> * AS)
		{
			oper_PlusRavno_Ptr(AS);
		}
		void operator-=(ActionSelf<> & AS)
		{
			oper_MinusRavno_Link(AS);
		}
		void operator-=(ActionSelf<> * AS)
		{
			oper_MinusRavno_Ptr(AS);
		}
	private:
		friend class ActionSelf<>;
	};	
}

#endif // #ifndef __ACTION_EVENT_H