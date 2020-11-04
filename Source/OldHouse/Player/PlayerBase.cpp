// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

bool APlayerBase::SelectWeapon_Implementation(int32 Id)
{
    if(Weapons.IsValidIndex(Id))
    {
        PreviousWeaponId = CurrentWeaponId;
        CurrentWeaponId = Id;
        return true;    
    }
    return false;
}
