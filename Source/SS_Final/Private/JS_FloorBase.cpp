// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_FloorBase.h"
#include "Components/StaticMeshComponent.h"
#include <Materials/MaterialInstance.h>
#include <Components/BoxComponent.h>

// Sets default values
AJS_FloorBase::AJS_FloorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	compFloorMesh->SetCollisionProfileName("BlockAll");

	compFloorMesh->SetRelativeScale3D(FVector(1));

	
	// 머테리얼(기본)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempBasicMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Concrete_Floor_virrebs/MI_Concrete_Floor_virrebs_1K.MI_Concrete_Floor_virrebs_1K'"));
	if (tempBasicMat.Succeeded())
	{
		arrFloorMat.Add(tempBasicMat.Object);
	}

	// 머테리얼(대리석)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempMarbleMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Nero_Marquina_Marble_wlhlabtv/MI_Nero_Marquina_Marble_wlhlabtv_1K.MI_Nero_Marquina_Marble_wlhlabtv_1K'"));
	if (tempMarbleMat.Succeeded())
	{
		arrFloorMat.Add(tempMarbleMat.Object);
	}

	// 머테리얼(나무)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempWoodMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Wooden_Planks_ulyobjsn/MI_Wooden_Planks_ulyobjsn_1K.MI_Wooden_Planks_ulyobjsn_1K'"));
	if (tempWoodMat.Succeeded())
	{
		arrFloorMat.Add(tempWoodMat.Object);
	}

	// 머테리얼(타일)
	ConstructorHelpers::FObjectFinder <UMaterialInstance> tempTileMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Megascans/Surfaces/Floor_Tiles_vlxjaed/MI_Floor_Tiles_vlxjaed_1K.MI_Floor_Tiles_vlxjaed_1K'"));
	if (tempTileMat.Succeeded())
	{
		arrFloorMat.Add(tempTileMat.Object);
	}
}

// Called when the game starts or when spawned
void AJS_FloorBase::BeginPlay()
{
	Super::BeginPlay();

	// 머테리얼 슬롯 개수 구하기
	matIdx = compFloorMesh->GetNumMaterials();

	// 머테리얼 슬롯 개수만큼 머테리얼 초기화
	for (int32 i = 0; i < matIdx; i++)
	{
		compFloorMesh->SetMaterial(i,arrFloorMat[0]);
	}
}

// Called every frame
void AJS_FloorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

///////////////////////////////////// 아래 정림 추가(텔레포트 이동을 위해)
	compFloorMesh->OnComponentBeginOverlap.AddDynamic(this, &AJS_FloorBase::ComponentBeginOverlapMove);

}

void AJS_FloorBase::ChangeFloorMat(int32 idx)
{
	
	for (int32 i = 0; i < matIdx; i++)
	{
		compFloorMesh->SetMaterial(i,arrFloorMat[idx]);
	}

}


///////////////////////////////////// 아래 정림 추가(텔레포트 이동을 위해)
void AJS_FloorBase::ComponentBeginOverlapMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

