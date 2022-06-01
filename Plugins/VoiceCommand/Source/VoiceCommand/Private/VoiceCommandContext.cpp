// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceCommandContext.h"

UVoiceCommandContext::UVoiceCommandContext() { }

bool UVoiceCommandContext::AddCommand(TArray<FString> Phrases, FOnCommandSuccess OnCommandSuccess)
{
	if (!OnCommandSuccess.IsBound() || Phrases.Num() == 0)
	{
		return false;
	}
	
	for (auto phrase : Phrases)
	{		
		if (_commands.Contains(phrase))
		{
			_commands[phrase] = OnCommandSuccess;
		}
		else
		{
			_commands.Add(phrase, OnCommandSuccess);
		}
	}	
	return true;
}

bool UVoiceCommandContext::RemoveCommand(FString CommandName)
{
	if (_commands.Contains(CommandName))
	{
		_commands.Remove(CommandName);
		return true;
	}
	return false;
}

bool UVoiceCommandContext::FindAndRunCommand(FString CommandName)
{
	if (_commands.Contains(CommandName) && _commands[CommandName].IsBound())
	{
		_commands[CommandName].Execute();
		return true;
	}
	return false;
}

TArray<FString> UVoiceCommandContext::GetCommandNames()
{
	TArray<FString> commandNames;
	_commands.GetKeys(commandNames);
	return commandNames;
}