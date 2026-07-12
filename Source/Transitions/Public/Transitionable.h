// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Transitionable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTransitionable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRANSITIONS_API ITransitionable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fade")
	void FadeInLevel();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Fade")
	void FadeOutLevel(const TSoftObjectPtr<UWorld>& LevelToLoad);
};
