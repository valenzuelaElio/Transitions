// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "TransitionsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TRANSITIONS_API UTransitionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable)
    void TransitionToLevel(TSubclassOf<UUserWidget> WidgetClass, TSoftObjectPtr<UWorld> LevelToLoad);

    UFUNCTION(BlueprintCallable)
    void AddWidgetToTransitionToLevel(UUserWidget* Widget, TSoftObjectPtr<UWorld> LevelToLoad);

    UFUNCTION()
    void OnFinishTransitionToLevel(UWorld* LoadedWorld);

private:
    UPROPERTY()
    UUserWidget* ActiveWidgetInstance;
	
};
