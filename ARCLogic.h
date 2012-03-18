//
//  ARCLogic.h
//	

#ifndef ARCLOGIC
#define ARCLOGIC

#ifdef HASARC
#undef HASARC
#endif
#ifdef HASWEAK
#undef HASWEAK
#endif
#ifdef STRONG
#undef STRONG
#endif
#ifdef __STRONG
#undef __STRONG
#endif
#ifdef WEAK
#undef WEAK
#endif
#ifdef __WEAK
#undef __WEAK
#endif

#define HASARC __has_feature(objc_arc)

#define HASWEAK __has_feature(objc_arc_weak)

#if HASARC
	#define IF_ARC(ARCBlock, NoARCBlock) ARCBlock
	#define NO_ARC(NoARCBlock) 
	#define STRONG strong
	#define __STRONG __strong
	#if HASWEAK
		#define __WEAK __weak
		#define WEAK weak
		#define NO_WEAK(NoWeakBlock) 
	#else
		#define WEAK assign
		#define __WEAK __unsafe_unretained
		#define NO_WEAK(NoWeakBlock) NoWeakBlock
	#endif
#else
	#define IF_ARC(ARCBlock, NoARCBlock) NoARCBlock
	#define NO_ARC(NoARCBlock) NoARCBlock
	#define STRONG retain
	#define __STRONG 
	#define WEAK assign
	#define __WEAK 
	#define NO_WEAK(NoWeakBlock) NoWeakBlock
#endif

#endif
