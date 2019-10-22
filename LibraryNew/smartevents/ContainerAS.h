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
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8, P9); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8, P9> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7, P8); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7, P8> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6, P7); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6, P7> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4, P5, P6); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5, P6> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4, P5); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4, P5> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3, P4); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3, P4> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
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
		typedef void (T::*M)(P1, P2, P3); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2, P3> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2, args->arg3);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M, class P1, class P2> // ������������� ��� ������� � ����� �����������
	class ContainerAS <T, M, P1, P2> : public IContainer
	{
	private:
		typedef void (T::*M)(P1, P2); // ���������� ��� "M"
		typedef ArgumentsAS<P1, P2> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1, args->arg2);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M, class P1 > // ������������� ��� ������� � ����� ����������
	class ContainerAS <T, M, P1> : public IContainer
	{
	private:
		typedef void (T::*M)(P1); // ���������� ��� "M"
		typedef ArgumentsAS<P1> A; // ���������� ��� "A"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}
		void Call(IArguments * i_args)
		{
			// IArguments - ������������, ��� ������������� c �����������
			A * args = static_cast<A*>(i_args);
			(_m_class->*_m_method)(args->arg1);
		}
	private:
		M _m_method;
		T * _m_class;
	};

	template< class T, class M > // ������������� ��� ������� ��� ���������
	class ContainerAS< T, M > : public IContainer
	{
	private:
		typedef void (T::*M)(void); // ���������� ��� "M"
	public:
		ContainerAS(T * l_class, M l_method) : _m_class(l_class), _m_method(l_method)
		{}	
		void Call(IArguments *)
		{
			// IArguments - �� ������������, ��� ������������� ��� ����������
			(_m_class->*_m_method)();
		}
	private:
		M _m_method;
		T * _m_class;
	};
}

#endif // #ifndef __CONTAINER_AS_H