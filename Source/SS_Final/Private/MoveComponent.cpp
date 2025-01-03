// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "CharacterBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/CapsuleComponent.h"
#include <Components/TextRenderComponent.h>
#include "MoveLocation.h"
#include <Kismet/GameplayStatics.h>
#include "TeleportLocationRingActor.h"
#include "NiagaraComponent.h"
#include <Engine/Engine.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "JS_FloorBase.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 클레스 캐싱
	player = Cast<ACharacterBase>(GetOwner());
	
	//월드 클래스 캐싱
	currentWorld = GetWorld();


	
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

// 	FString name = UGameplayStatics::GetCurrentLevelName(currentWorld);
// 	if (name.Contains("Main") || name.Contains("Select"))
// 	{
// 		isTeleport = false;
// 	}
// 	else
// 	{
// 		isTeleport = true;
// 	}

	if (blsShowLine) //만약 라인이 보이면
	{
		DrawMoveLine(); //이동 곡선(이동할 곡선을 화면에 그린다) 함수 실행
	}


}


//[SetupPlayerInputComponent] 가상합수
void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//[왼손]
	//왼손 스틱 ---> 좌우 회전
	PlayerInputComponent->BindAction(leftStick, ETriggerEvent::Triggered, this, &UMoveComponent::LeftStickRotateAxis);
	
	//왼손 트리거 ---> 텔레포트 이동
	if (bIsTeleport)
	{
		PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Started, this, &UMoveComponent::leftTriggerShowLine);
		PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Completed, this, &UMoveComponent::leftTriggerHideLine);
	}
	

}


//왼손 트리거 관련, 이동할 곡선을 화면에 그린다
void UMoveComponent::DrawMoveLine()
{
	//p = p0 + vt - 0.5 * g * t ^ 2

	//방향. 왼손 모델링의 로컬 좌표에 맞춰서 forward 방향과 up 방향을 다시 계산하다. 현재 사용한 왼손 모델링에 맞춰...
	FVector handForward = FRotationMatrix(player->meshLeftHand->GetComponentRotation()).GetUnitAxis(EAxis::Y); //★현재 모델링한 손의 Y 가 앞방향을 향하고 있기 때문에 손의 Y 를 앞방향으로 만듬
	FVector handUP = FRotationMatrix(player->meshLeftHand->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1; //★현재 모델링한 손의 X 가 아래향을 향하고 있기 때문에 손의 X 에 -1 곱해서 위방향으로 만듬
	FVector dir = handForward + handUP;

	//배열 비운다. 왼손 좌표로 돌아오지 않도록...
	lineLocation.Empty();


	for (int32 i = 0; i < lineTimeSegment; i++)
	{
		//시간 t. 소요 시간. 흘러간 시간
		float timeTaken = lineTimeInterval * i;

		//p = p0 + vt
		FVector prediction = player->meshLeftHand->GetComponentLocation() + dir * power * timeTaken;

		//p.Z -= 0.5 * g * t^2
		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		//배열에 넣는다
		lineLocation.Add(prediction);

		//라인트레이스를 구간마다 체크한다.
		FHitResult hitInfo;

		if (i > 0)
		{
			if (GetWorld()->LineTraceSingleByChannel(hitInfo, lineLocation[i - 1], lineLocation[i], ECC_Visibility))
			{
				//position = Cast<AMoveLocation>(hitInfo.GetActor()); //MoveLocation
				position = Cast<AJS_FloorBase>(hitInfo.GetActor()); //JS_FloorBase 에서만 이동 가능하도록 함
				//부딪힌 지점을 마지막 좌표로 넣고 반복문을 강제 종료한다.
				lineLocation.Add(hitInfo.ImpactPoint);
				break;
			}
		}
	}

	//앞에서 구한 위치 마다 선으로 연결한 그림을 그린다.(DrawLine)
	for (int32 i = 0; i < lineLocation.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), lineLocation[i], lineLocation[i + 1], FColor::Green, false, -1, 0, 1); //true 로 할 경우 선이 지워지지 않는다. -1 한 프레임. 2 굵기
	}

	//[텔레포트 링 이펙트를 마지막 라인 위치에 배치한다]
// 	if (spawnedVFXTeleportRing == nullptr) //텔레포트 링이 없으면
// 	{
// 		//텔레포트 링 이펙트를 생성한다
// 		spawnedVFXTeleportRing = currentWorld->SpawnActor<ATeleportLocationRingActor>(VFXTeleportRing, lineLocation[lineLocation.Num() - 1], FRotator::ZeroRotator);
// 	}
// 	else
// 	{	
// 		//안보이게 처리된 이펙트를 다시 보이게 한다
// 		spawnedVFXTeleportRing->compNiagara->SetVisibility(true);
// 		spawnedVFXTeleportRing->SetActorLocation(lineLocation[lineLocation.Num() - 1]);
// 	}
}

//왼손 트리거 관련, 순간 이동. 즉시 좌표 변경
void UMoveComponent::Teleport()
{
	//가리킨 지점으로 순간 이동한다.(즉시 좌표 변경)
	FVector targetLoc = lineLocation[lineLocation.Num() - 1];
	targetLoc.Z += player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); //플레이어가 묻히지 않게 Z 축으로 절반 올린다
	player->SetActorLocation(targetLoc, false, nullptr, ETeleportType::TeleportPhysics);

	//텔레포트 링 이펙트가 보이면
// 	if (spawnedVFXTeleportRing != nullptr) 
// 	{
// 		//텔레포트 링 이펙트를 안 보이게 한다
// 		spawnedVFXTeleportRing->compNiagara->SetVisibility(false);
// 	}
}

//왼손 트리거 ---> 이동. 라인이 보인다.
void UMoveComponent::leftTriggerShowLine()
{
	blsShowLine = true;
}

//왼손 트리거 ---> 이동. 라인이 안 보이면서 텔레포트 한다.
void UMoveComponent::leftTriggerHideLine()
{
	blsShowLine = false; //라인 안 보인다
	
	if (position != nullptr)
	{
		//텔레포트 페이드 인 실행
		TeleportFade();

		//1초 뒤에 Teleport 를 실행
		FTimerHandle WaitHandle;
		float WaitTime = 1;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Teleport();
		}), WaitTime, false);
	}
}

//텔레포트 페이드 인
void UMoveComponent::TeleportFade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);
}


//왼손 스틱 ---> 회전
void UMoveComponent::LeftStickRotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//좌우 회전
	player->AddControllerYawInput(axis.X);

	//상하 회전
	//player->AddControllerPitchInput(axis.Y * -1.0f);
}