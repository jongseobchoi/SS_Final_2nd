// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/TextRenderComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "MoveComponent.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "WidgetPointerComponent.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "Widget_Righthand.h"
#include "WidgetActor_Righthand.h"
#include "JS_InteractionComp.h"
#include "ProductBase.h"
#include "JS_ProductManager.h"
#include <Kismet/GameplayStatics.h>
#include <JS_ProductGhost.h>
#include "JS_FloorBathroom.h"
#include "JS_FloorBase.h"
#include "JS_WidgetActor.h"
#include <Kismet/KismetMathLibrary.h>
#include <Engine/DirectionalLight.h>
#include "CSVLoader.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "JS_WallBase.h"
#include "JS_CameraTopView.h"
#include <UnrealClient.h>
#include "JS_DoorBase.h"
#include "LightBase.h"



// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 


	righthandWidgetActor = Cast<AWidgetActor_Righthand>(UGameplayStatics::GetActorOfClass(GetWorld(), AWidgetActor_Righthand::StaticClass()));
	
	//[Scene]
	//��(ī�޶�, ��Ʈ�ѷ� �θ� ������ ����)
	compScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	compScene->SetupAttachment(RootComponent);
	compScene->SetRelativeLocation(FVector(0, 0, 0)); //���ʿ� �� ���� ����

	//[ī�޶�]
	//ī�޶� 
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	compCamera->SetupAttachment(compScene);
	compCamera->SetRelativeLocation(FVector(-60, 0, 0)); //���ʿ� �� ���� ����
	//���� ������ ī�޶� ����
	compScreenShotWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenShot Widget"));
	compScreenShotWidget->SetupAttachment(compCamera);
	ConstructorHelpers::FClassFinder<UUserWidget> tempScreenShotWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_ScreenShot.BP_WG_ScreenShot_C'"));
	if (tempScreenShotWidget.Succeeded())
	{
		compScreenShotWidget->SetWidgetClass(tempScreenShotWidget.Class);
	}
	compScreenShotWidget->SetRelativeLocation(FVector(120, 0,0));
 	compScreenShotWidget->SetRelativeRotation(FRotator(0, 180, 0));
 	compScreenShotWidget->SetRelativeScale3D(FVector(0.1f));
	compScreenShotWidget->SetVisibility(false);
	compScreenShotWidget->SetCollisionProfileName("UI");

	//[�޼�]
	//��Ʈ�ѷ�
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	compLeftCon->SetupAttachment(compScene);
	//�޽�
	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	meshLeftHand->SetupAttachment(compLeftCon);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'")); //���⺻ ���� ��. �ʿ� �� ���� ����
	if (tempLeftHand.Succeeded())
	{
		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
	}
	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	meshLeftHand->SetRelativeRotation(FRotator(-25, 180, 90)); //���ʿ� �� ���� ����
	meshLeftHand->SetRelativeLocation(FVector(0, -15, 0)); //���ʿ� �� ���� ����
	//�α�(Ȯ�ο�)
