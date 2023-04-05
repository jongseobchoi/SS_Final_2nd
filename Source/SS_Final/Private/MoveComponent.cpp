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

	//�÷��̾� Ŭ���� ĳ��
	player = Cast<ACharacterBase>(GetOwner());
	
	//���� Ŭ���� ĳ��
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

	if (blsShowLine) //���� ������ ���̸�
	{
		DrawMoveLine(); //�̵� �(�̵��� ��� ȭ�鿡 �׸���) �Լ� ����
	}


}


//[SetupPlayerInputComponent] �����ռ�
void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//[�޼�]
	//�޼� ��ƽ ---> �¿� ȸ��
	PlayerInputComponent->BindAction(leftStick, ETriggerEvent::Triggered, this, &UMoveComponent::LeftStickRotateAxis);
	
	//�޼� Ʈ���� ---> �ڷ���Ʈ �̵�
	if (bIsTeleport)
	{
		PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Started, this, &UMoveComponent::leftTriggerShowLine);
		PlayerInputComponent->BindAction(leftTrigger, ETriggerEvent::Completed, this, &UMoveComponent::leftTriggerHideLine);
	}
	

}


//�޼� Ʈ���� ����, �̵��� ��� ȭ�鿡 �׸���
void UMoveComponent::DrawMoveLine()
{
	//p = p0 + vt - 0.5 * g * t ^ 2

	//����. �޼� �𵨸��� ���� ��ǥ�� ���缭 forward ����� up ������ �ٽ� ����ϴ�. ���� ����� �޼� �𵨸��� ����...
	FVector handForward = FRotationMatrix(player->meshLeftHand->GetComponentRotation()).GetUnitAxis(EAxis::Y); //������ �𵨸��� ���� Y �� �չ����� ���ϰ� �ֱ� ������ ���� Y �� �չ������� ����
	FVector handUP = FRotationMatrix(player->meshLeftHand->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1; //������ �𵨸��� ���� X �� �Ʒ����� ���ϰ� �ֱ� ������ ���� X �� -1 ���ؼ� ���������� ����
	FVector dir = handForward + handUP;

	//�迭 ����. �޼� ��ǥ�� ���ƿ��� �ʵ���...
	lineLocation.Empty();


	for (int32 i = 0; i < lineTimeSegment; i++)
	{
		//�ð� t. �ҿ� �ð�. �귯�� �ð�
		float timeTaken = lineTimeInterval * i;

		//p = p0 + vt
		FVector prediction = player->meshLeftHand->GetComponentLocation() + dir * power * timeTaken;

		//p.Z -= 0.5 * g * t^2
		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		//�迭�� �ִ´�
		lineLocation.Add(prediction);

		//����Ʈ���̽��� �������� üũ�Ѵ�.
		FHitResult hitInfo;

		if (i > 0)
		{
			if (GetWorld()->LineTraceSingleByChannel(hitInfo, lineLocation[i - 1], lineLocation[i], ECC_Visibility))
			{
				//position = Cast<AMoveLocation>(hitInfo.GetActor()); //MoveLocation
				position = Cast<AJS_FloorBase>(hitInfo.GetActor()); //JS_FloorBase ������ �̵� �����ϵ��� ��
				//�ε��� ������ ������ ��ǥ�� �ְ� �ݺ����� ���� �����Ѵ�.
				lineLocation.Add(hitInfo.ImpactPoint);
				break;
			}
		}
	}

	//�տ��� ���� ��ġ ���� ������ ������ �׸��� �׸���.(DrawLine)
	for (int32 i = 0; i < lineLocation.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), lineLocation[i], lineLocation[i + 1], FColor::Green, false, -1, 0, 1); //true �� �� ��� ���� �������� �ʴ´�. -1 �� ������. 2 ����
	}

	//[�ڷ���Ʈ �� ����Ʈ�� ������ ���� ��ġ�� ��ġ�Ѵ�]
// 	if (spawnedVFXTeleportRing == nullptr) //�ڷ���Ʈ ���� ������
// 	{
// 		//�ڷ���Ʈ �� ����Ʈ�� �����Ѵ�
// 		spawnedVFXTeleportRing = currentWorld->SpawnActor<ATeleportLocationRingActor>(VFXTeleportRing, lineLocation[lineLocation.Num() - 1], FRotator::ZeroRotator);
// 	}
// 	else
// 	{	
// 		//�Ⱥ��̰� ó���� ����Ʈ�� �ٽ� ���̰� �Ѵ�
// 		spawnedVFXTeleportRing->compNiagara->SetVisibility(true);
// 		spawnedVFXTeleportRing->SetActorLocation(lineLocation[lineLocation.Num() - 1]);
// 	}
}

//�޼� Ʈ���� ����, ���� �̵�. ��� ��ǥ ����
void UMoveComponent::Teleport()
{
	//����Ų �������� ���� �̵��Ѵ�.(��� ��ǥ ����)
	FVector targetLoc = lineLocation[lineLocation.Num() - 1];
	targetLoc.Z += player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight(); //�÷��̾ ������ �ʰ� Z ������ ���� �ø���
	player->SetActorLocation(targetLoc, false, nullptr, ETeleportType::TeleportPhysics);

	//�ڷ���Ʈ �� ����Ʈ�� ���̸�
// 	if (spawnedVFXTeleportRing != nullptr) 
// 	{
// 		//�ڷ���Ʈ �� ����Ʈ�� �� ���̰� �Ѵ�
// 		spawnedVFXTeleportRing->compNiagara->SetVisibility(false);
// 	}
}

//�޼� Ʈ���� ---> �̵�. ������ ���δ�.
void UMoveComponent::leftTriggerShowLine()
{
	blsShowLine = true;
}

//�޼� Ʈ���� ---> �̵�. ������ �� ���̸鼭 �ڷ���Ʈ �Ѵ�.
void UMoveComponent::leftTriggerHideLine()
{
	blsShowLine = false; //���� �� ���δ�
	
	if (position != nullptr)
	{
		//�ڷ���Ʈ ���̵� �� ����
		TeleportFade();

		//1�� �ڿ� Teleport �� ����
		FTimerHandle WaitHandle;
		float WaitTime = 1;
		currentWorld->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			Teleport();
		}), WaitTime, false);
	}
}

//�ڷ���Ʈ ���̵� ��
void UMoveComponent::TeleportFade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);
}


//�޼� ��ƽ ---> ȸ��
void UMoveComponent::LeftStickRotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//�¿� ȸ��
	player->AddControllerYawInput(axis.X);

	//���� ȸ��
	//player->AddControllerPitchInput(axis.Y * -1.0f);
}