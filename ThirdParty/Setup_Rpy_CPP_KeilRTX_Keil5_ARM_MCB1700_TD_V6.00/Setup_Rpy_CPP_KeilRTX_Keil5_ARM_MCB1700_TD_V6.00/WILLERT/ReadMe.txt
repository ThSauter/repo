
            == I M P O R T A N T   N O T E S ==


INSTALLATION AND PREREQUISITES

Setup.exe which will guide you through the product installation
of Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00.
Please make sure the following Software is already installed:

- IBM Rational Rhapsody
  (Tested with version 8.1.4)

- Keil MDK-ARM for Cortex-M3
  (Tested with version V5.18)

- Keil RTX (RL-ARM)
  (Tested with version V4.60)


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
 
- If the Keil ARM Simulator is used instead of a hardware board,
  the Target Debugger only allows monitoring the target behavior.
  Injection of events etc. is only possible in combination with ARM
  hardware.
- Keil MDK 5 does not include the RTX Real Time Library anymore. Instead it allows
  installing an CMSIS-RTOS compatible RTX package via the package manager. 
  The RXF for CMSIS-RTOS is available. However the RXF version you currently have
  is adapted to the Legacy RTOS. 
  Please install the legacy Keil RTX package, to still have access to the Keil RTX
  and it's full featured RTOS interface: http://www2.keil.com/mdk5/legacy
  With this legacy package the Keil RTX is supported together with MDK-ARM V5.
  


- The current implementation of the WSTMonitor causes restrictions
  regarding code roundtripping. It is planned to solve this issue
  in the near future. The WSTMonitor is required to communicate
  with the Embedded UML Target Debugger. 

  Currently the Target Debugger monitor part (C++ code on target)
  has problems to receive commands via Keil UVSOCK.
  When used in C++ code, the Keil UVSOCK interface seems to skip
  some bytes during data reception. As a workaround all communication
  from Target Debugger (host) to C++ Monitor (target) is
  deactivated. Several Target Debugger features (e.g. query
  attributes, query states, suspend, set filters and breakpoints)
  are currently not available in the C++ evaluation version.
  We are in contact with Keil and trying to solve this problem
  with the Keil UVSOCK communication interface.




