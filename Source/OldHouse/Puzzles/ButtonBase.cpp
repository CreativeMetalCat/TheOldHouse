// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonBase.h"

// Sets default values
AButtonBase::AButtonBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&AButtonBase::OnBoxBeginOverlap);

	OnActorEndOverlap.AddDynamic(this,&AButtonBase::OnBoxEndOverlap);
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonBase::OnButtonActivated_Implementation()
{
	OnActivated.Broadcast();
	bActivated = true;
}

void AButtonBase::OnButtonDeactivated_Implementation()
{
	OnDeactivated.Broadcast();
	bActivated = false;
	if(AmountOfActors < 0)
	{
		AmountOfActors = 0;
	}
}

void AButtonBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsValidLowLevel())
	{	
		if(OverlappedActors.Find(OtherActor) == -1)
		{
			if(AcceptableClasses.Num() > 0)
			{
				for(int i=0;i<AcceptableClasses.Num();i++)
				{
					if(OtherActor->GetClass()->IsChildOf(AcceptableClasses[i]) || OtherActor->GetClass() == AcceptableClasses[i])
					{
						AmountOfActors++;
						OverlappedActors.Add(OtherActor);
						
						if(!bActivated && AmountOfActors>= NeededAmount){OnButtonActivated();}
						return;
					}
				}		
			}
	
			if(AcceptableActors.Num() > 0)
			{
				for(int i=0;i<AcceptableActors.Num();i++)
				{
					if(AcceptableActors[i] == OtherActor)
					{
						AmountOfActors++;
						OverlappedActors.Add(OtherActor);
						
						if(!bActivated && AmountOfActors>= NeededAmount){OnButtonActivated();}
						return;
					}
				}
			}
		}
	}
}

void AButtonBase::OnBoxEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	if(OtherActor->IsValidLowLevel())
	{
		if(OverlappedActors.Find(OtherActor) != -1)
		{
			if(AcceptableClasses.Num() > 0)
			{
				for(int i=0;i<AcceptableClasses.Num();i++)
				{
					if(OtherActor->GetClass()->IsChildOf(AcceptableClasses[i]) || OtherActor->GetClass() == AcceptableClasses[i])
					{
						AmountOfActors--;
						OverlappedActors.Remove(OtherActor);						
						if(bActivated && AmountOfActors < NeededAmount){OnButtonDeactivated();}					
						return;
					}
				}		
			}
	
			if(AcceptableActors.Num() > 0)
			{
				for(int i=0;i<AcceptableActors.Num();i++)
				{
					if(AcceptableActors[i] == OtherActor)
					{
						AmountOfActors--;
						OverlappedActors.Remove(OtherActor);						
						if(bActivated && AmountOfActors < NeededAmount){OnButtonDeactivated();}					
						return;
					}
				}
			}
		}
	}
}

