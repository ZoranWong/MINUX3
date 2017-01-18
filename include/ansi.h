/* The <ansi.h> header attempts to decide whether the compiler has enough
 * conformance to Standard C for Minix to take advantage of.  If so, the
 * symbol _ANSI is defined (as 31459).  Otherwise _ANSI is not defined
 * here, but it may be defined by applications that want to bend the rules.
 * The magic number in the definition is to inhibit unnecessary bending
 * of the rules.  (For consistency with the new '#ifdef _ANSI" tests in
 * the headers, _ANSI should really be defined as nothing, but that would
 * break many library routines that use "#if _ANSI".)

 * If _ANSI ends up being defined, a macro
 *
 *	_PROTOTYPE(function, params)
 *
 * is defined.  This macro expands in different ways, generating either
 * ANSI Standard C prototypes or old-style K&R (Kernighan & Ritchie)
 * prototypes, as needed.  Finally, some programs use _CONST, _VOIDSTAR etc
 * in such a way that they are portable over both ANSI and K&R compilers.
 * The appropriate macros are defined here.
 */
//<ansi.h>的作用是测试编译器是否符合ISO规定的标准C（ANSI C）的要求。
#ifndef _ANSI_H
#define _ANSI_H	//特征测试宏

#if __STDC__ == 1			//标准C编译器定义的一个宏
#define _ANSI		31459	/* compiler claims full ANSI conformance */
#endif

#ifdef __GNUC__				//GNU C一定满足ANSI C的要求
#define _ANSI		31459	/* gcc conforms enough even in non-ANSI mode */
#endif

#ifdef _ANSI
//如果满足ANSI C标准，则使用ANSI C的函数原型。对函数的输入参数进行
//严格的类型检查。
/* Keep everything for ANSI prototypes. */
#define	_PROTOTYPE(function, params)	function params
#define	_ARGS(params)			params

#define	_VOIDSTAR	void *
#define	_VOID		void
#define	_CONST		const
#define	_VOLATILE	volatile
#define _SIZET		size_t

#else
//用于老式（K&R C）编译器，编译器只会记住函数的返回类型，关于参数个
//数以及类型，编译器不管。
/* Throw away the parameters for K&R prototypes. */
#define	_PROTOTYPE(function, params)	function()
#define	_ARGS(params)			()

#define	_VOIDSTAR	void *
#define	_VOID		void
#define	_CONST
#define	_VOLATILE
#define _SIZET		int

#endif /* _ANSI */

/* This should be defined as restrict when a C99 compiler is used. */
#define _RESTRICT
// 如果设置了_MINIX, _POSIX_C_SOURCE 或 _POSIX2_SOURCE其中任意一个，
// 就意味着_POSIX_SOURCE，（但把它放在这个文件里，好像有点问题）
/* Setting any of _MINIX, _POSIX_C_SOURCE or _POSIX2_SOURCE implies
 * _POSIX_SOURCE.  (Seems wrong to put this here in ANSI space.)
 */
#if defined(_MINIX) || _POSIX_C_SOURCE > 0 || defined(_POSIX2_SOURCE)
#undef _POSIX_SOURCE //特征测试宏
#define _POSIX_SOURCE	1
#endif

#endif /* ANSI_H */
