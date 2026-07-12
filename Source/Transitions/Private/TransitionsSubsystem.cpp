// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionsSubsystem.h"
#include "Engine/GameInstance.h"
#include "Transitionable.h"
#include "Kismet/GameplayStatics.h"

void UTransitionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTransitionsSubsystem::OnFinishTransitionToLevel);
}

void UTransitionsSubsystem::Deinitialize()
{
    Super::Deinitialize();
    FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);

}

void UTransitionsSubsystem::TransitionToLevel(TSubclassOf<UUserWidget> WidgetClass, TSoftObjectPtr<UWorld> LevelToLoad)
{
    if (!WidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShowPersistentWidget: WidgetClass is null!"));
        return;
    }

    // Get the GameInstance owning this subsystem
    UGameInstance* GameInstance = GetGameInstance();
    if (!GameInstance) return;

    // Fetch a valid world context via the GameInstance
    UWorld* World = GameInstance->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShowPersistentWidget: World is not ready yet!"));
        return;
    }

    // Safely fetch the first local player controller
    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (!PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShowPersistentWidget: PlayerController not found!"));
        return;
    }

    // Create the widget instance safely using the Player Controller as the owner
    if(!ActiveWidgetInstance)
        ActiveWidgetInstance = CreateWidget<UUserWidget>(PC, WidgetClass);

    if(ActiveWidgetInstance)
        GameInstance->GetGameViewportClient()->AddViewportWidgetContent(ActiveWidgetInstance->TakeWidget());

    if (ActiveWidgetInstance && ActiveWidgetInstance->GetClass()->ImplementsInterface(UTransitionable::StaticClass()))
        ITransitionable::Execute_FadeOutLevel(ActiveWidgetInstance, LevelToLoad);

    //if (!LevelToLoad.IsNull())
        //UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelToLoad);


}

void UTransitionsSubsystem::AddWidgetToTransitionToLevel(UUserWidget* Widget, TSoftObjectPtr<UWorld> LevelToLoad)
{
    if (!Widget)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShowPersistentWidget: WidgetClass is null!"));
        return;
    }

    // Get the GameInstance owning this subsystem
    UGameInstance* GameInstance = GetGameInstance();
    if (!GameInstance) return;

    // Fetch a valid world context via the GameInstance
    UWorld* World = GameInstance->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShowPersistentWidget: World is not ready yet!"));
        return;
    }

    ActiveWidgetInstance = Widget;
    if (ActiveWidgetInstance)
        GameInstance->GetGameViewportClient()->AddViewportWidgetContent(ActiveWidgetInstance->TakeWidget());

    if (ActiveWidgetInstance && ActiveWidgetInstance->GetClass()->ImplementsInterface(UTransitionable::StaticClass()))
        ITransitionable::Execute_FadeOutLevel(ActiveWidgetInstance, LevelToLoad);
}

void UTransitionsSubsystem::OnFinishTransitionToLevel(UWorld* LoadedWorld)
{
    // Get the GameInstance owning this subsystem
    UGameInstance* GameInstance = GetGameInstance();
    if (!GameInstance) return;

    if (ActiveWidgetInstance && ActiveWidgetInstance->GetClass()->ImplementsInterface(UTransitionable::StaticClass()))
        ITransitionable::Execute_FadeInLevel(ActiveWidgetInstance);
    //GameInstance->GetGameViewportClient()->RemoveViewportWidgetContent(ActiveWidgetInstance->TakeWidget());
    
}

void UTransitionsSubsystem::ClearTemporalDoorData() {

	TransitionData.DoorsRelationID.Empty();
}

void UTransitionsSubsystem::SetDoorsRelationID(FString doorsRelationID) {
	
	TransitionData.DoorsRelationID = doorsRelationID;
}

void UTransitionsSubsystem::SetTransitionData(FTransitionData transitionData) {

	TransitionData = transitionData;
}