// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

class IModuleConsoleCommand : public IModuleInterface
{
public:

	static IModuleConsoleCommand* Get()
	{
		static const FName ModuleName = "ModuleEditorConsoleCommand";
		return FModuleManager::GetModulePtr<IModuleConsoleCommand>(ModuleName);
	}

	/*
	* Execute the given command.
	* @return true if the command ran successfully, false if there were errors (the output log will show the errors).
	*/
	virtual bool ExecModuleCommand(const TCHAR* InCommand) = 0;

};