// 	logLeft = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LeftLogText"));
// 	logLeft->SetupAttachment(compLeftCon);
// 	logLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //�ؽ�Ʈ 180 ����
// 	logLeft->SetRelativeLocation(FVector(0.0f, 20.f, 0.0f)); //��ġ ����
// 	logLeft->SetRelativeScale3D(FVector(0.25)); //������ ����
// 	logLeft->SetTextRenderColor(FColor::Yellow);
// 	logLeft->SetHorizontalAlignment(EHTA_Center);
// 	logLeft->SetVerticalAlignment(EVRTA_TextCenter);

	//�޼� ������ �޼� ��Ʈ�ѷ��� ����-----------------------------------------------------------------------------> �޼� �޴� ����
	compLefthandWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lefthand Widget"));
	compLefthandWidget->SetupAttachment(compLeftCon);
	ConstructorHelpers::FClassFinder<UUserWidget> tempLefthandWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_Righthand.BP_WG_Righthand_C'"));
	if (tempLefthandWidget.Succeeded())
	{
		compLefthandWidget->SetWidgetClass(tempLefthandWidget.Class);
	}
	compLefthandWidget->SetRelativeLocation(FVector(15, 0, -30));
	compLefthandWidget->SetRelativeRotation(FRotator(110, 180, 0));
	compLefthandWidget->SetRelativeScale3D(FVector(0.04f));
	//compLefthandWidget->SetVisibility(false);
	compLefthandWidget->SetCollisionProfileName("UI");

	//���� ���� ������ ī�޶� ����--------------------------------------------------------------------------------> �޼� ��ǰ ����
	compAssetMainWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Asset Main Widget"));
	compAssetMainWidget->SetupAttachment(compLeftCon);
	ConstructorHelpers::FClassFinder<UUserWidget> tempAssetMainWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_AssetMain.BP_WG_AssetMain_C'"));
	if (tempAssetMainWidget.Succeeded())
	{
		compAssetMainWidget->SetWidgetClass(tempAssetMainWidget.Class);
	}
	compAssetMainWidget->SetRelativeLocation(FVector(40, 15, -75));
	compAssetMainWidget->SetRelativeRotation(FRotator(100, 360, 180));
	compAssetMainWidget->SetRelativeScale3D(FVector(0.08f));
	compAssetMainWidget->SetGeometryMode(EWidgetGeometryMode::Cylinder);
	compAssetMainWidget->SetCylinderArcAngle(120.0f);
	compAssetMainWidget->SetVisibility(false);
	compAssetMainWidget->SetCollisionProfileName("UI");
	
	//���� ������ ī�޶� ����-------------------------------------------------------------------------------------> �޼� ���� ����
	compSettingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Setting Widget"));
	compSettingWidget->SetupAttachment(compLeftCon);
	ConstructorHelpers::FClassFinder<UUserWidget> tempSettingWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_Setting.BP_WG_Setting_C'"));
	if (tempSettingWidget.Succeeded())
	{
		compSettingWidget->SetWidgetClass(tempSettingWidget.Class);
	}
	compSettingWidget->SetRelativeLocation(FVector(40, 15, -75));
	compSettingWidget->SetRelativeRotation(FRotator(100, 360, 180));
	compSettingWidget->SetRelativeScale3D(FVector(0.08f));
	compSettingWidget->SetGeometryMode(EWidgetGeometryMode::Cylinder);
	compSettingWidget->SetCylinderArcAngle(120.0f);
	compSettingWidget->SetVisibility(false);
	compSettingWidget->SetCollisionProfileName("UI");
	
	//�ֹ� ������ �޼� ��Ʈ�ѷ��� ����-------------------------------------------------------------------------------> �޼� ��ٱ��� �� �ݾ�/�ֹ��ϱ� ��ư ����
	compOrderWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Order Widget"));
	compOrderWidget->SetupAttachment(compLeftCon);
	ConstructorHelpers::FClassFinder<UUserWidget> tempOrderWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_Order.BP_WG_Order_C'"));
	if (tempOrderWidget.Succeeded())
	{
		compOrderWidget->SetWidgetClass(tempOrderWidget.Class);
	}
	compOrderWidget->SetRelativeLocation(FVector(4, 3, -22));
	compOrderWidget->SetRelativeRotation(FRotator(110, 180, 0));
	compOrderWidget->SetRelativeScale3D(FVector(0.05f));
 	compOrderWidget->SetVisibility(false);
 	compOrderWidget->SetCollisionProfileName("UI");
	//��� �ҽ� ����
	compLeftCon->MotionSource = "Left";

	//[������]
	//��Ʈ�ѷ�
	compRightCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	compRightCon->SetupAttachment(compScene);
	//�޽�
	meshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	meshRightHand->SetupAttachment(compRightCon);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRihgtHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'")); //���⺻ ���� ��. �ʿ� �� ���� ����
	if (tempRihgtHand.Succeeded())
	{
		meshRightHand->SetSkeletalMesh(tempRihgtHand.Object);
	}
	meshRightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //�޽� ���ݸ���
	meshRightHand->SetRelativeRotation(FRotator(25, 0, 90)); //���ʿ� �� ���� ����
	meshRightHand->SetRelativeLocation(FVector(0, 15, 0));
	//�α�(Ȯ�ο�)
