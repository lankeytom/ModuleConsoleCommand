// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ModuleConsoleCommand.h"

#include "EngineGlobals.h"
#include "Editor.h"

#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "ModuleConsoleCommand"

DEFINE_LOG_CATEGORY(LogModuleConsoleCommand);

/*
* Module Executor Class
*/

FModuleConsoleCommandExecutor::FModuleConsoleCommandExecutor(IModuleConsoleCommand* InModuleConsoleCommand)
	: ModuleConsoleCommand(InModuleConsoleCommand)
{
}

FName FModuleConsoleCommandExecutor::StaticName()
{
	static const FName CmdExecName = TEXT("ModuleCommand");
	return CmdExecName;
}

FName FModuleConsoleCommandExecutor::GetName() const
{
	return StaticName();
}

FText FModuleConsoleCommandExecutor::GetDisplayName() const
{
	return LOCTEXT("ModuleCommandExecutorDisplayName", "Module Console Command");
}

FText FModuleConsoleCommandExecutor::GetDescription() const
{
	return LOCTEXT("ModuleCommandExecutorDescription", "Execute Module Command");
}

FText FModuleConsoleCommandExecutor::GetHintText() const
{
	return LOCTEXT("ModuleCommandExecutorDisplayNameHintText", "Module Command to Execute");
}

void FModuleConsoleCommandExecutor::GetAutoCompleteSuggestions(const TCHAR* Input, TArray<FString>& Out)
{
}

void FModuleConsoleCommandExecutor::GetExecHistory(TArray<FString>& Out)
{
	IConsoleManager::Get().GetConsoleHistory(TEXT("ModuleCommand"), Out);
}

bool FModuleConsoleCommandExecutor::Exec(const TCHAR* Input)
{
	IConsoleManager::Get().AddConsoleHistoryEntry(TEXT("ModuleCommand"), Input);

	ModuleConsoleCommand->ExecModuleCommand(Input);

	return true;
}

bool FModuleConsoleCommandExecutor::AllowHotKeyClose() const
{
	return false;
}

bool FModuleConsoleCommandExecutor::AllowMultiLine() const
{
	return true;
}

/*
* Module Command Class
*/

FModuleConsoleCommand::FModuleConsoleCommand()
	:
	CmdExec(this)
{
}

bool FModuleConsoleCommand::ExecModuleCommand(const TCHAR* InModuleCommand)
{
	FString Command = InModuleCommand;
	UE_LOG(LogModuleConsoleCommand, Log, TEXT("%s"), *Command); 
	//Forward your commands here
	//Python plugin is a good place for reference
	return true;
}

void FModuleConsoleCommand::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IModularFeatures::Get().RegisterModularFeature(IConsoleCommandExecutor::ModularFeatureName(), &CmdExec);
}

void FModuleConsoleCommand::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IModularFeatures::Get().UnregisterModularFeature(IConsoleCommandExecutor::ModularFeatureName(), &CmdExec);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FModuleConsoleCommand, ModuleConsoleCommand)


