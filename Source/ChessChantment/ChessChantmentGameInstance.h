// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChessChantmentGameInstance.generated.h"

UCLASS()
class CHESSCHANTMENT_API UChessChantmentGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	bool IsInEditor();
};
