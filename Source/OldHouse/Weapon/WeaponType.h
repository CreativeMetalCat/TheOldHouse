// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "WeaponType.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class EWeaponType:uint8
{
 EWT_Melee UMETA(DisplayName = "Melee"),
 EWT_MeleeBig UMETA(DisplayName = "MeleeBig"),
 EWT_Pistol UMETA(DisplayName = "Pistol"),
 EWT_Rifle UMETA(DisplayName = "Rifle"),
 EWT_Shotgun UMETA(DisplayName = "Shotgun")
};
