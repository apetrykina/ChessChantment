#include "SpeechRecognitionActor.h"
#include "SpeechRecognition.h"

#define SPEECHRECOGNITIONPLUGIN ISpeechRecognition::Get()

bool ASpeechRecognitionActor::Init(ESpeechRecognitionLanguage language, FString modelDirPath)
{
	// terminate any existing thread
	if (listenerThread != NULL) {
		if (!modelDirPath.IsEmpty())
		{
			listenerThread->SetModelDirPath(modelDirPath);
		}
		listenerThread->SetLanguage(language);
		return true;
	}

	// start listener thread
	listenerThread = new FSpeechRecognitionWorker();
	TArray<FRecognitionPhrase> dictionaryList;
	if (!modelDirPath.IsEmpty())
	{
		listenerThread->SetModelDirPath(modelDirPath);
	}
	listenerThread->SetLanguage(language);
	bool threadSuccess = listenerThread->StartThread(this);
	return threadSuccess;
}

int32 ASpeechRecognitionActor::GetCurrentVolume()
{
	if (listenerThread != NULL) {
		int16 returnVal = listenerThread->GetCurrentVolume();
		return returnVal;
	}
	return false;
}

bool ASpeechRecognitionActor::SetConfigParam(FString param, ESpeechRecognitionParamType type, FString value)
{
	if (listenerThread != NULL) {
		bool returnVal = listenerThread->SetConfigParam(param, type, value);
		return returnVal;
	}
	return false;
}

bool ASpeechRecognitionActor::Shutdown()
{
	if (listenerThread != NULL) {
		listenerThread->ShutDown();
		listenerThread = NULL;
		return true;
	}
	else{
		return false;
	}
}

/**************************
// Change recognition methods
**************************/
bool ASpeechRecognitionActor::EnableKeywordMode(TArray<FRecognitionPhrase> wordList)
{
	if (listenerThread != NULL) {
		return listenerThread->EnableKeywordMode(wordList);
	}
	return false;
}

bool ASpeechRecognitionActor::EnableGrammarMode(FString grammarName)
{
	if (listenerThread != NULL) {
		return listenerThread->EnableGrammarMode(grammarName);
	}
	return false;
}

bool ASpeechRecognitionActor::EnableLanguageModel(FString languageModel)
{
	if (listenerThread != NULL) {
		return listenerThread->EnableLanguageModel(languageModel);
	}
	return false;
}

/**************************
// Callback methods
**************************/
void ASpeechRecognitionActor::WordsSpoken_trigger(FWordsSpokenSignature delegate_method, FRecognisedPhrases text)
{
	delegate_method.Broadcast(text);
}

void ASpeechRecognitionActor::WordsSpoken_method(FRecognisedPhrases text)
{
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady
		(
			FSimpleDelegateGraphTask::FDelegate::CreateStatic(&WordsSpoken_trigger, OnWordsSpoken, text)
			, TStatId()
			, nullptr
			, ENamedThreads::GameThread
			);
}

void ASpeechRecognitionActor::UnknownPhrase_trigger(FUnknownPhraseSignature delegate_method)
{
	delegate_method.Broadcast();
}

void ASpeechRecognitionActor::UnknownPhrase_method()
{
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady
		(
			FSimpleDelegateGraphTask::FDelegate::CreateStatic(&UnknownPhrase_trigger, OnUnknownPhrase)
			, TStatId()
			, nullptr
			, ENamedThreads::GameThread
			);
}

void ASpeechRecognitionActor::StartedSpeaking_trigger(FStartedSpeakingSignature delegate_method)
{
	delegate_method.Broadcast();
}

void ASpeechRecognitionActor::StartedSpeaking_method()
{
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady
		(
			FSimpleDelegateGraphTask::FDelegate::CreateStatic(&StartedSpeaking_trigger, OnStartedSpeaking)
			, TStatId()
			, nullptr
			, ENamedThreads::GameThread
			);
}

void ASpeechRecognitionActor::StoppedSpeaking_trigger(FStoppedSpeakingSignature delegate_method)
{
	delegate_method.Broadcast();
}

void ASpeechRecognitionActor::StoppedSpeaking_method()
{
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady
		(
			FSimpleDelegateGraphTask::FDelegate::CreateStatic(&StoppedSpeaking_trigger, OnStoppedSpeaking)
			, TStatId()
			, nullptr
			, ENamedThreads::GameThread
			);
}
