I-Logix-RPY-Archive version 8.11.0 C 8254044
{ IProject 
	- _id = GUID fab1930c-d4a3-428e-927c-2e1a62109790;
	- _myState = 8192;
	- _properties = { IPropertyContainer 
		- Subjects = { IRPYRawContainer 
			- size = 1;
			- value = 
			{ IPropertySubject 
				- _Name = "General";
				- Metaclasses = { IRPYRawContainer 
					- size = 1;
					- value = 
					{ IPropertyMetaclass 
						- _Name = "Model";
						- Properties = { IRPYRawContainer 
							- size = 1;
							- value = 
							{ IProperty 
								- _Name = "DiagramIsSavedUnit";
								- _Value = "True";
								- _Type = Bool;
							}
						}
					}
				}
			}
		}
	}
	- _name = "MetaTest";
	- _modifiedTimeWeak = 2.10.2015::10:18:4;
	- _lastID = 5;
	- _UserColors = { IRPYRawContainer 
		- size = 16;
		- value = 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 
	}
	- _defaultSubsystem = { ISubsystemHandle 
		- _m2Class = "ISubsystem";
		- _filename = "TestPart01_PEPS_Pkg.sbs";
		- _subsystem = "";
		- _class = "";
		- _name = "TestPart01_PEPS_Pkg";
		- _id = GUID 44aa1857-ce12-4fcb-bce5-045353898d04;
	}
	- _component = { IHandle 
		- _m2Class = "IComponent";
		- _filename = "TargetComponent.cmp";
		- _subsystem = "";
		- _class = "";
		- _name = "TargetComponent";
		- _id = GUID e0d637fa-b61c-449c-b72d-414f989ee17d;
	}
	- Multiplicities = { IRPYRawContainer 
		- size = 6;
		- value = 
		{ IMultiplicityItem 
			- _name = "1";
			- _count = 4;
		}
		{ IMultiplicityItem 
			- _name = "*";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "0,1";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "1..*";
			- _count = -1;
		}
		{ IMultiplicityItem 
			- _name = "MAX_CHILD_INSTANCES";
			- _count = 3;
		}
		{ IMultiplicityItem 
			- _name = "MAX_";
			- _count = 0;
		}
	}
	- Subsystems = { IRPYRawContainer 
		- size = 9;
		- value = 
		{ ISubsystem 
			- fileName = "TestPart01_PEPS_Pkg";
			- _id = GUID 44aa1857-ce12-4fcb-bce5-045353898d04;
		}
		{ IProfile 
			- fileName = "Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_Profile";
			- _persistAs = "@WILLERT_3@\\@WST_RELEASE_NAME@\\Config\\UserSettings\\@WST_PRODUCT_NAME@_Profile_rpy";
			- _id = GUID 12831e05-d580-d500-2767-cffc5fe8467e;
			- _name = "Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_Profile";
			- _isReference = 1;
		}
		{ IProfile 
			- fileName = "WSTProfile";
			- _persistAs = "@WILLERT_3@\\@WST_RELEASE_NAME@\\Config\\UserSettings\\@WST_PRODUCT_NAME@_Profile_rpy";
			- _id = GUID 1cf73d66-e129-d1bb-9e84-fbe96f0e3ebf;
			- _isReference = 1;
		}
		{ IProfile 
			- fileName = "WST_CG_Profile";
			- _persistAs = "@WILLERT_3@\\@WST_RELEASE_NAME@\\Config\\UserSettings\\@WST_PRODUCT_NAME@_Profile_rpy";
			- _id = GUID 198390c0-3c25-77ce-027f-7a374fb23d02;
			- _isReference = 1;
		}
		{ ISubsystem 
			- fileName = "TestControlPkg";
			- _id = GUID ee3f34d3-1d0b-49dd-bca6-3631afdaf2dd;
		}
		{ ISubsystem 
			- fileName = "TestPart02_Port_Pkg";
			- _id = GUID 3559ce7c-db2d-41e2-8907-7b1b8ba8a2f4;
		}
		{ ISubsystem 
			- fileName = "TestPart03_FSM_Pkg";
			- _id = GUID 8eef82d3-8196-4d69-9161-ace95470bedd;
		}
		{ ISubsystem 
			- fileName = "TestPart04_Huge_Pkg";
			- _id = GUID 67957628-6fd5-4ea6-9181-568bf774d976;
		}
		{ ISubsystem 
			- fileName = "TestPart05_CON_Pkg";
			- _id = GUID 64521002-3f4b-4ae2-9a50-4d0c2606c2ec;
		}
	}
	- Diagrams = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IDiagram 
			- fileName = "Overview";
			- _id = GUID 54d91baf-17b9-4e35-a4cf-14c09c9fb24a;
		}
	}
	- Components = { IRPYRawContainer 
		- size = 1;
		- value = 
		{ IComponent 
			- fileName = "TargetComponent";
			- _id = GUID e0d637fa-b61c-449c-b72d-414f989ee17d;
		}
	}
}

