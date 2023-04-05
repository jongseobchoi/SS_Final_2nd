// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_WidgetActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "CharacterBase.h"
#include "JS_InteractionComp.h"
#include <Kismet/GameplayStatics.h>
#include "JS_WallWidget.h"
#include "JS_FloorWidget.h"
#include "JS_ProductWidget.h"

// Sets default values
AJS_WidgetActor::AJS_WidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	compWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET COMP"));
	ConstructorHelpers::FClassFinder<UJS_ProductWidget> tempProductWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/Widget/JS_BP_ProductWidget.JS_BP_ProductWidget_C'"));
	if (tempProductWidget.Succeeded())
	{
		productWidgetFactroy = tempProductWidget.Class;
	}
	ConstructorHelpers::FClassFinder<UJS_FloorWidget> tempFloorWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/Widget/JS_BP_FloorWidget.JS_BP_FloorWidget_C'"));
	if (tempFloorWidget.Succeeded())
	{
		floorWidgetFactroy = tempFloorWidget.Class;
	}
	ConstructorHelpers::FClassFinder<UJS_WallWidget> tempWallWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/Widget/JS_BP_WallWidget.JS_BP_WallWidget_C'"));
	if (tempFloorWidget.Succeeded())
	{
		wallWidgetFactroy = tempWallWidget.Class;
	}
	compWidget->SetWidgetClass(floorWidgetFactroy);
	compWidget->SetRelativeRotation(FRotator(0.f,180.f,0.f));
	compWidget->SetDrawSize(FVector2D(2500.f,2500.f));
	compWidget->SetRelativeScale3D(FVector(0.1f));
	compWidget->SetCollisionProfileName("UI");
	compWidget->SetCastShadow(false);
	SetRootComponent(compWidget);
}

// Called when the game starts or when spawned
void AJS_WidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� �����ͼ� ĳ��Ʈ�ؼ� �־��ش�
	
	// ���� Ŭ���� �ѹ��� �ҷ�����
}

// Called every frame
void AJS_WidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// ���� ��ġ�� ��������
	FVector currLoc = GetActorLocation();

	// ���� ���� ��ġ�� ���̰� 30 ���ϸ�
	if (currLoc.Z <= 30.f)
	{
		SetActorLocation(FVector(currLoc.X,currLoc.Y,30.f));
	}
	
	
}
void AJS_WidgetActor::SetActive(bool value)
{
	// ���� ������ ���� ����
	SetWidgetType(actorState);
	// ���� ���� ���̰�
	compWidget->SetVisibility(value);
	if (value)
	{
		
		compWidget->SetCollisionProfileName("UI");
		UE_LOG(LogTemp, Warning, TEXT("UI Collision"))
	}
	else
	{
		compWidget->SetCollisionProfileName("NoCollision");
		UE_LOG(LogTemp, Warning, TEXT("NO Collision"))
	}

}

void AJS_WidgetActor::SetWidgetType(EHitActorState value)
{
	switch (player->compInteraction->hitActorState)
	{
	case EHitActorState::Floor:
	{
		compWidget->SetWidgetClass(floorWidgetFactroy);
	}
	break;
	case EHitActorState::Product:
	{
		compWidget->SetWidgetClass(productWidgetFactroy);
	}
	break;
 	case EHitActorState::Wall:
 	{
 		compWidget->SetWidgetClass(wallWidgetFactroy);
 	}
 	break;
 	}
}
