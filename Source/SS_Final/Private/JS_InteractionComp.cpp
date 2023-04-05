// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_InteractionComp.h"
#include "CharacterBase.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Camera/CameraComponent.h>
#include <Materials/MaterialInstance.h>
#include <Kismet/KismetMathLibrary.h>
#include "JS_ProductGhost.h"
#include "JS_ProductManager.h"
#include <Kismet/GameplayStatics.h>
#include "ProductBase.h"
#include <MotionControllerComponent.h>
#include "JS_FloorBase.h"
#include "JS_WallBase.h"

// Sets default values for this component's properties
UJS_InteractionComp::UJS_InteractionComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UJS_InteractionComp::BeginPlay()
{
	Super::BeginPlay();
	
	// 캐릭터 플레이어 캐스팅
	
	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
	// ...
	
	player = Cast<ACharacterBase>(GetOwner());
	// 라인트레이스 매개변수 세팅

	


}

// Called every frame
void UJS_InteractionComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UJS_InteractionComp::InteractionLineTrace()
{
/*	UE_LOG(LogTemp, Error, TEXT("Line"))*/

	
	FHitResult hitInfo;
	FVector startLoc = player->compRightCon->GetComponentLocation();
	FVector endLoc = player->compRightCon->GetForwardVector() * 5000.f;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	// 라인트레이스 발사


	bool bhit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, params);
	if (bhit)
	{
		// 라인트레이스 시각화
		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Blue, false, 1.f, 1, 1.f);
		// 맞은 액터
		hitActor = hitInfo.GetActor();

		if (hitActor != nullptr)
		{
			// 액터가 어떤 클래스의 인스턴스인지 확인
			if (hitActor->IsA(AProductBase::StaticClass()))
			{
				// hitActor가 AProductBase 클래스의 인스턴스인 경우 실행할 코드
				hitActorState = EHitActorState::Product;
			}
			else if (hitActor->IsA(AJS_FloorBase::StaticClass()))
			{
				// hitActor가 AJS_FloorBase 클래스의 인스턴스인 경우 실행할 코드
				hitActorState = EHitActorState::Floor;
			}
			else if (hitActor->IsA(AJS_WallBase::StaticClass()))
			{
				// hitActor가 AJS_FloorBase 클래스의 인스턴스인 경우 실행할 코드
				hitActorState = EHitActorState::Wall;
			}
			actorName = hitInfo.GetActor()->GetName();
			actorLoc = hitInfo.Location;
			hitClass = hitActor->GetClass();

 			GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, hitClass->GetName(), true, FVector2D(3));
		}

	}
}

