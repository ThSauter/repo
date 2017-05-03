/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Poti
//!	Generated Date	: Wed, 5, Apr 2017  
	File Path	: MCB1700\Debug\Poti.h
*********************************************************************/

#ifndef Poti_H
#define Poti_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## link itsBoard
class Board;

//## package Default

//## class Poti
class Poti : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Poti()
    Poti(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Poti();
    
    ////    Operations    ////
    
    //## operation sample()
    void sample();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getAdcValue() const;
    
    //## auto_generated
    void setAdcValue(int p_adcValue);
    
    //## auto_generated
    int getPotiValue() const;
    
    //## auto_generated
    void setPotiValue(int p_potiValue);
    
    //## auto_generated
    int getSampleInterval() const;
    
    //## auto_generated
    void setSampleInterval(int p_sampleInterval);
    
    //## auto_generated
    Board* getItsBoard() const;
    
    //## auto_generated
    void setItsBoard(Board* p_Board);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);

private :

    //## auto_generated
    int getAdcFullRangeDeflection() const;
    
    //## auto_generated
    void setAdcFullRangeDeflection(int p_AdcFullRangeDeflection);
    
    //## auto_generated
    int getLastPotiValue() const;
    
    //## auto_generated
    void setLastPotiValue(int p_lastPotiValue);
    
    ////    Attributes    ////

protected :

    int AdcFullRangeDeflection;		//## attribute AdcFullRangeDeflection
    
    int adcValue;		//## attribute adcValue
    
    int lastPotiValue;		//## attribute lastPotiValue
    
    int potiValue;		//## attribute potiValue
    
    int sampleInterval;		//## attribute sampleInterval
    
    ////    Relations and components    ////
    
    Board* itsBoard;		//## link itsBoard
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void __setItsBoard(Board* p_Board);
    
    //## auto_generated
    void _setItsBoard(Board* p_Board);
    
    //## auto_generated
    void _clearItsBoard();
    
    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Sample:
    //## statechart_method
    inline bool Sample_IN() const;
    
    // Hold:
    //## statechart_method
    inline bool Hold_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Poti_Enum {
        OMNonState = 0,
        Sample = 1,
        Hold = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool Poti::rootState_IN() const {
    return true;
}

inline bool Poti::Sample_IN() const {
    return rootState_subState == Sample;
}

inline bool Poti::Hold_IN() const {
    return rootState_subState == Hold;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Poti.h
*********************************************************************/
