// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	this->Owner = this->GetOwner();
	this->ActorThatOpens = this->GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor(){
	
	FRotator NewRotatoion = FRotator(0.f, this->OpenAngle, 0.f);
	this->Owner->SetActorRotation(NewRotatoion);
} 

void UOpenDoor::CloseDoor()
{
	FRotator NewRotatoion = FRotator(0.f, 0.f, 0.f);
	this->Owner->SetActorRotation(NewRotatoion);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->PressurePlate->IsOverlappingActor(this->ActorThatOpens))
	{
		this->OpenDoor();
		this->LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - this->LastDoorOpenTime > this->CloseDoorDelay)
	{
		this->CloseDoor();
	}
	
}

