// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AzSpeechData.h"
#include "VoiceCommandHelperBase.h"

#include "AzSpeechCommandHelper.generated.h"

UCLASS()
class VOICECOMMAND_API UAzSpeechCommandHelper : public UVoiceCommandHelperBase
{
	GENERATED_BODY()

public:

	void SetInitialParams(FString APIAccessKey, FString RegionID, FString LanguageID);
	
	virtual void StartRecognizingKeywords(TArray<FString> Keywords) override;
	virtual void StopRecognizingSpeech() override;

protected:

	UFUNCTION()
	void Callback(const FString& TaskResult);

	UPROPERTY()
	TArray<FString> _keywords;

private:

	FAzSpeechData _speechData;
	bool _paramsSet;
};
