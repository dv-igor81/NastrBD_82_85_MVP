//#pragma once
#ifndef __ARGUMENTS_AS_H
#define __ARGUMENTS_AS_H

#include "IArguments.h"
#include "NIL.h"

namespace smarteventsMin
{
	template<class P1, class P2 = NIL, class P3 = NIL, class P4 = NIL, class P5 = NIL, class P6 = NIL, class P7 = NIL, class P8 = NIL, class P9 = NIL, class P10 = NIL>
	class ArgumentsAS : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5, P6 i_arg6, P7 i_arg7, P8 i_arg8, P9 i_arg9, P10 i_arg10)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5),
			arg6(i_arg6), arg7(i_arg7), arg8(i_arg8), arg9(i_arg9), arg10(i_arg10)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
		P6 arg6;
		P7 arg7;
		P8 arg8;
		P9 arg9;
		P10 arg10;
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	class ArgumentsAS <P1, P2, P3, P4, P5, P6, P7, P8, P9> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5, P6 i_arg6, P7 i_arg7, P8 i_arg8, P9 i_arg9)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5),
			arg6(i_arg6), arg7(i_arg7), arg8(i_arg8), arg9(i_arg9)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
		P6 arg6;
		P7 arg7;
		P8 arg8;
		P9 arg9;
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	class ArgumentsAS <P1, P2, P3, P4, P5, P6, P7, P8> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5, P6 i_arg6, P7 i_arg7, P8 i_arg8)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5),
			arg6(i_arg6), arg7(i_arg7), arg8(i_arg8)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
		P6 arg6;
		P7 arg7;
		P8 arg8;
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	class ArgumentsAS <P1, P2, P3, P4, P5, P6, P7> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5, P6 i_arg6, P7 i_arg7)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5),
			arg6(i_arg6), arg7(i_arg7)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
		P6 arg6;
		P7 arg7;
	};

	template<class P1, class P2, class P3, class P4, class P5, class P6>
	class ArgumentsAS <P1, P2, P3, P4, P5, P6> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5, P6 i_arg6)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5),
			arg6(i_arg6)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
		P6 arg6;
	};

	template<class P1, class P2, class P3, class P4, class P5>
	class ArgumentsAS <P1, P2, P3, P4, P5> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4, P5 i_arg5)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4), arg5(i_arg5)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
		P5 arg5;
	};

	template<class P1, class P2, class P3, class P4>
	class ArgumentsAS <P1, P2, P3, P4> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3, P4 i_arg4)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3), arg4(i_arg4)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
		P4 arg4;
	};

	template<class P1, class P2, class P3>
	class ArgumentsAS <P1, P2, P3> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2, P3 i_arg3)
			: arg1(i_arg1), arg2(i_arg2), arg3(i_arg3)
		{}
		P1 arg1;
		P2 arg2;
		P3 arg3;
	};

	template< class P1, class P2 >
	class ArgumentsAS <P1, P2> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1, P2 i_arg2)
			: arg1(i_arg1), arg2(i_arg2)
		{}
		P1 arg1;
		P2 arg2;
	};

	template< class P1 >
	class ArgumentsAS <P1> : public IArguments
	{
	public:
		ArgumentsAS(P1 i_arg1) : arg1(i_arg1)
		{}
		P1 arg1;
	};
}
#endif // #ifndef __ARGUMENTS_AS_H