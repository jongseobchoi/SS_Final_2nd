// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_CartKillZone.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_CartProduct.h"

// Sets default values
ARIM_CartKillZone::ARIM_CartKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	compBox->SetupAttachment(RootComponent);
	//compBox->BoxExtent();
	compBox->SetCollisionProfileName(TEXT("OverlapAll"));

}

// Called when the game starts or when spawned
void ARIM_CartKillZone::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARIM_CartKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARIM_CartKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	cartProduct = Cast<ARIM_CartProduct>(OtherActor);

	//킬존에 닿은 것이 제품일 때
	if (cartProduct != nullptr)
	{
		//킬존에 제품이 닿으면 파괴된다
		cartProduct->Destroy();
	}
}