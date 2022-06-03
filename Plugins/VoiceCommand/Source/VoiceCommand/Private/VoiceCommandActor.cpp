// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceCommandActor.h"

#include "SpeechRecognitionHelper.h"


AVoiceCommandActor::AVoiceCommandActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoiceCommandActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Setup Helper based on SpeechRecognition Plugin
	_voiceCommandHelper = NewObject<USpeechRecognitionHelper>();
	_voiceCommandHelper->Rename(nullptr, this);
	
	if (_voiceCommandHelper)
	{
		_voiceCommandHelper->OnSpeechRecognized.BindDynamic(this, &AVoiceCommandActor::OnSpeechRecognized);
	}
}

void AVoiceCommandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVoiceCommandActor::InitiateCommandRecognition()
{
	if (_voiceCommandHelper)
	{
		_voiceCommandHelper->StartRecognizingKeywords(GetAllCommandNames());
	}
}

void AVoiceCommandActor::StopCommandRecognition()
{
	if (_voiceCommandHelper)
	{
		_voiceCommandHelper->StopRecognizingSpeech();
	}
}

void AVoiceCommandActor::OnSpeechRecognized(FString Command)
{
	if (Command.IsEmpty())
	{
		return;
	}
	for (auto context : _voiceCommandContexts)
	{
		if (context.Key->FindAndRunCommand(Command)) break;
	}
}

void AVoiceCommandActor::AddVoiceCommandContext(UVoiceCommandContext* VoiceCommandContext, int32 Priority)
{
	if (!VoiceCommandContext)
	{
		return;
	}
	_voiceCommandContexts.Add(VoiceCommandContext, Priority);
	_voiceCommandContexts.ValueSort([](int32 A, int32 B){ return A > B; });
}

void AVoiceCommandActor::RemoveVoiceCommandContext(UVoiceCommandContext* VoiceCommandContext)
{
	if (!VoiceCommandContext)
	{
		return;
	}
	_voiceCommandContexts.Remove(VoiceCommandContext);
	_voiceCommandContexts.ValueSort([](int32 A, int32 B){ return A > B; });
}

TArray<FString> AVoiceCommandActor::GetAllCommandNames()
{
	TArray<FString> names;
	for (auto context : _voiceCommandContexts)
	{
		names.Append(context.Key->GetCommandNames());
	}
	return names;
}

FString AVoiceCommandActor::GetLastCommand()
{
	return _voiceCommandHelper->GetLastCommand();
}