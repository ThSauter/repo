I-Logix-RPY-Archive version 8.5.2 C 2030848
{ IProject 
	- _id = GUID 66d27327-94a9-467e-aa47-e266b73dc3aa;
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
	- _name = "Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_Profile";
	- _description = { IDescription 
		- _text = "
Configuration Management Infos:

$Id: RXFProfile.rpy 33643 2016-02-03 15:52:31Z eroemer $
$URL: https://svn.willert.de/V6/trunk/Component/Modelling/Rpy/Config/UserSettings/RXFProfile.rpy $

";
	}
	- _lastID = 1;
	- _UserColors = { IRPYRawContainer 
		- size = 16;
		- value = 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 16777215; 
	}
	- _defaultSubsystem = { ISubsystemHandle 
		- _m2Class = "ISubsystem";
		- _id = GUID 6ce23edf-1de8-49a7-9695-7c3c26da9baa;
	}
	- _component = { IHandle 
		- _m2Class = "IComponent";
		- _id = GUID bf2f1f2f-ab20-43a3-8e86-646cd71760ab;
	}
	- Multiplicities = { IRPYRawContainer 
		- size = 4;
		- value = 
		{ IMultiplicityItem 
			- _name = "1";
			- _count = -1;
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
			- _id = GUID 6ce23edf-1de8-49a7-9695-7c3c26da9baa;
			- _myState = 8192;
			- _name = "NotUsedPkg";
			- _description = { IDescription 
				- _text = "This Rhapsody model only includes the RXF Product Profile and is used to maintain it. However, Rhapsody requires every model to include at least one package, component and configurations. This is why the \"empty\" model elements \"NotUsedPkg\", \"NotUsedComponent\" and \"NotUsedConfiguration\" are part of the model.";
			}
			- Declaratives = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IComponent 
					- _id = GUID bf2f1f2f-ab20-43a3-8e86-646cd71760ab;
					- _myState = 139264;
					- _name = "NotUsedComponent";
					- _description = { IDescription 
						- _text = "This Rhapsody model only includes the RXF Product Profile and is used to maintain it. However, Rhapsody requires every model to include at least one package, component and configurations. This is why the \"empty\" model elements \"NotUsedPkg\", \"NotUsedComponent\" and \"NotUsedConfiguration\" are part of the model.";
					}
					- m_buildType = Executable;
					- m_libraries = "";
					- m_additionalSources = "";
					- m_standardHeaders = "";
					- m_includePath = "";
					- m_initializationCode = "";
					- m_folder = { IFolder 
						- _id = GUID 12712e77-d8ba-4a63-b426-7f0a36a6744b;
						- _myState = 65536;
						- _name = "Files";
						- m_path = "";
						- Elements = { IRPYRawContainer 
							- size = 0;
						}
						- Files = { IRPYRawContainer 
							- size = 0;
						}
					}
					- m_configActive = { ICodeGenConfigInfoHandle 
						- _m2Class = "ICodeGenConfigInfo";
						- _id = GUID fe512dee-3b01-4d3e-9a1f-e3723282df86;
					}
					- Configs = { IRPYRawContainer 
						- size = 1;
						- value = 
						{ ICodeGenConfigInfo 
							- _id = GUID fe512dee-3b01-4d3e-9a1f-e3723282df86;
							- _myState = 8192;
							- _name = "NotUsedConfiguration";
							- _description = { IDescription 
								- _text = "This Rhapsody model only includes the RXF Product Profile and is used to maintain it. However, Rhapsody requires every model to include at least one package, component and configurations. This is why the \"empty\" model elements \"NotUsedPkg\", \"NotUsedComponent\" and \"NotUsedConfiguration\" are part of the model.";
							}
							- HyperLinks = { IRPYRawContainer 
								- size = 2;
								- value = 
								{ IMHyperLink 
									- _id = GUID 628195f9-bfe9-4cfd-acca-5c9956412b29;
									- _dependsOn = { INObjectHandle 
										- _m2Class = "";
									}
									- _linkDispName = "Edit Makefile";
									- _linkType = "FREE";
									- _linkTarget = "C:\\V5\\Component\\Products\\Beethoven\\Config\\Profiles\\NotUsedComponent\\NotUsedConfiguration\\NotUsedComponent.mak";
									- isConfigurationFileHyperLink = 1;
								}
								{ IMHyperLink 
									- _id = GUID 9bc85548-e9af-421a-9dc9-a48f083f9f87;
									- _dependsOn = { INObjectHandle 
										- _m2Class = "";
									}
									- _linkDispName = "Edit Main File";
									- _linkType = "FREE";
									- _linkTarget = "C:\\V5\\Component\\Products\\Beethoven\\Config\\Profiles\\NotUsedComponent\\NotUsedConfiguration\\MainNotUsedComponent";
									- isConfigurationFileHyperLink = 1;
								}
							}
							- _scopeType = Explicit;
							- _libraries = "";
							- _additionalSources = "";
							- _standardHeaders = "";
							- _includePath = "";
							- _targetMain = "";
							- _instrumentation = None;
							- _timeModel = RealTime;
							- m_generateActors = 1;
							- _statechartImplementation = Flat;
							- _initializationCode = "";
							- _checksList = 0 ;
							- ScopeElements = { IRPYRawContainer 
								- size = 0;
							}
							- InitialInstances = { IRPYRawContainer 
								- size = 0;
							}
							- _root = { IFolder 
								- _id = GUID c0ec7300-c148-4c3e-b638-cb8ffa9e99cc;
								- _name = "NotUsedConfiguration";
								- m_path = "";
								- Elements = { IRPYRawContainer 
									- size = 0;
								}
								- Files = { IRPYRawContainer 
									- size = 0;
								}
							}
							- weakCGTime = 3.10.2008::11:9:31;
							- strongCGTime = 3.10.2008::11:6:29;
							- AnimScopeElements = { IRPYRawContainer 
								- size = 0;
							}
							- m_allInAnimScope = 1;
						}
					}
					- HandlesInMe = { IRPYRawContainer 
						- size = 2;
						- value = 
						{ IHandle 
							- _m2Class = "IProfile";
							- _filename = "Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_Profile.sbs";
							- _subsystem = "";
							- _class = "";
							- _name = "Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_Profile";
							- _id = GUID 63b9fb62-92f4-4462-ad4c-dcdac9796b49;
						}
						{ IHandle 
							- _m2Class = "IProfile";
							- _filename = "WSTProfile.sbs";
							- _subsystem = "";
							- _class = "";
							- _name = "WSTProfile";
							- _id = GUID 839b3570-feed-482e-8776-cdf59c7831ae;
						}
					}
					- VariationPoints = { IRPYRawContainer 
						- size = 0;
					}
					- SelectedVariants = { IRPYRawContainer 
						- size = 0;
					}
					- weakCGTime = 3.10.2008::11:14:37;
					- strongCGTime = 3.10.2008::11:6:54;
				}
			}
			- weakCGTime = 3.10.2008::11:14:46;
			- strongCGTime = 3.10.2008::11:10:13;
			- _defaultComposite = GUID b7ffe0d4-24ba-436b-886e-5a167394b3f5;
			- _eventsBaseID = -1;
			- Classes = { IRPYRawContainer 
				- size = 1;
				- value = 
				{ IClass 
					- _id = GUID b7ffe0d4-24ba-436b-886e-5a167394b3f5;
					- _myState = 40960;
					- _name = "TopLevel";
					- weakCGTime = 1.24.2008::9:10:19;
					- strongCGTime = 1.24.2008::9:10:19;
					- _multiplicity = "";
					- _itsStateChart = { IHandle 
						- _m2Class = "";
					}
					- _classModifier = Unspecified;
				}
			}
			- _configurationRelatedTime = 1.24.2008::9:10:19;
		}
		{ IProfile 
			- fileName = "Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_Profile";
			- _id = GUID 63b9fb62-92f4-4462-ad4c-dcdac9796b49;
		}
		{ IProfile 
			- fileName = "WSTProfile";
			- _id = GUID 839b3570-feed-482e-8776-cdf59c7831ae;
		}
	}
	- Diagrams = { IRPYRawContainer 
		- size = 0;
	}
	- Components = { IRPYRawContainer 
		- size = 0;
	}
}

