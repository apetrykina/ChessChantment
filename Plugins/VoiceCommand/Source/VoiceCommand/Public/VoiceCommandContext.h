// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VoiceCommandContext.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnCommandSuccess);

UCLASS(BlueprintType)
class VOICECOMMAND_API UVoiceCommandContext : public UObject
{
	GENERATED_BODY()

public:
	
	UVoiceCommandContext();

	UFUNCTION(BlueprintCallable)
	bool AddCommand(TArray<FString> Phrases, FOnCommandSuccess OnCommandSuccess);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveCommand(FString CommandName);

	UFUNCTION(BlueprintCallable)
	bool FindAndRunCommand(FString CommandName);

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetCommandNames();
	
private:

	TMap<FString, FOnCommandSuccess> _commands;
};