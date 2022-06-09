// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpeechRecognition.h"
#include "SpeechRecognitionActor.h"
#include "VoiceCommandHelperBase.h"
#include "SpeechRecognitionHelper.generated.h"

UCLASS()
class VOICECOMMAND_API USpeechRecognitionHelper : public UVoiceCommandHelperBase
{
	GENERATED_BODY()

public:

	~USpeechRecognitionHelper();
	
	virtual void StartRecognizingKeywords(TArray<FString> Keywords) override;
	virtual void StopRecognizingSpeech() override;

protected:

	UFUNCTION()
	void OnWordSpoken(FRecognisedPhrases phrases);
	
	TArray<FRecognitionPhrase> GetKeywordList(TArray<FString> Keywords);

private:

	UPROPERTY()
	ASpeechRecognitionActor * _speechRecognitionActor;
};
