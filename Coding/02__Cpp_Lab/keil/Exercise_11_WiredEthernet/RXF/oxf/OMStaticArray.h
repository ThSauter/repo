//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMStaticArray
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2008. All Rights Reserved.
//


#ifndef OMStaticArray_H
#define OMStaticArray_H

//## class OMStaticArray
#include "OMAbstractContainer.h"
//## dependency OMIterator
#include "OMIterator.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMStaticArray
// A fixed-size safe array
template <class Concept> class OMStaticArray : public OMAbstractContainer<Concept> {
    ////    Constructors and destructors    ////
    
public :

    // copy constructor
    // Argument const OMStaticArray<Concept> & anArray :
    // The array to copy
    //## operation OMStaticArray(const OMStaticArray<Concept> & )
    inline OMStaticArray(const OMStaticArray<Concept> & anArray) : count(0), size(0), theLink(NULL) {
        //#[ operation OMStaticArray(const OMStaticArray<Concept> & )
        copy(anArray);
        //#]
    }
    
    // Initialize an array of a given size
    // Argument const sint32 theSize :
    // The array size
    //## operation OMStaticArray(sint32)
    inline OMStaticArray(const sint32 theSize) : count(0), size(theSize), theLink(NULL) {
        //#[ operation OMStaticArray(sint32)
        if (size > 0) {
        	theLink = static_cast<Concept*>(WST_MEM::getMemory(sizeof(Concept) * theSize));
        }
        //#]
    }
    
    // Destructor	
    //## operation ~OMStaticArray()
    inline virtual ~OMStaticArray(void) {
        //#[ operation ~OMStaticArray()
    	WST_MEM::returnMemory(theLink);
        theLink = NULL;
        count = 0;
        size = 0;
        //#]
    }
    
    ////    Operations    ////
    
    // Add an element to the array
    // Argument Concept aConcept :
    // The element
    //## operation add(Concept)
    inline void add(Concept aConcept) {
        //#[ operation add(Concept)
        theLink[count] = aConcept;
        count = count + 1;
        //#]
    }
    
    // Find if p in the collection
    // Argument Concept aConcept :
    // The element to find
    //## operation find(Concept) const
    inline bool find(Concept aConcept) const {
        //#[ operation find(Concept) const
        bool status = false;
        
        for (sint32 i = 0; i < count; i++) {
        	if (theLink[i] == aConcept) {
        		status = true;
        		break;
        	}
        }
        return status;
        //#]
    }
    
    // Get the element in the specified index
    // Argument const sint32 anIndex :
    // The index
    //## operation getAt(sint32) const
    inline Concept & getAt(const sint32 anIndex) const {
        //#[ operation getAt(sint32) const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if ( (anIndex >= 0) && (anIndex < count) ) {
          	return theLink[anIndex];
        } else {
            return OMNullValue<Concept>::get();
        }
        //#]
    }
    
    // Check if the array is empty
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (count == 0);
        //#]
    }
    
    // Assignment operator
    // Argument const OMStaticArray<Concept> & anArray :
    // The array to copy
    //## operation operator=(const OMStaticArray<Concept> & )
    inline OMStaticArray<Concept> & operator=(const OMStaticArray<Concept> & anArray) {
        //#[ operation operator=(const OMStaticArray<Concept> & )
        copy(anArray);
        return (*this);
        //#]
    }
    
    // Get the element in the specified index
    // Argument const sint32 anIndex :
    // The index
    //## operation operator[](sint32) const
    inline Concept & operator[](const sint32 anIndex) const {
        //#[ operation operator[](sint32) const
        return getAt(anIndex);
        //#]
    }
    
    // Clear the array
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        count = 0;
        //#]
    }
    
    // Set the element at the given index.
    // The index should be smaller then the number of elements currently located in the array
    // Argument const sint32 anIndex :
    // The index
    // Argument Concept aConcept :
    // The element
    //## operation setAt(sint32,Concept)
    inline void setAt(const sint32 anIndex, Concept aConcept) {
        //#[ operation setAt(sint32,Concept)
        if ( (anIndex >= 0) && (anIndex < count) ) {
        	theLink[anIndex] = aConcept;
        }
        //#]
    }
    

protected :

    // Copy an array
    // Argument const OMStaticArray<Concept> & aClone :
    // The array to copy
    //## operation copy(const OMStaticArray<Concept> & )
    inline void copy(const OMStaticArray<Concept> & aClone) {
        //#[ operation copy(const OMStaticArray<Concept> & )
        if (theLink != aClone.theLink) {
        	// avoid self copy
        	if (theLink != NULL) {
        		// cleanup before copy
        		WST_MEM::returnMemory(theLink);
        	}
        
        	count = aClone.count;
        	size = aClone.size;
        	theLink = static_cast<Concept*>(WST_MEM::getMemory(sizeof(Concept) * size));
        
        	for (sint32 i = 0; i < count; ++i) {
        		theLink[i] = aClone.theLink[i];
        	}
        }
        //#]
    }
    
    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The iterator position
    //## operation getCurrent(void *) const
    inline virtual Concept& getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        sint32 index = (sint32)((sint32)(pos));
        return getAt(index);
        //#]
    }
    
    // Set the initial position for the iterator
    // Argument void *& pos :
    // The array[0] address (out)
    //## operation getFirst(void *) const
    inline virtual void getFirst(void *& pos) const {
        //#[ operation getFirst(void *) const
        pos = reinterpret_cast<void*>(0);
        //#]
    }
    
    // Update the provided position to the next position in the container
    // Argument void *& pos :
    // The iterator position to advance
    //## operation getNext(void *) const
    inline virtual void getNext(void *& pos) const {
        //#[ operation getNext(void *) const
        pos = reinterpret_cast<void*>(reinterpret_cast<uint32>(pos) + 1U);
        //#]
    }
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    inline sint32 getCount(void) const {
        //#[ auto_generated
        return count;
        //#]
    }
    
    //## auto_generated
    inline sint32 getSize(void) const {
        //#[ auto_generated
        return size;
        //#]
    }
    
    ////    Attributes    ////
    

protected :

    // The number of elements currently placed in the array
    sint32 count;		//## attribute count
    
    // The array total size
    sint32 size;		//## attribute size
    
    // The underlying C array
    Concept* theLink;		//## attribute theLink
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMStaticArray

#endif
//
//! Log: $Log$
//


