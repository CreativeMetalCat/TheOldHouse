// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OldHouse/CharacterBase.h"
#include "OldHouse/Weapon/WeaponBase.h"


#include "PlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class OLDHOUSE_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	TArray<AWeaponBase*>Weapons;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	int32 CurrentWeaponId = -1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	int32 PreviousWeaponId = -1;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category= Weapons)
	bool SelectWeapon(int32 Id);
};
