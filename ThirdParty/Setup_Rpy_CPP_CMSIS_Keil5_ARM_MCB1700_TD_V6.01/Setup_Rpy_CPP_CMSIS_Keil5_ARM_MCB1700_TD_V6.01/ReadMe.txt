
            == I M P O R T A N T   N O T E S ==


INSTALLATION AND PREREQUISITES

Setup.exe which will guide you through the product installation
of Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01.
Please make sure the following Software is already installed:

- IBM Rational Rhapsody
  (Tested with version 8.1.5)

- Keil MDK-ARM
  (Tested with version V5.21a)

- Keil CMSIS RTOS
  (Tested with version V4.81.0)


FIRST STEPS

Please refer to the Help file index.htm, which is available
after installation via the menu
Start | Programs | Willert Software Tools RXF <your product>:

- the Introduction | Restrictions section shows you what you can 
  expect from the product and what restrictions apply.

- the Usage section describes how to build a sample project.


KNOWN ISSUES

- if you deploy your generated files while you have the simulator or debugger
  active in uVision, the uVision project file might get corrupted.
  Please close the simulator or debug session first before you deploy files!
  If there is a problem with the project file you can use the latest backup
  which can be automatically created by the Deployer.

- If ITM interface is used to communicate with the Target
  Debugger, the Monitor part must be executed in privileged
  mode.
 

- The current implementation of the WSTMonitor causes restrictions
  regarding code roundtripping. It is planned to solve this issue
  in the near future. The WSTMonitor is required to communicate
  with the Embedded UML Target Debugger. 

  Currently the Target Debugger monitor part (C++ code on target)
  has problems to receive commands via Keil UVSOCK.
  When used in C++ code, the Keil UVSOCK interface seems to skip
  some bytes during data reception. Several Target Debugger features (e.g. query
  attributes, query states, suspend, set filters and breakpoints)
  may cause problems in the current C++ version.



