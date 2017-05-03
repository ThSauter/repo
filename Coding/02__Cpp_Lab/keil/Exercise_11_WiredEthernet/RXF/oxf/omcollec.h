//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMCollection
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2008. All Rights Reserved.
//


#ifndef omcollec_H
#define omcollec_H

//## class OMCollection
#include "OMStaticArray.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMCollection
// A dynamic array
template <class Concept> class OMCollection : public OMStaticArray<Concept> {
public :

    //#[ type DEFAULT_START_SIZE
    #define DEFAULT_START_SIZE 20
    //#]
    
    //#[ type DEFAULT_FACTOR
    #define DEFAULT_FACTOR 2
    //#]
    
    ////    Constructors and destructors    ////
    
    // copy constructor and assignment operator
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation OMCollection(const OMCollection<Concept> & )
    explicit inline OMCollection(const OMCollection<Concept> & aCollection) : OMStaticArray<Concept>(0) {
        //#[ operation OMCollection(const OMCollection<Concept> & )
        copy(aCollection);
        //#]
    }
    
    // Constructor
    // Argument const sint32 theSize = DEFAULT_START_SIZE :
    // The array initial size
    //## operation OMCollection(sint32)
    explicit inline OMCollection(const sint32 theSize = DEFAULT_START_SIZE) : OMStaticArray<Concept>(theSize)  {
        //#[ operation OMCollection(sint32)
        //#]
    }
    
    ////    Operations    ////
    
    // Add an element to the end of the array
    // Argument Concept aConcept :
    // The element to add
    //## operation add(Concept)
    inline void add(Concept aConcept) {
        //#[ operation add(Concept)
        if (this->count >= this->size) {
        	reorganize();
        }
        this->theLink[this->count] = aConcept;
        this->count++;
        //#]
    }
    
    // add new element if in range, without increase of the container size.
    // Argument const sint32 anIndex :
    // The index
    // Argument Concept aConcept :
    // The element to add
    //## operation addAt(sint32,Concept)
    inline void addAt(const sint32 anIndex, Concept aConcept) {
        //#[ operation addAt(sint32,Concept)
        if (anIndex >= 0) {
        	if (this->count > anIndex) {
        		this->theLink[anIndex] = aConcept;
        	} else {
        		if ( (anIndex == this->count) && 
        	  		 (this->size > this->count) ) {
        			this->theLink[this->count] = aConcept;
        			this->count++; 
        		}
        	}
        }
        //#]
    }
    
    // Assignment operator
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation operator=(const OMCollection<Concept> & )
    inline OMCollection<Concept> & operator=(const OMCollection<Concept> & aCollection) {
        //#[ operation operator=(const OMCollection<Concept> & )
        copy(aCollection);
        return *this;
        //#]
    }
    
    // Remove p from the array
    // Argument Concept aConcept :
    // The element to remove
    //## operation remove(Concept)
    inline void remove(Concept aConcept) {
        //#[ operation remove(Concept)
        // Delete aCount
        for (sint32 i = 0; i < this->count; i++) {
        	if (this->theLink[i] == aConcept) { 
        		removeByIndex(i);
        		// assuming no duplicates
        		break;
        	}
        }
        //#]
    }
    
    // Cleanup the array
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
    	WST_MEM::returnMemory(this->theLink);
        this->count = 0;
        this->size = DEFAULT_START_SIZE;
        this->theLink = static_cast<Concept*>(WST_MEM::getMemory(sizeof(Concept) * this->size));
        //#]
    }
    
    // Remove the element at the specified index
    // Argument const sint32 i :
    // The index
    //## operation removeByIndex(sint32)
    inline void removeByIndex(const sint32 i) {
        //#[ operation removeByIndex(sint32)
        this->count--;
        this->theLink[i] = this->theLink[this->count];
        //#]
    }
    
    // Reset the collection size
    // Argument const sint32 factor = DEFAULT_FACTOR :
    // resize factor
    //## operation reorganize(sint32)
    inline void reorganize(const sint32 factor = DEFAULT_FACTOR) {
        //#[ operation reorganize(sint32)
        sint32 f;
        if (factor < 1) {
        	f = 1;
        } else {
            f = factor;
        }
        this->size = (this->count * f) + 1;
        Concept* tmpLink = static_cast<Concept*>( WST_MEM::getMemory(sizeof(Concept) * this->size) );
        for (sint32 i = 0; i < this->count; i++) {
        	tmpLink[i] = this->theLink[i];
        }
        WST_MEM::returnMemory(this->theLink);
        this->theLink = tmpLink;
        //#]
    }
    

private :

    // Copy a collection
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation copy(const OMCollection<Concept> & )
    inline void copy(const OMCollection<Concept> & aCollection) {
        //#[ operation copy(const OMCollection<Concept> & )
        OMStaticArray<Concept>::copy(aCollection);
        //#]
    }
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMCollection

#endif
//
//! Log: $Log$
//

