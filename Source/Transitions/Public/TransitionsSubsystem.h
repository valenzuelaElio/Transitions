// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "TransitionsSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTransitionData
{
    GENERATED_BODY() // Required as the first line of the struct body.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition")
    FString DoorsRelationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition")
    bool OverInitialLoad;

    FTransitionData()
    {
        DoorsRelationID = "";
        OverInitialLoad = false;
    }
};

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

    UFUNCTION(BlueprintCallable)
    void ClearTemporalDoorData();

    UFUNCTION(BlueprintCallable)
    void SetDoorsRelationID(FString doorsRelationID);

    UFUNCTION(BlueprintCallable)
    void SetTransitionData(FTransitionData transitionData);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FTransitionData TransitionData;

private:
    UPROPERTY()
    UUserWidget* ActiveWidgetInstance;
	
};
