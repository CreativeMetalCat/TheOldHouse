// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

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

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("ReloadAction", IE_Pressed, this, &APlayerBase::Reload);
}