// 	logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
// 	logRight->SetupAttachment(compRightCon);
// 	logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //�ؽ�Ʈ 180 ����
// 	logRight->SetRelativeLocation(FVector(0.0f, -20.f, 0.0f)); //��ġ ����
// 	logRight->SetRelativeScale3D(FVector(0.25)); //������ ����
// 	logRight->SetTextRenderColor(FColor::Yellow);
// 	logRight->SetHorizontalAlignment(EHTA_Center);
// 	logRight->SetVerticalAlignment(EVRTA_TextCenter);
	//������
	compWidgetPointer_right = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	compWidgetPointer_right->SetupAttachment(compRightCon);
	compWidgetPointer_right->SetRelativeLocation(FVector(-1, 12, -1));
	compWidgetPointer_right->SetRelativeRotation(FRotator(-90, 0, 0));
	compWidgetPointer_right->bShowDebug = true; //����׶���
	//��� �ҽ� ����
	compRightCon->MotionSource = "Right";


	//axis ���� �̿��ؼ� ĳ����(��Ʈ�ѷ�)�� ȸ��
	bUseControllerRotationPitch = true;
	//�÷��̾� ����...?
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	

	//[�÷��̾ ���� ������Ʈ �߰�]
	//�̵�, �ڷ���Ʈ ����
	compMove = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	//����(������) ����
	compWidget = CreateDefaultSubobject<UWidgetPointerComponent>(TEXT("WidgetComponent"));


	// ĳ���� ���� �����ڿ��� ã��
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempCharMap(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/SS_Final/CharacterInput/IMC_CharacterMapping.IMC_CharacterMapping'"));
	if (tempCharMap.Succeeded())
	{
		CharacterMapping = tempCharMap.Object;
	}

	// ����� ���� �����ڿ��� ã��
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempDebugMap(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/SS_Final/CharacterInput/IMC_CharacterDebug.IMC_CharacterDebug'"));
	if (tempDebugMap.Succeeded())
	{
		DebugMapping = tempDebugMap.Object;
	}

	// ����Ʈ���̽� ��� ����
	compInteraction = CreateDefaultSubobject<UJS_InteractionComp>(TEXT("COMP INTERACTION"));

	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	//1. �÷��̾� ��Ʈ�ѷ��� �����´�.
	playerCon = GetWorld()->GetFirstPlayerController();

	//2. �÷��̾� ��Ʈ�ѷ����� EnhancedInputLocalPlayerSubsystem �� �����´�.
	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	//3. ������ Subsystem �� IMC �� ����Ѵ�.(�켱���� 0��) , selectInput ������ ���� context ����
	subsys->AddMappingContext(CharacterMapping, selectInput);
	subsys->AddMappingContext(DebugMapping, 1-selectInput);
	
	
	


	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
	// ��Ʈ �̸� ����
	
	if (productManager != nullptr)
	{
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		productGhost = GetWorld()->SpawnActor<AJS_ProductGhost>(AJS_ProductGhost::StaticClass(), productManager->GetActorTransform(), spawnParams);
		productGhost->SetActive(false);
		// ž�� ī�޶� ����
		topViewCam = GetWorld()->SpawnActor<AJS_CameraTopView>(AJS_CameraTopView::StaticClass(), FVector(0), FRotator(0));
		// ���� ������Ʈ �迭 �ʱ�ȭ �Լ�
	}

	SetWidgetArr();
	VisibleOrderWidget(); //�޼� �ֹ��ݾ� ���� ����
	//compOrderWidget->SetTotalPriceWidgetInCart();
	VisibleHandMenuWidget();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	switch (currState)
	{
		case EPlayerState::Idle:
		{
			IdleState();
		}
			break;
		case EPlayerState::OnDoor:
		{
		}
			break;
		case EPlayerState::SelectedProduct:
		{
			SelectedProductState();
		}
			break;
		case EPlayerState::OpenWidget:
		{
		}
		case EPlayerState::OpenProductWidget:
		{
		}
			break;
		case EPlayerState::CameraMode:
		{
		}
			break;
	}


}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//[Enhanced Action Events]
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		//�̵� �Լ� ����
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);
		//���� ������ ����
		compWidget->SetupPlayerInputComponent(EnhancedInputComponent);

		//[������]
		//������ ��ư A ---> ������ ���� ����, �ݱ� ---> �޼����� �ű�(����NO) ---> �������� ���� ����
		EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ACharacterBase::StartedA);

		//[�޼�]
		//�޼� ��ư X ---> ������ ���� ����, �ݱ�
		FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		//���� 01_Title ���� �̸�
		if (levelName.Contains("01_Title"))
		{
			return;
		}
		else
		{
/*			EnhancedInputComponent->BindAction(LeftX, ETriggerEvent::Started, this, &ACharacterBase::SetLeftHandWidget);*/
		}



		// ����׿� Ű ���ε�
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Started, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(cameraAction, ETriggerEvent::Triggered, this, &ACharacterBase::CameraRotate);
		EnhancedInputComponent->BindAction(mouseXY, ETriggerEvent::Triggered, this, &ACharacterBase::HandRotate);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Triggered, this, &ACharacterBase::TriggerA);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Started, this, &ACharacterBase::StartedA);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Completed, this, &ACharacterBase::ReleaseA);
		EnhancedInputComponent->BindAction(pressB, ETriggerEvent::Started, this, &ACharacterBase::StartedB);


		// ����׿� Ű ���ε� 2
		EnhancedInputComponent->BindAction(press1, ETriggerEvent::Started, this, &ACharacterBase::Started1);
		EnhancedInputComponent->BindAction(press2, ETriggerEvent::Started, this, &ACharacterBase::Started2);
		EnhancedInputComponent->BindAction(press3, ETriggerEvent::Started, this, &ACharacterBase::Started3);
		EnhancedInputComponent->BindAction(press4, ETriggerEvent::Started, this, &ACharacterBase::Started4);
		EnhancedInputComponent->BindAction(press5, ETriggerEvent::Started, this, &ACharacterBase::Started5);
	}


}


void ACharacterBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AJS_DoorBase::StaticClass()))
	{
		currDoor = Cast<AJS_DoorBase>(OtherActor);
	}
}

// ����׿� ĳ���� �����̴� �Լ�(WASD)
void ACharacterBase::Move(const FInputActionValue& value)
{
	// ī�޶� ����
	if (currState == EPlayerState::CameraMode)
	{
	
	}
	// ī�޶� ��尡 �ƴϸ�
	else
	{
		FVector2D dir = value.Get<FVector2D>();


		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, dir.Y);
		AddMovementInput(RightDirection, dir.X);
	}

}

void ACharacterBase::TriggerA(const FInputActionValue& value)
{
	
}

void ACharacterBase::StartedA()
{
		switch (currState)
		{
			case (EPlayerState::Idle):
			{
/*				SetSmallWidget(true);*/
			}
			break;
			case (EPlayerState::OnDoor):
			{
				
				currDoor->OpenDoor();
				
			}
			break;
			// ��Ʈ ���¶��
			case (EPlayerState::SelectedProduct):
			{
				productGhost->SetActive(false);
				SpawnProduct();
			}
			break;
			case (EPlayerState::SpawnProduct):
			{
				
			}
			break;
			case (EPlayerState::OpenWidget):
			{
				compWidgetPointer_right->PressPointerKey(EKeys::LeftMouseButton);
			}
		}
}

void ACharacterBase::ReleaseA()
{
	UE_LOG(LogTemp,Warning, TEXT("A"))

	if(currState == EPlayerState::OpenWidget || currState == EPlayerState::OpenProductWidget)
	{
		compWidgetPointer_right->ReleasePointerKey(EKeys::LeftMouseButton);

	}
}

void ACharacterBase::StartedB()
{
	UE_LOG(LogTemp, Warning, TEXT("B"))
		// Y ��ư ���

		switch (currState)
		{

			case EPlayerState::Idle:
			{
				SetLeftHandWidget();
			}
			break;
			// ���� �÷��̾��� ���°� ��Ʈ���
			case EPlayerState::SelectedProduct:
			{
				productGhost->RotateGhost();
			}
			case EPlayerState::OpenProductWidget:
			{
			}
			break;

		}
}

void ACharacterBase::Started1()
{
// 	currState = EPlayerState::Idle;
// 	UE_LOG(LogTemp,Warning, TEXT("Button : 1"))
// 	bDebugLine = !bDebugLine;
	
}

void ACharacterBase::Started2()
{
	UE_LOG(LogTemp,Warning, TEXT("Button : 2"))

		// ī�޶� ����
		if (currState == EPlayerState::CameraMode)
		{
			
			// ī�޶� ������ ������
			playerCon->SetViewTarget(this);
			
			// Idle ���·�
			ChangeState(EPlayerState::Idle);
		}
		// ī�޶� ��尡 �ƴϸ�
		else
		{
			// ī�޶� ž���
			playerCon->SetViewTarget(topViewCam);
		
			// ī�޶� ����
			ChangeState(EPlayerState::CameraMode);
		}
		
}

