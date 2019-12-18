// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IModuleConsoleCommand.h"

#include "CoreMinimal.h"
#include "LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogModuleConsoleCommand, Log, All);

class FModuleConsoleCommandModule;

class FModuleConsoleCommandExecutor : public IConsoleCommandExecutor
{
public:
	FModuleConsoleCommandExecutor(IModuleConsoleCommand* InModuleConsoleCommand);

	static FName StaticName();
	virtual FName GetName() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetDescription() const override;
	virtual FText GetHintText() const override;
	virtual void GetAutoCompleteSuggestions(const TCHAR* Input, TArray<FString>& Out) override;
	virtual void GetExecHistory(TArray<FString>& Out) override;
	virtual bool Exec(const TCHAR* Input) override;
	virtual bool AllowHotKeyClose() const override;
	virtual bool AllowMultiLine() const override;

	virtual FInputChord GetHotKey() const override
	{
		return FInputChord();
	}
private:
	IModuleConsoleCommand* ModuleConsoleCommand;
};

class FModuleConsoleCommand : public IModuleConsoleCommand
{
public:

	FModuleConsoleCommand();

	/** Get this module */
	static FModuleConsoleCommand* Get()
	{
		return static_cast<FModuleConsoleCommand*>(IModuleConsoleCommand::Get());
	}

	//~ IModuleConsoleCommand interface
	virtual bool ExecModuleCommand(const TCHAR* InBlueprintCommand) override;

	//~ IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FModuleConsoleCommandExecutor CmdExec;

};
