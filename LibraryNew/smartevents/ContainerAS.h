//#pragma once
#ifndef __CONTAINER_AS_H
#define __CONTAINER_AS_H

#include "IContainer.h"
#include "ArgumentsAS.h"
#include "NIL.h"

namespace smarteventsMin
{
	template<class T, class M, class P1 = NIL, class P2 = NIL, class P3 = NIL, class P4 = NIL, class P5 = NIL, class P6 = NIL, class P7 = NIL, class P8 = NIL, class P9 = NIL, class P10 = NIL>
	class ContainerAS : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5, args->arg6, args->arg7, args->arg8, args->arg9, args->arg10);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	class ContainerAS <T, M, P1, P2, P3, P4, P5, P6, P7, P8, P9> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8, P9); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8, P9> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5, args->arg6, args->arg7, args->arg8, args->arg9);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	class ContainerAS <T, M, P1, P2, P3, P4, P5, P6, P7, P8> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5, args->arg6, args->arg7, args->arg8);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	class ContainerAS <T, M, P1, P2, P3, P4, P5, P6, P7> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5, args->arg6, args->arg7);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4, class P5, class P6>
	class ContainerAS <T, M, P1, P2, P3, P4, P5, P6> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5, args->arg6);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4, class P5>
	class ContainerAS <T, M, P1, P2, P3, P4, P5> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4, P5); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4, args->arg5);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3, class P4>
	class ContainerAS <T, M, P1, P2, P3, P4> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3, P4); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3, P4> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3, args->arg4);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template<class T, class M, class P1, class P2, class P3>
	class ContainerAS <T, M, P1, P2, P3> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2, P3); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2, P3> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M, class P1, class P2> // Специализация для методов с двумя аргументами
	class ContainerAS <T, M, P1, P2> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2); // Определяем тип "M"
		typedef ArgumentsAS<P1, P2> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M, class P1 > // Специализация для методов с одним аргументом
	class ContainerAS <T, M, P1> : public IContainer
	{
	private:
		typedef void (T::*M)(P1); // Определяем тип "M"
		typedef ArgumentsAS<P1> A; // Определяем тип "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - используется, для специализации c аргументами
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M > // Специализация для методов без аргумента
	class ContainerAS< T, M > : public IContainer
	{
	private:
		typedef void (T::*M)(void); // Определяем тип "M"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}	
		void Call(IArguments *)
		{
			// IArguments - не используется, для специализации без аргументов
			(_m_class->*_m_method)();
		}
	private:
		M _m_method;
		T * _m_class;
	};
}

#endif // #ifndef __CONTAINER_AS_H