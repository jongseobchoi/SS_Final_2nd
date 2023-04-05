// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLocation.h"
#include <Components/BoxComponent.h>

// Sets default values
AMoveLocation::AMoveLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	compCollision->SetupAttachment(RootComponent);
	//compCollision->SetBoxExtent(FVector(50.0f)); //������ �ʿ� �� ����

}

// Called when the game starts or when spawned
void AMoveLocation::BeginPlay()
{
	Super::BeginPlay();

	compCollision->OnComponentBeginOverlap.AddDynamic(this, &AMoveLocation::ComponentBeginOverlapMove);


}

// Called every frame
void AMoveLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMoveLocation::ComponentBeginOverlapMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}