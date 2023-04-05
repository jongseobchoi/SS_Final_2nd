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
	// ����ƽ �Ž� ������Ʈ
	compGhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	SetRootComponent(compGhostMesh);
	compGhostMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	// ��ġ ���� ���׸���(�ʷϻ�)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempGreenMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/SS_Final/Asset/Product/bPlace_true_Inst.bPlace_true_Inst'"));
	if (tempGreenMat.Succeeded())
	{
		greenMat = tempGreenMat.Object;
	}

	// ��ġ �Ұ��� ���׸���(������)
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

	// ���忡�� �÷��̾� ��������
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(),ACharacterBase::StaticClass()));


	// ���忡�� ���δ�Ʈ �Ŵ��� ��������
 		productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
	// ����ƽ�Ž� �ʱⰪ ����
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
	// ���� �Ž� ������ ����
	currGhostMesh = compGhostMesh->GetStaticMesh();

	// ���׸��� ���� ���� ��������
	matIdx = compGhostMesh->GetNumMaterials();
	// �������� ���� �� ��ȭ
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