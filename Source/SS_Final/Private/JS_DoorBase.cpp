// ©Copyright 2021 XID


#include "JS_DoorBase.h"
#include <Components/BoxComponent.h>
#include <Components/SceneComponent.h>
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include "CharacterBase.h"
#include <Kismet/GameplayStatics.h>
#include "Math/Vector.h"
// Sets default values
AJS_DoorBase::AJS_DoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(compScene);
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	compBox->SetupAttachment(compScene);
	compBox->SetRelativeLocation(FVector(0.46f, 40.f, 100.5f));
	compBox->SetBoxExtent(FVector(32));
	compBox->SetRelativeRotation(FRotator(0, -90, 0));
	compBox->SetRelativeScale3D(FVector(1.3f, 2.7f, 3.1f));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/APARTS/DVIZ_R2HOUSE/DVIZ_R2HOUSE/Geometries/Structure/SM_SimpleDoor_01.SM_SimpleDoor_01'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	compMesh->SetupAttachment(compScene);
	compMesh->SetRelativeScale3D(FVector(1, 1.125f, 1));
	
	


}

// Called when the game starts or when spawned
void AJS_DoorBase::BeginPlay()
{
	Super::BeginPlay();
	initRot = compMesh->GetRelativeRotation();
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass()));

}

// Called every frame
void AJS_DoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AJS_DoorBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor == player)
	{
		player->ChangeState(EPlayerState::OnDoor);
		canDoorOpen = true;
	}
	

}
void AJS_DoorBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == player)
	{
		player->ChangeState(EPlayerState::Idle);
		canDoorOpen = false;
		OpenDoor();
	}
	

}

void AJS_DoorBase::OpenDoor()
{
	if (canDoorOpen == true)
	{
		FRotator openDoorDir;
		FVector door = compMesh->GetForwardVector();
		FVector playerDir = player->GetActorLocation() - door;
		playerDir.Normalize();
		float dotValue = FVector::DotProduct(door, playerDir);
		float openDir = FMath::Acos(dotValue);

		UE_LOG(LogTemp, Warning, TEXT("내적의 결과값 : %f"), dotValue)
		UE_LOG(LogTemp, Warning, TEXT("Acos 적용한 값 : %f"), openDir)

			if (openDir >= 0)
			{
				openDoorDir = FRotator(0, -90.f, 0);
			}
			else
			{
				openDoorDir = FRotator(0, 90.f, 0);
			}
		compMesh->SetRelativeRotation(openDoorDir);
		compMesh->SetCollisionProfileName("NoCollision");
		canDoorOpen = false;
	}
	else
	{
		compMesh->SetRelativeRotation(FRotator(initRot));
		compMesh->SetCollisionProfileName("BlockAllDynamic");
		canDoorOpen = true;
	}
}
