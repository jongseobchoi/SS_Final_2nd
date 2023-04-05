// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_ConveyorBelt.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ARIM_ConveyorBelt::ARIM_ConveyorBelt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	compMesh->SetupAttachment(RootComponent);

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	compBox->SetupAttachment(compMesh);
	

}

// Called when the game starts or when spawned
void ARIM_ConveyorBelt::BeginPlay()
{
	Super::BeginPlay();
	
	//블루프린트에 Arrow 를 만들었기 때문에 C++ 로 가져오는 코드
	compArrow = Cast<UArrowComponent>( FindComponentByClass(UArrowComponent::StaticClass()));

}

// Called every frame
void ARIM_ConveyorBelt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// 	//CompBox
// 	TSet<AActor*> overlappingActor;
// 	compBox->GetOverlappingActors(overlappingActor);
// 
// 	//Speed
// 	float createMoveSpeed = currentMoveSpeed * DeltaTime;
// 
// 	//Arrow
// 	FRotator fRotator = compArrow->K2_GetComponentRotation();
// 	FVector vFoward = UKismetMathLibrary::GetForwardVector(fRotator);
// 	FVector deltaLocation = createMoveSpeed * vFoward;
// 
// 	//For Each Loop
// 	for (AActor* var : overlappingActor)	
// 	{	
// 		var->AddActorWorldOffset(deltaLocation);
// 	}

	Activity();

}

void ARIM_ConveyorBelt::Activity()
{
	if (isStop != false)
	{
		//CompBox
		TSet<AActor*> overlappingActor;
		compBox->GetOverlappingActors(overlappingActor);

		//Speed
		float createMoveSpeed = currentMoveSpeed * GetWorld()->DeltaTimeSeconds;

		//Arrow
		FRotator fRotator = compArrow->K2_GetComponentRotation();
		FVector vFoward = UKismetMathLibrary::GetForwardVector(fRotator);
		FVector deltaLocation = createMoveSpeed * vFoward;

		//For Each Loop
		for (AActor* var : overlappingActor)
		{
			var->AddActorWorldOffset(deltaLocation);
		}

		isStop = false;
	}
	else
	{
		//CompBox
		TSet<AActor*> overlappingActor;
		compBox->GetOverlappingActors(overlappingActor);

		//Speed
		float createMoveSpeed = 0 * GetWorld()->DeltaTimeSeconds;

		//Arrow
		FRotator fRotator = compArrow->K2_GetComponentRotation();
		FVector vFoward = UKismetMathLibrary::GetForwardVector(fRotator);
		FVector deltaLocation = createMoveSpeed * vFoward;

		//For Each Loop
		for (AActor* var : overlappingActor)
		{
			var->AddActorWorldOffset(deltaLocation);
		}

		isStop = true;
	}

	
}