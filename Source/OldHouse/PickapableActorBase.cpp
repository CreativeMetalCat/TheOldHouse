// Fill out your copyright notice in the Description page of Project Settings.


#include "PickapableActorBase.h"

// Sets default values
APickapableActorBase::APickapableActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickapableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickapableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickapableActorBase::OnPickedUp_Implementation()
{
}

void APickapableActorBase::OnDropped_Implementation()
{
}

