// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_ProductGhost.h"
#include "JS_ProductManager.h"
#include <Kismet/GameplayStatics.h>
#include <Components/StaticMeshComponent.h>
#include "CharacterBase.h"
#include "JS_InteractionComp.h"
#include "JS_FloorBase.h"
#include "ProductBase.h"

// Sets default values
AJS_ProductGhost::AJS_ProductGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 스태틱 매쉬 컴포넌트
	compGhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	SetRootComponent(compGhostMesh);
	compGhostMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	// 배치 가능 머테리얼(초록색)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempGreenMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/SS_Final/Asset/Product/bPlace_true_Inst.bPlace_true_Inst'"));
	if (tempGreenMat.Succeeded())
	{
		greenMat = tempGreenMat.Object;
	}

	// 배치 불가능 머테리얼(빨간색)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempRedMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/SS_Final/Asset/Product/bPlace_false_Inst.bPlace_false_Inst'"));
	if (tempGreenMat.Succeeded())
	{
		redMat = tempRedMat.Object;
	}
}

// Called when the game starts or when spawned
void AJS_ProductGhost::BeginPlay()
{
	Super::BeginPlay();

	// 월드에서 플레이어 가져오기
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(),ACharacterBase::StaticClass()));


	// 월드에서 프로덕트 매니저 가져오기
 		productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
	// 스태틱매쉬 초기값 세팅
	if (productManager != nullptr)
	{
/*		compGhostMesh->SetStaticMesh(productManager->selectedMesh);*/
	}



}

// Called every frame
void AJS_ProductGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (player->compInteraction->hitActorState == EHitActorState::Floor)
	{
		canPlace = true;
	}
	else
	{
		canPlace = false;
	}
	// 현재 매쉬 변수에 저장
	currGhostMesh = compGhostMesh->GetStaticMesh();

	// 머테리얼 슬롯 개수 가져오기
	matIdx = compGhostMesh->GetNumMaterials();
	// 오버랩에 따라 색 변화
	CanSofaMat(canPlace, matIdx);


}

void AJS_ProductGhost::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Error, TEXT("BeginOverlap = false"))
	canPlace = false;

}
void AJS_ProductGhost::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	UE_LOG(LogTemp, Error, TEXT("EndOverlap = true"))

	canPlace = true;

}


void AJS_ProductGhost::CanSofaMat(bool value, int32 matCount)
{
	if (value)
	{
		for (int32 i = 0; i < matCount; i++)
		{
			compGhostMesh->SetMaterial(i, greenMat);
		}

	}
	else
	{
		for (int32 i = 0; i < matCount; i++)
		{
			compGhostMesh->SetMaterial(i, redMat);
		}
	}
}

void AJS_ProductGhost::SetActive(bool value)
{
	compGhostMesh->SetVisibility(value);
	if (value)
	{
		compGhostMesh->SetCollisionProfileName("ProductPreset");
	}
	else
	{
		compGhostMesh->SetCollisionProfileName("NoCollision");
	}
	
}

void AJS_ProductGhost::RotateGhost()
{
	UE_LOG(LogTemp,Warning,TEXT("RotateGhost"))
	FRotator currRot = GetActorRotation();
	float angle = 89.9f;
	currRot.Yaw += angle;
	UE_LOG(LogTemp,Warning,TEXT("newRot.Yaw : %f"),currRot.Yaw)
	SetActorRotation(FRotator(currRot.Pitch,currRot.Yaw,currRot.Roll));
}
void AJS_ProductGhost::SetInit(int32 value)
{
	compGhostMesh->SetStaticMesh(productManager->productArr[value]->info.mesh);
	
	selectedWidgetIdx = value;
}