void ACharacterBase::Started3()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Button : 3"))

	if (compInteraction->hitActorState == EHitActorState::Product)
	{
		selectedProduct = Cast<AProductBase>(compInteraction->hitActor);
		if (selectedProduct != nullptr)
		{
			SetSmallWidget(true);
			ChangeState(EPlayerState::OpenWidget);
		}
	}
	else if (compInteraction->hitActorState == EHitActorState::Floor)
	{
		selectedFloor = Cast<AJS_FloorBase>(compInteraction->hitActor);
		if (selectedFloor != nullptr)
		{
			SetSmallWidget(true);
			ChangeState(EPlayerState::OpenWidget);
		}
	}
	else if (compInteraction->hitActorState == EHitActorState::Wall)
	{
		selectedWall = Cast<AJS_WallBase>(compInteraction->hitActor);
		if (selectedWall != nullptr)
		{
			SetSmallWidget(true);
			ChangeState(EPlayerState::OpenWidget);
		}
	}
}

void ACharacterBase::Started4()
{
	if (bSmallWidget)
	{
		SetSmallWidget(false);
	}
}

void ACharacterBase::Started5()
{
	TakeScreenShot();
	isNight = !isNight;
	ChangeDayNight(isNight);
}

void ACharacterBase::CameraRotate(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	float currYaw = compCamera->GetComponentRotation().Yaw;
	float currPitch = compCamera->GetComponentRotation().Pitch;
	currPitch += axis.Y * 10.f * GetWorld()->DeltaTimeSeconds;
	currYaw += axis.X * 10.f * GetWorld()->DeltaTimeSeconds;
	compCamera->SetRelativeRotation(FRotator(currPitch, currYaw, 0));

}

void ACharacterBase::HandRotate(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	float currPitch = compRightCon->GetRelativeRotation().Pitch;
	currPitch += axis.Y * 100 * GetWorld()->DeltaTimeSeconds;

	float currYaw = compRightCon->GetRelativeRotation().Yaw;
	currYaw += axis.X * 100 * GetWorld()->DeltaTimeSeconds;

	FMath::Clamp(currYaw,-60,60);
	FMath::Clamp(currPitch,-60,60);
	compRightCon->SetRelativeRotation(FRotator(currPitch,currYaw,0));
}

void ACharacterBase::ChangeState(EPlayerState value)
{
	currState = value;
	// ���� ���� ����Ʈ�� ����
	UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerState"), true);
	if (enumPtr != nullptr)
	{
		stateName = *enumPtr->GetNameStringByIndex((int32)(currState));
	}
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, stateName, true, FVector2D(3));
}


void ACharacterBase::SpawnProduct()
{
	
	// ���� ��ġ�� �����ϸ� (canplace)
	if (productGhost->canPlace)
	{
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		product = GetWorld()->SpawnActor<AProductBase>(productManager->selectedProduct->GetClass(), productGhost->GetActorLocation(), productGhost->GetActorRotation(), spawnParams);
		product->SetInit(productManager->selectedProduct->info);
		if (product->kindProduct == 1)
		{
			light = Cast<ALightBase>(product);
			light->SetLights();
		}
	}
	// ���� ��ġ�� �Ұ����ϴٸ�
	else
	{
	}
}

void ACharacterBase::IdleState()
{
	compInteraction->InteractionLineTrace();
}


void ACharacterBase::SelectedProductState()
{
	compInteraction->InteractionLineTrace();
	productGhost->SetActive(true);
	productGhost->SetActorLocation(compInteraction->actorLoc);
}


void ACharacterBase::SetSmallWidget(bool value)
{
	// ������ ��ǰ ���� ����
	smallWidget = Cast<AJS_WidgetActor>(productManager->spawnedSmallWidget);

	// �÷��̾�� ������ ���̰� ���ϱ�
	smallWidgetLoc = UKismetMathLibrary::VLerp(GetActorLocation(),  compInteraction->actorLoc, 0.7f);


	// ������ ���� ������ ��ġ��
	smallWidget->SetActorLocation(smallWidgetLoc);



	if (value)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTIVE PRODUCT WIDGET"))

		// ���� Ȱ��ȭ
		smallWidget->SetActive(value);

		// ĳ���� ���¸� ���� ���·�
		ChangeState(EPlayerState::OpenProductWidget);

	}
	else
	{
		// ������ ��Ȱ��ȭ
		smallWidget->SetActive(false);

		// ĳ���� ���¸� �⺻ ���·�
		ChangeState(EPlayerState::Idle);
	}
}

