// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeactivated);
/*
* Button is actor that act like floor buttons in portal(you put stuff on them and they activate)
*/
UCLASS()
class OLDHOUSE_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AActor*>OverlappedActors;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnActivated OnActivated;

	UPROPERTY(BlueprintAssignable)
	FOnActivated OnDeactivated;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UBoxComponent *BoxCollision;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	USceneComponent *RootScene;

	//Instead of calling get overlapping actors all the time
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Info)
	int AmountOfActors = 0;

	/*Button will only send Activated signal if overlapped actor has this class*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Settings)
	TArray<TSubclassOf<AActor>> AcceptableClasses;

	/*Button will only send Activated signal if overlapped actor is in this array(ignores class setting)*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Settings)
	TArray<AActor*> AcceptableActors;

	/*If it needs more than one thing(will be hard to use with physics items)*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Settings)
	int NeededAmount = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= State)
	bool bActivated = false;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnButtonActivated();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void OnButtonDeactivated();

	UFUNCTION()
 void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
 void OnBoxEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
