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

int APlayerBase::GetAmmoForWeaponType(EWeaponType type)
{
    TArray<EWeaponType>keys;
    Ammo.GetKeys(keys);
    TArray<int>count;
    Ammo.GenerateValueArray(count);
    
    if(keys.Find(type) != -1)
    {
        return count[keys.Find(type)];
    }
    return -1;
}

void APlayerBase::RemoveAmmo(EWeaponType type, int amount)
{
    if(GetAmmoForWeaponType(type) > 0)
    {
        TArray<EWeaponType> keys;
        Ammo.GetKeys(keys);
        TArray<int> count;
        Ammo.GenerateValueArray(count);

        const int Res = count[keys.Find(type)] - amount;

        Ammo.Add(type, Res > 0 ? Res : 0);
    }
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
