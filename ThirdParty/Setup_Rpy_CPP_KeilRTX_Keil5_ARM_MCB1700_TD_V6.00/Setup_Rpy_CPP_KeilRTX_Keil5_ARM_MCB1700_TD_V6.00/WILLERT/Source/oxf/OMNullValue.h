//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMNullValue
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2008. All Rights Reserved.
//


#ifndef OMNullValue_H
#define OMNullValue_H

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMNullValue
// Empty value class - used by containers to return non-existing element
template <class Concept> class OMNullValue {
    ////    Operations    ////
    
public :

    // Get the empty value
    //## operation get()
    inline static Concept & get(void) {
        //#[ operation get()
        	static sint32 nullSet = 0;
        	static uint8 nillValue[sizeof(Concept)];
        	if (nullSet == 0) {
        		// need to zero the array 
        		nullSet = 1; 
        		for (uint32 i = 0U; i < (sizeof(Concept)); ++i) {
        			nillValue[i] = 0;
        		}
        	}
        	return ((Concept&)(*nillValue));
        //#]
    }
    
    // Ensure that the OMContainersNullBlock is initialized
    //## operation initNullBlock()
    //#[ ignore
    //#]
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMNullValue

#endif
//
//! Log: $Log$
//


