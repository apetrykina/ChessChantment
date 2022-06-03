// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoiceCommandHelperBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSpeechRecognized, FString, SpeechResult);

UCLASS()
class VOICECOMMAND_API UVoiceCommandHelperBase : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual void StartRecognizingSpeech();
	
	UFUNCTION()
	virtual void StartRecognizingKeywords(TArray<FString> Keywords);
	
	UFUNCTION()
	virtual void StopRecognizingSpeech();

	UFUNCTION()
	virtual FString GetLastCommand();

	FOnSpeechRecognized OnSpeechRecognized;
};
