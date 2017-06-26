/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: SDCard
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\SDCard.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "SDCard.h"
//## link itsClock
#include "Clock.h"
//## link itsDisplay
#include "Display.h"
//## package DefaultPkg

//## class SDCard
int SDCard::counter(0);

const char* SDCard::fileName = {"DemoFile.txt"};

SDCard::SDCard(WST_TSK* myTask) {
    joystickPos = 0x00;
    setTask( myTask, false );
    itsClock = NULL;
    itsDisplay = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 107, (void*)&counter);
    
}

SDCard::~SDCard() {
    cleanUpRelations();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void SDCard::append(char position) {
    //#[ operation append(char)
    FILE *f;
    char str[40]; 
    const char* direction;
    
    switch(position)
    {
    	case Joystick_LEFT: 
    		direction = "LEFT"; 
    		break;
    	case Joystick_UP: 
    		direction = "UP"; 
    		break;
    	case Joystick_RIGHT: 
    		direction = "RIGHT";
    		break;
    	case Joystick_DOWN: 
    		direction = "DOWN";
    		break;
    	case Joystick_SELECT: 
    	default:
    		return;
    }
     
    // Open a file for appending -> "a"
    f = fopen (fileName, "a");               
    if (f == NULL) {
    	// error when trying to open file
    	FIRE(this->itsDisplay, evSDLog2("Can not open file.                ")); 
    	FIRE(this, evError());  
    	return;
    }  
    
    // Format string
    sprintf(str, "[%02d:%02d:%02d] # %3d: %s\n", 
    		itsClock->getHour(), 
    		itsClock->getMin(), 
    		itsClock->getSec(), 
    		counter, 
    		direction);
    fprintf (f, "%s", str);
        
    if (fflush (f)) {
    	// Error when trying to flush file
    	fclose (f);
    	FIRE(this->itsDisplay, evSDLog2("Can not flush file.               "));     
    	FIRE( this, evError()); 
    	return;
    }
    
    // Close the output file
    fclose (f);                          	
    
    FIRE(this->itsDisplay, evSDLog2((OMString)"W: " + str));
    //#]
}

void SDCard::deleteFile() {
    //#[ operation deleteFile()
    fsStatus status;
    
    status = fdelete (fileName, NULL);
    
    if (status == fsOK) {
    	FIRE(this->itsDisplay, evSDLog2("Delete successful.                "));   
    }
    else if (status == fsFileNotFound) { 
    	FIRE(this->itsDisplay, evSDLog2("File not found.                   "));
    	FIRE(this, evError());   	
    }
    else {
    	FIRE(this->itsDisplay, evSDLog2("Delete failed.                    "));
    	FIRE(this, evError());   	
    }
    //#]
}

void SDCard::initAndMount() {
    //#[ operation initAndMount()
    fsStatus stat;
    
    // Initialize and mount drive "M0"
    stat = finit ("M0:");
    if (stat == fsOK) {
    	stat = fmount ("M0:");
    	if (stat == fsOK) {
    		FIRE(this->itsDisplay, evSDLog2("Drive M0 ready!                   "));
    	}
    	else if (stat == fsNoFileSystem) {
    		// Format the drive
    		FIRE(this->itsDisplay, evSDLog2("Drive M0 not formatted!           "));
    		//cmd_format ("M0:");
    	}
    	else {
    		FIRE(this->itsDisplay, evSDLog2("Drive M0 mount failed!            "));
    	}
    }
    else {
    	FIRE(this->itsDisplay, evSDLog2("Drive M0 initialization failed!   "));
    }
    //#]
}

void SDCard::read() {
    //#[ operation read()
    FILE *f;
    char line[25];
    char line2[25];     
    
    f = fopen (fileName,"r"); 
    
    if (f != NULL)  {
    while (fgets (line, sizeof (line), f) != NULL)  {
      strcpy(line, line2);
    }  
    
    fclose (f);
    }
    
    //#]
}

int SDCard::getCounter() {
    return counter;
}

void SDCard::setCounter(int p_counter) {
    counter = p_counter;
}

char SDCard::getJoystickPos() const {
    return joystickPos;
}

void SDCard::setJoystickPos(char p_joystickPos) {
    joystickPos = p_joystickPos;
}

Clock* SDCard::getItsClock() const {
    return itsClock;
}

void SDCard::setItsClock(Clock* p_Clock) {
    itsClock = p_Clock;
}

Display* SDCard::getItsDisplay() const {
    return itsDisplay;
}

void SDCard::setItsDisplay(Display* p_Display) {
    itsDisplay = p_Display;
}

bool SDCard::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void SDCard::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void SDCard::cleanUpRelations() {
    if(itsClock != NULL)
        {
            itsClock = NULL;
        }
    if(itsDisplay != NULL)
        {
            itsDisplay = NULL;
        }
}

const char* SDCard::getFileName() {
    return fileName;
}

void SDCard::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = Initialize;
        rootState_active = Initialize;
        //#[ state Initialize.(Entry) 
        initAndMount();
        //#]
    }
}

