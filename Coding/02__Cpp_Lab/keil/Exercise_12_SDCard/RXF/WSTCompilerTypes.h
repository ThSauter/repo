#ifndef WSTTYPEDEFINITIONS_H
#define WSTTYPEDEFINITIONS_H


/**
* \brief Definition file for integer data types, in a similar way AUTOSAR defines them.
* 
* This allows to use data types in an application without dependency to the target
* and compiler specific data type widths.
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTCompilerTypes.h 32886 2015-08-20 11:38:42Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/CompilerAndTarget/Keil5_ARM/Source/Common/WSTCompilerTypes.h $
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



/*
 * AUTOSAR integer data types
 */
typedef signed char         sint8;          /**<        -128 .. +127            */
typedef unsigned char       uint8;          /**<           0 .. 255             */
typedef signed short        sint16;         /**<      -32768 .. +32767          */
typedef unsigned short      uint16;         /**<           0 .. 65535           */
typedef signed int			sint32;         /**< -2147483648 .. +2147483647     */
typedef unsigned int		uint32;         /**<           0 .. 4294967295      */
typedef float               float32;
typedef double              float64;

typedef unsigned char       uint8_least;    /**< At least 8 bit                 */
typedef unsigned short      uint16_least;   /**< At least 16 bit                */
typedef unsigned int		uint32_least;   /**< At least 32 bit                */
typedef signed char         sint8_least;    /**< At least 7 bit + 1 bit sign    */
typedef signed short        sint16_least;   /**< At least 15 bit + 1 bit sign   */
typedef signed int			sint32_least;   /**< At least 31 bit + 1 bit sign   */

typedef bool				boolean;        /**< for use with TRUE/FALSE. bool type is supported in C++ only by ARM */

typedef char      			char_t;	        /**< type for character data 								*/
typedef int					int_t;			/**< type for integers, used to align memory pool blocks,	*/
											/**< see RiC_MemoryAllocationPkg.h						*/
/* PC-lint might report a MISRA Rule 20.2 violation in the following line. This is a false positive, as MISRA does not completely disallow that naming pattern. */
typedef unsigned int		struct_t;		/**< Used to cast structure pointers to (struct_t*)		*/
											/**< e.g. before performing arithmetic operations			*/

#define	WSTTRUE	true
#define	WSTFALSE false

#if !defined(__size_t)
  #define __size_t 1
  typedef unsigned int size_t;   /* see <stddef.h> */
#endif


#endif  /* of WSTTYPEDEFINITIONS_H */
