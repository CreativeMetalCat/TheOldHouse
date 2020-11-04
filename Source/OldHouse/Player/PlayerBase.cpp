// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

#include "OldHouse/Interaction.h"

bool APlayerBase::SelectWeapon_Implementation(int32 Id)
{
    if(Id!=CurrentWeaponId)
    {
        if(Weapons.IsValidIndex(Id))
        {
            PreviousWeaponId = CurrentWeaponId;
            CurrentWeaponId = Id;
            return true;    
        }
    }
    return false;
}

void APlayerBase::Reload_Implementation()
{
    //because reloading is tied to animation no c++ code will be here
}

APlayerBase::APlayerBase()
{
    InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollision"));
    InteractionCollision->SetupAttachment(RootComponent);
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("ReloadAction", IE_Pressed, this, &APlayerBase::Reload);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerBase::InteractAction);
}

void APlayerBase::InteractAction()
{
    TArray<AActor*> actors;
    InteractionCollision->GetOverlappingActors(actors);
    if (actors.Num() > 0)
    {
        for (int i = 0; i < actors.Num(); i++)
        {
            if (actors[i]->Implements<UInteraction>() || (Cast<IInteraction>(actors[i]) != nullptr))
            {
                IInteraction::Execute_Interact(actors[i], this);
            }
        }
    }
}

EWeaponType APlayerBase::GetCurrentWeaponType(bool& hasCurrentWeapon)
{
    hasCurrentWeapon = false;
    if(Weapons.IsValidIndex(CurrentWeaponId))
    {
        hasCurrentWeapon = true;
        return Weapons[CurrentWeaponId]->Type;
    }
    return EWeaponType::EWT_Melee;
}

AWeaponBase* APlayerBase::GetCurrentWeapon(bool& hasCurrentWeapon)
{
    hasCurrentWeapon = false;
    if(Weapons.IsValidIndex(CurrentWeaponId))
    {
        hasCurrentWeapon = true;
        return Weapons[CurrentWeaponId];
    }
    return nullptr;
}
