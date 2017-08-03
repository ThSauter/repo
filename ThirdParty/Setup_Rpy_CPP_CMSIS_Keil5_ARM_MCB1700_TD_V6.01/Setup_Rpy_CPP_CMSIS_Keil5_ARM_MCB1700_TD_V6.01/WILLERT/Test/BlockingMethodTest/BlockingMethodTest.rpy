I-Logix-RPY-Archive version 8.6.0 C 2071424
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
	- _name = "BlockingMethodTest";
	- _UserColors = { IRPYRawContainer 
		- size = 16;
		- value = 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 
	}
	- _defaultSubsystem = { ISubsystemHandle 
		- _m2Class = "ISubsystem";
		- _filename = "ExamplePkg.sbs";
		- _subsystem = "";
		- _class = "";
		- _name = "ExamplePkg";
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
		- size = 4;
		- value = 
		{ IMultiplicityItem 
			- _name = "1";
			- _count = 1;
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
	}
	- Subsystems = { IRPYRawContainer 
		- size = 3;
		- value = 
		{ ISubsystem 
			- fileName = "ExamplePkg";
			- _id = GUID 44aa1857-ce12-4fcb-bce5-045353898d04;
		}
		{ IProfile 
			- fileName = "Rpy_C_embOS_IAR_RX_Profile";
			- _persistAs = "@WILLERT_3@\\Rpy_C_embOS_IAR_RX_Dev\\Config\\UserSettings\\Rpy_C_embOS_IAR_RX_Profile_rpy";
			- _id = GUID ccbaa044-c563-69b9-1a81-2eac1ac0bbb8;
			- _name = "Rpy_C_embOS_IAR_RX_Dev_Profile";
			- _isReference = 1;
		}
		{ IProfile 
			- fileName = "WSTProfile";
			- _persistAs = "@WILLERT_3@\\Rpy_C_embOS_IAR_RX_Dev\\Config\\UserSettings\\Rpy_C_embOS_IAR_RX_Profile_rpy";
			- _id = GUID 839b3570-feed-482e-8776-cdf59c7831ae;
			- _isReference = 1;
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

