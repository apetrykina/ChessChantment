// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechRecognitionHelper.h"
#include "Interfaces/IPluginManager.h"


void USpeechRecognitionHelper::StartRecognizingKeywords(TArray<FString> Keywords)
{
	if (!_speechRecognitionActor)
	{
		_speechRecognitionActor = GetWorld()->SpawnActor<ASpeechRecognitionActor>();
		
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
	}
	_speechRecognitionActor->EnableKeywordMode(GetKeywordList(Keywords));	
}

void USpeechRecognitionHelper::StopRecognizingSpeech()
{
	if (_speechRecognitionActor)
	{
		_speechRecognitionActor->Shutdown();
	}
}

void USpeechRecognitionHelper::OnWordSpoken(FRecognisedPhrases phrases)
{
	FString command = "";
	for (int i = 0; i < phrases.phrases.Num() - 1; i++)
	{
		command += phrases.phrases[i]+ "";
	}
	command += phrases.phrases.Last();
	_lastCommand = command;
	
	UE_LOG(LogTemp, Warning, TEXT("Recognized command: %s"), command.GetCharArray().GetData());
	
	if (OnSpeechRecognized.IsBound())
	{
		OnSpeechRecognized.Execute(command);
	}
}

FString USpeechRecognitionHelper::GetLastCommand()
{
	return  _lastCommand;
}

TArray<FRecognitionPhrase> USpeechRecognitionHelper::GetKeywordList(TArray<FString> Keywords)
{
	TArray<FRecognitionPhrase> keywordList;
	for (auto keyword : Keywords)
	{
		keywordList.Add(FRecognitionPhrase(keyword, EPhraseRecognitionTolerance::VE_2));
	}
	return keywordList;
}





