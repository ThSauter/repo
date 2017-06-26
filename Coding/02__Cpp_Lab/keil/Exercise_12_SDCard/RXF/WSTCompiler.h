#ifndef WSTCOMPILER_H
#define WSTCOMPILER_H

/**
*  Compiler specific settings like defines, typedefs and eventually needed functions or data are
* specified in WSTCompiler.
* 
* \ingroup Adaptation
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTCompiler.h 34418 2016-05-12 15:36:02Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/CompilerAndTarget/Keil5_ARM/Source/Common/WSTCompiler.h $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/


#include "WSTCompilerTypes.h"

#define WST_COMPILER_INIT_AS_EMPTY_MACRO						/**< we do not need a WSTCompiler_Init()	*/

/** Define OMitoa for Rhapsody compatibility, note: limited to radix==10. do-while(0)-construct because of MISRA-2004 */
/* @MISRA_19.7=OFF PD-0002: Using function-like macros is needed to map certain symbols for compatibility with the Rhapsody code generator and to have runtime efficient code. */
#define	OMitoa( val, str, radix ) 	do {\
		sprintf( (str), "%d", (val) )	\
	} while(0)
/* @MISRA_19.7=ON */



/** This typedef is just for Rhapsody compatibility, even if it actually makes little sense	*/
typedef unsigned long	 WST_UINT64;			



/* Types used in the framework, which are depending on toolchain:
 */
typedef boolean			WSTBoolean;			/**< Boolean type for Rhapsody compatibility 						*/
typedef char			WSTHandle;			/**< Rhapsody compatibility: Data type to store a handle			*/
typedef void * 			gen_ptr;			/**< Generic pointer used by the RXF (e.g. in containers classes)	*/
typedef sint16			WST_EVT_ID_t;		/**< Event identifier, used by the RXF 								*/
typedef uint32			WST_TimeUnit_t;		/**< Time counter unit, used by the RXF								*/


 
typedef size_t		MALLOC_ARGUMENT_TYPE;	/**< Type of the argument, which is passed to malloc()		 		*/
typedef void *		MALLOC_RETURN_TYPE;		/**< Return type of malloc()		 								*/

typedef void *		FREE_ARGUMENT_TYPE;		/**< Type of the argument, which is passed to free()		 		*/
typedef void		FREE_RETURN_TYPE;		/**< Return type of free()									 		*/


/** 
 * \brief Value to correctly handle timer overflows.
 *
 * The calculation for overflow in timeouts uses the constant WST_TM_OVERFLOW,
 * which value depends on the defined type WST_TimeUnit_t. Use the appropriate constant:
 */
#define WST_TM_OVERFLOW		((WST_TimeUnit_t) INT_MAX)




/**
 * \brief The macros WST_NEARD, WST_FARD, WST_NEARC and WST_FARC are used in declarations, 
 * for those toolchains which support 'near' and 'far' keywords.
 *
 * We distinguish between data and code, hence the 'D' or 'C' in the macros.
 *
 * Because one may not use the sizeof() operator in preprocessor macro expressions, we must define
 * some size macros to be used to trigger the proper the memory type macros used in the framework:
 * - the size of pointers which are using this 'near' or 'far'. 
 * - the size of a WST_TimeUnit_t
 * 
 * In the framework code, which is not specific for a toolchain, 
 * we test on the size and START/STOP the proper section macro.
 * Please note that the sizeof() operator may not be used in the "macro size definitions".
 * 
 */ 
#define WST_NEARD
#define WST_FARD						/**< \see WST_NEARD */ 		
#define WST_NEARC						/**< \see WST_NEARD */
#define WST_FARC						/**< \see WST_NEARD */

#define WST_NEARD_ADDRESS_SIZE		32	/**< \see WST_NEARD */
#define WST_FARD_ADDRESS_SIZE		32	/**< \see WST_NEARD */
#define WST_NEARC_ADDRESS_SIZE		32	/**< \see WST_NEARD */
#define WST_FARC_ADDRESS_SIZE		32	/**< \see WST_NEARD */
#define WST_TIMEUNIT_ADDRESS_SIZE	32	/**< \see WST_NEARD */


/**
  * Allows to define a type or storage class specifier, which is used in front of RXF data declarations.
  * It can be used to e.g. specify something compiler specific like __no_init to skip zero initialization.
  */
#define WST_VAR_TYPE_SPECIFIER          

/**
  * Allows to define a compiler specific inline operation specifier, which is used in front of RXF operations
  * which may make sense to declare as inline functions.
  * The MISRA-C-2004 check with PC-lint might report a rule 19.4 violation here, but is is a define to a
  * compiler specific storage class, which is allowed as described in the MISRA-C-2004 standard for rule 19.4.
  */
#define WST_INLINE_OP __forceinline


/** Not each toolchain has TRUE and FALSE defined in the same include file;
 * if these are not defined yet, define them ourselves.
 */
#ifndef TRUE
#define TRUE  1
#endif

/** \see TRUE */
#ifndef FALSE
#define FALSE 0
#endif

#endif /* WSTCOMPILER_H */

