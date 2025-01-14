// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeaponBase::CanShoot()
{
	return Ammo > 0;
}

void AWeaponBase::PlayReloadEffects_Implementation()
{
	
}

void AWeaponBase::Reload_Implementation()
{
}

void AWeaponBase::Attack_Implementation(UAnimMontage* AttackAnim)
{
	
}

void AWeaponBase::Fire_Implementation(FVector Location, FRotator Rotation)
{
	Ammo--;
	if(Ammo < 0){Ammo = 0;}
}

