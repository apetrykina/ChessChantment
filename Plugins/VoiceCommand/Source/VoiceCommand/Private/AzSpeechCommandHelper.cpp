// Fill out your copyright notice in the Description page of Project Settings.

#include "AzSpeechCommandHelper.h"
#include "AzSpeech/VoiceToTextAsync.h"

void UAzSpeechCommandHelper::SetInitialParams(FString APIAccessKey, FString RegionID, FString LanguageID)
{
	_speechData.APIAccessKey = APIAccessKey;
	_speechData.RegionID = RegionID;
	_speechData.LanguageID = LanguageID;
	_paramsSet = true;
}

void UAzSpeechCommandHelper::StartRecognizingKeywords(TArray<FString> Keywords)
{
	if (!_paramsSet) return;
	
	_keywords = Keywords;

	UVoiceToTextAsync* speechTask = UVoiceToTextAsync::VoiceToTextAsync(this, _speechData);

	speechTask->TaskCompleted.AddDynamic(this, &UAzSpeechCommandHelper::Callback);
	speechTask->Activate();
}

void UAzSpeechCommandHelper::StopRecognizingSpeech()
{
	_keywords.Empty();
}

void UAzSpeechCommandHelper::Callback(const FString& TaskResult)
{
	if (_keywords.Num() == 0)
	{
		return;
	}
	
	FString result = TaskResult.ToLower();
	result.RemoveFromEnd(".");

	FString firstCloseResult;
	for (int i = 0; i < _keywords.Num(); i++)
	{
		int32 comparison = _keywords[i].Compare(result);
		if (comparison == 0 || comparison > 0 && firstCloseResult.IsEmpty())
		{
			firstCloseResult = _keywords[i];
			if (comparison == 0) break;
		}
	}
	
	if (!firstCloseResult.IsEmpty())
	{
		_lastCommand = firstCloseResult;
	
		UE_LOG(LogTemp, Warning, TEXT("Recognized command: %s"), _lastCommand.GetCharArray().GetData());
		
		if (OnSpeechRecognized.IsBound())
		{
			OnSpeechRecognized.Execute(_lastCommand);
		}
	}
	else if (OnSpeechFailed.IsBound())
	{
		OnSpeechFailed.Execute();
	}
}


