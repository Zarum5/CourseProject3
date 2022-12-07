// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //attach actor to podium and tell the mover
    AActor* Actor = GetAcceptableActor();
    if (Actor!=nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        Mover->SetShouldMove(true);
    } else {
        Mover->SetShouldMove(false);
    }
}

//Find actor with matching tag that isn't grabbed
AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for (AActor* Actor : Actors)
    {
        if (Actor->ActorHasTag(DetectTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }
    return nullptr;
}

//update mover var
void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}
