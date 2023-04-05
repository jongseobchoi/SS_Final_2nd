// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_WallBase.h"
#include "Components/StaticMeshComponent.h"
#include <Materials/MaterialInstance.h>

// Sets default values
AJS_WallBase::AJS_WallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	compWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	compWallMesh->SetCollisionProfileName("BlockAll");
	compWallMesh->SetRelativeScale3D(FVector(1));

	// 머테리얼(기본)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempBasicMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Concrete_Floor_virrebs/MI_Concrete_Floor_virrebs_1K.MI_Concrete_Floor_virrebs_1K'"));
	if (tempBasicMat.Succeeded())
	{
		arrWallMat.Add(tempBasicMat.Object);
	}

	// 머테리얼(대리석)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempMarbleMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Nero_Marquina_Marble_wlhlabtv/MI_Nero_Marquina_Marble_wlhlabtv_1K.MI_Nero_Marquina_Marble_wlhlabtv_1K'"));
	if (tempMarbleMat.Succeeded())
	{
		arrWallMat.Add(tempMarbleMat.Object);
	}

	// 머테리얼(나무)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempWoodMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Wooden_Planks_ulyobjsn/MI_Wooden_Planks_ulyobjsn_1K.MI_Wooden_Planks_ulyobjsn_1K'"));
	if (tempWoodMat.Succeeded())
	{
		arrWallMat.Add(tempWoodMat.Object);
	}

	// 머테리얼(타일)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempTileMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Floor_Tiles_vlxjaed/MI_Floor_Tiles_vlxjaed_1K.MI_Floor_Tiles_vlxjaed_1K'"));
	if (tempTileMat.Succeeded())
	{
		arrWallMat.Add(tempTileMat.Object);
	}
}

// Called when the game starts or when spawned
void AJS_WallBase::BeginPlay()
{
	Super::BeginPlay();
	// 머테리얼 슬롯 개수 구하기
	matIdx = compWallMesh->GetNumMaterials();

	// 머테리얼 슬롯 개수만큼 머테리얼 초기화
	for (int32 i = 0; i < matIdx; i++)
	{
		compWallMesh->SetMaterial(i, arrWallMat[0]);
	}
}

// Called every frame
void AJS_WallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJS_WallBase::ChangeWallMat(int32 idx)
{

	for (int32 i = 0; i < matIdx; i++)
	{
		compWallMesh->SetMaterial(i, arrWallMat[idx]);
	}

}
