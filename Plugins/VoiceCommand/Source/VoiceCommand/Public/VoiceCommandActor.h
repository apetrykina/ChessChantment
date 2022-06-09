// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoiceCommandContext.h"
#include "VoiceCommandHelperBase.h"
#include "GameFramework/Actor.h"
#include "VoiceCommandActor.generated.h"

UCLASS(BlueprintType)
class VOICECOMMAND_API AVoiceCommandActor : public AActor
{
	GENERATED_BODY()

public:

	AVoiceCommandActor();
	
	UFUNCTION(BlueprintCallable)
	void InitiateCommandRecognition();

	UFUNCTION(BlueprintCallable)
	void StopCommandRecognition();

	UFUNCTION(BlueprintCallable)
	void AzureSetInitialParams(FString APIAccessKey, FString RegionID, FString LanguageID);

	UFUNCTION(BlueprintCallable)
	void AddVoiceCommandContext(UVoiceCommandContext* VoiceCommandContext, int32 Priority);

	UFUNCTION(BlueprintCallable)
	void RemoveVoiceCommandContext(UVoiceCommandContext* VoiceCommandContext);

	UFUNCTION(BlueprintCallable)
	FString GetLastCommand();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSpeechRecognized(FString Command);

	TArray<FString> GetAllCommandNames();

	UPROPERTY()
	UVoiceCommandHelperBase* _voiceCommandHelper;

private:

	UPROPERTY()
	TMap<UVoiceCommandContext*, int32> _voiceCommandContexts;	
};
