// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceCommandHelperBase.h"

void UVoiceCommandHelperBase::StartRecognizingSpeech()
{
	UE_LOG(LogTemp, Warning, TEXT("Speech recorgnition started."));
}

void UVoiceCommandHelperBase::StartRecognizingKeywords(TArray<FString> Keywords)
{
	UE_LOG(LogTemp, Warning, TEXT("Keyword recorgnition started."));	
}

void UVoiceCommandHelperBase::StopRecognizingSpeech()
{
	UE_LOG(LogTemp, Warning, TEXT("Recorgnition stopped."));	
}


