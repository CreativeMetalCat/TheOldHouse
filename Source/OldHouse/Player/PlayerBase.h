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

	/*This weapons will be given to player on begin play*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	TArray<TSubclassOf<AWeaponBase>> WeaponClasses;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	int32 CurrentWeaponId = -1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Weapons)
	int32 PreviousWeaponId = -1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Health)
	float Health = 100.f;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category= Weapons)
	bool SelectWeapon(int32 Id);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category= Weapons)
	void Reload();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	virtual EWeaponType GetCurrentWeaponType(bool&hasCurrentWeapon);

	UFUNCTION(BlueprintPure)
    virtual AWeaponBase* GetCurrentWeapon(bool&hasCurrentWeapon);
};
