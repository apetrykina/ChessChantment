// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechRecognitionHelper.h"
#include "Interfaces/IPluginManager.h"

USpeechRecognitionHelper::~USpeechRecognitionHelper()
{
	if (_speechRecognitionActor)
	{
		_speechRecognitionActor->Shutdown();
	}
}

void USpeechRecognitionHelper::StartRecognizingKeywords(TArray<FString> Keywords)
{
	_speechRecognitionActor = GetWorld()->SpawnActor<ASpeechRecognitionActor>();
	if (!_speechRecognitionActor)
	{
		return;;
	}
		
	FString modelDirPath = IPluginManager::Get().FindPlugin(TEXT("VoiceCommand"))->GetContentDir() + "/";
	if (_speechRecognitionActor && _speechRecognitionActor->Init(ESpeechRecognitionLanguage::VE_English, modelDirPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpeechRecogTestActor:Init success"));
			
		_speechRecognitionActor->OnWordsSpoken.AddDynamic(this, &USpeechRecognitionHelper::OnWordSpoken);
			
		_speechRecognitionActor->SetConfigParam("-vad_prespeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		_speechRecognitionActor->SetConfigParam("-vad_postspeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		_speechRecognitionActor->SetConfigParam("-agc", ESpeechRecognitionParamType::VE_STRING, "noise");
		_speechRecognitionActor->SetConfigParam("-beam", ESpeechRecognitionParamType::VE_FLOAT, "1e-60");			
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpeechRecogTestActor:Init failure"));
		return;
	}
	_speechRecognitionActor->EnableKeywordMode(GetKeywordList(Keywords));	
}

void USpeechRecognitionHelper::StopRecognizingSpeech()
{
	if (_speechRecognitionActor)
	{
		_speechRecognitionActor->Shutdown();
		_speechRecognitionActor->Destroy();
	}
}

void USpeechRecognitionHelper::OnWordSpoken(FRecognisedPhrases phrases)
{
	if (phrases.phrases.Num() == 0)
	{
		return;
	}
	FString command = phrases.phrases[0];
	_lastCommand = command;
	
	UE_LOG(LogTemp, Warning, TEXT("Recognized command: %s"), command.GetCharArray().GetData());
	
	if (OnSpeechRecognized.IsBound())
	{
		OnSpeechRecognized.Execute(command);
	}
}

TArray<FRecognitionPhrase> USpeechRecognitionHelper::GetKeywordList(TArray<FString> Keywords)
{
	TArray<FRecognitionPhrase> keywordList;
	for (auto keyword : Keywords)
	{
		keywordList.Add(FRecognitionPhrase(keyword, EPhraseRecognitionTolerance::VE_5));
	}
	return keywordList;
}