IOxfReactive::TakeEventStatus SDCard::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Log
        case Log:
        {
            if(IS_EVENT_TYPE_OF(evJoystickPos_DefaultPkg_id))
                {
                    OMSETPARAMS(evJoystickPos);
                    //## transition 4 
                    if(params->joystickPosition == Joystick_SELECT)
                        {
                            //#[ state Log.(Exit) 
                            counter++;
                            //#]
                            //#[ transition 0 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Confirm_Delete;
                            rootState_active = Confirm_Delete;
                            //#[ state Confirm_Delete.(Entry) 
                            FIRE(this->itsDisplay, evSDLog2("Press SELECT again to delete file."));
                            //#]
                            res = eventConsumed;
                        }
                    else
                        {
                            //#[ state Log.(Exit) 
                            counter++;
                            //#]
                            //#[ transition 0 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Log;
                            rootState_active = Log;
                            //#[ state Log.(Entry) 
                            append(joystickPos);
                            //#]
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evError_DefaultPkg_id))
                {
                    //#[ state Log.(Exit) 
                    counter++;
                    //#]
                    //#[ transition 11 
                    counter--;
                    //#]
                    pushNullTransition();
                    rootState_subState = Initialize;
                    rootState_active = Initialize;
                    //#[ state Initialize.(Entry) 
                    initAndMount();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        // State Initialize
        case Initialize:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    popNullTransition();
                    rootState_subState = Read;
                    rootState_active = Read;
                    //#[ state Read.(Entry) 
                    read();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        // State Confirm_Delete
        case Confirm_Delete:
        {
            if(IS_EVENT_TYPE_OF(evJoystickPos_DefaultPkg_id))
                {
                    OMSETPARAMS(evJoystickPos);
                    //## transition 6 
                    if(params->joystickPosition == Joystick_SELECT)
                        {
                            //#[ transition 5 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Delete_File;
                            rootState_active = Delete_File;
                            //#[ state Delete_File.(Entry) 
                            deleteFile();    
                            
                            //#]
                            res = eventConsumed;
                        }
                    else
                        {
                            //#[ transition 5 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Log;
                            rootState_active = Log;
                            //#[ state Log.(Entry) 
                            append(joystickPos);
                            //#]
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State Delete_File
        case Delete_File:
        {
            if(IS_EVENT_TYPE_OF(evJoystickPos_DefaultPkg_id))
                {
                    OMSETPARAMS(evJoystickPos);
                    //## transition 10 
                    if(params->joystickPosition == Joystick_SELECT)
                        {
                            //#[ state Delete_File.(Exit) 
                            counter=0;
                            //#]
                            //#[ transition 8 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Delete_File;
                            rootState_active = Delete_File;
                            //#[ state Delete_File.(Entry) 
                            deleteFile();    
                            
                            //#]
                            res = eventConsumed;
                        }
                    else
                        {
                            //#[ state Delete_File.(Exit) 
                            counter=0;
                            //#]
                            //#[ transition 8 
                            joystickPos=params->joystickPosition;
                            //#]
                            rootState_subState = Log;
                            rootState_active = Log;
                            //#[ state Log.(Entry) 
                            append(joystickPos);
                            //#]
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State Read
        case Read:
        {
            if(IS_EVENT_TYPE_OF(evJoystickPos_DefaultPkg_id))
                {
                    OMSETPARAMS(evJoystickPos);
                    //#[ transition 2 
                    joystickPos=params->joystickPosition;
                    //#]
                    rootState_subState = Log;
                    rootState_active = Log;
                    //#[ state Log.(Entry) 
                    append(joystickPos);
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\SDCard.cpp
*********************************************************************/