//�޼� ��ư X ---> �޼� ���� ����, �ݱ�
void ACharacterBase::SetLeftHandWidget()
{
// 	ACSVLoader* csv = Cast<ACSVLoader>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSVLoader::StaticClass())); //----->��ٱ��� �׽�Ʈ(������)
// 	csv->CreateProductInCart(); //----->��ٱ��� �׽�Ʈ(������)
// 	return; //----->��ٱ��� �׽�Ʈ(������)
	
	if (isWidgetOpen == false) //������ �������� �� = �� ���� ��
	{
		UE_LOG(LogTemp, Warning, TEXT("Lefthand Widget ---> Pressed ---> Open"));
		SetWidgetActive(0,true); //��ư X �� ������ ������ ���δ�
		ChangeState(EPlayerState::OpenWidget);
	}
	else //������ �������� �� = ���� ��
	{
		UE_LOG(LogTemp, Warning, TEXT("Lefthand Widget ---> Pressed ---> Close"));
		SetWidgetActive(0,false); //��ư X �� ������ ������ �� ���δ�
		
		// ������ �����ߴٸ�
		ChangeState(EPlayerState::SelectedProduct);
	}
}

void ACharacterBase::SetWidgetActive(int32 compIdx,bool value)
{

	isWidgetOpen = value;
	
	arrWidgetComp[compIdx]->SetVisibility(value);
	if (value)
	{
		arrWidgetComp[compIdx]->SetCollisionProfileName("UI");
	}
	else
	{
		arrWidgetComp[compIdx]->SetCollisionProfileName("NoCollision");
	}
}

void ACharacterBase::SetWidgetArr()
{
	//���� ������Ʈ �迭�� �־����
	arrWidgetComp.Add(compLefthandWidget); //0
	arrWidgetComp.Add(compAssetMainWidget); //1
	arrWidgetComp.Add(compScreenShotWidget); //2
	arrWidgetComp.Add(compSettingWidget); //3


	// ���� ������Ʈ �׸��� ����
	for (int32 i = 0; i < arrWidgetComp.Num(); i++)
	{
		arrWidgetComp[i]->SetCastShadow(false);
		arrWidgetComp[i]->SetCollisionProfileName("NoCollision");
	}
}

void ACharacterBase::ChangeDayNight(bool value)
{
	// ��ġ�Ǿ��ִ� �𷺼ų� ����Ʈ ���� ��������
	sunLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(),ADirectionalLight::StaticClass()));

	if (sunLight != nullptr)
	{
		if (value)
		{
			// ���͸� ���� ������ ����
			sunLight->SetActorRotation(FRotator(250.f, 220.f, 120.f));
			
			// ����Ʈ �÷��� ������� (�⺻��)
			sunLight->SetLightColor(FLinearColor(1,1,1));
		}
		else
		{
			// ���͸� ���� ������ ����
			sunLight->SetActorRotation(FRotator(3.f,-160.f,260.f));

			// ����Ʈ �÷��� ���������
			sunLight->SetLightColor(FLinearColor(0.2,0.2,0.4));
			
		}
	}	


}

//(���� �߰�) �޼տ� �ֹ� �ݾ� ���� ����
void ACharacterBase::VisibleOrderWidget()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//���� 03_Cart ���� �̸�
	if (levelName.Contains("03_Cart"))
	{
		//���� ���� ��Ų��
		compOrderWidget->SetVisibility(true);
	}
}

void ACharacterBase::TakeScreenShot()
{
	// ��ũ���� ���
	const FDateTime Now = FDateTime::Now();

	// ��ũ���� ����
#if WITH_EDITOR
	const FString imgDir = FString::Printf(TEXT("%s/%s"), *FPaths::ProjectDir(),TEXT("Screenshots"));
#else
	const FString imgDir = FString::Printf(TEXT("%s/../%s"), *FPaths::ProjectDir(),TEXT("Screenshots"));
#endif

	const FString imgFilename = FString::Printf(TEXT("%s/Screenshot_%d%02d%02d_%02d%02d.png"), *imgDir, Now.GetYear(), Now.GetMonth(), Now.GetDay(), Now.GetHour(), Now.GetMinute());

	FScreenshotRequest::RequestScreenshot(imgFilename, false, false);
}


//(���� �߰�) Ÿ��Ʋ �������� �޼� �޴� ���� �̳���
void ACharacterBase::VisibleHandMenuWidget()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//���� 01_Title ���� �̸�
	if (levelName.Contains("01_Title"))
	{
		//�� �޴� ���� �� ���δ�
		SetWidgetActive(0, false);

	}
}

