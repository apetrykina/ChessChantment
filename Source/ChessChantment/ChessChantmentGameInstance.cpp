// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessChantmentGameInstance.h"

bool UChessChantmentGameInstance::IsInEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}
