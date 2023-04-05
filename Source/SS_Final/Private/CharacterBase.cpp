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
	//씬(카메라, 컨트롤러 부모 용으로 만듬)
	compScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	compScene->SetupAttachment(RootComponent);
	compScene->SetRelativeLocation(FVector(0, 0, 0)); //▶필요 시 추후 변경

	//[카메라]
	//카메라 
	compCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	compCamera->SetupAttachment(compScene);
	compCamera->SetRelativeLocation(FVector(-60, 0, 0)); //▶필요 시 추후 변경
	//스샷 위젯을 카메라에 붙임
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

	//[왼손]
	//컨트롤러
	compLeftCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	compLeftCon->SetupAttachment(compScene);
	//메시
	meshLeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	meshLeftHand->SetupAttachment(compLeftCon);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempLeftHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'")); //▶기본 여성 손. 필요 시 추후 변경
	if (tempLeftHand.Succeeded())
	{
		meshLeftHand->SetSkeletalMesh(tempLeftHand.Object);
	}
	meshLeftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	meshLeftHand->SetRelativeRotation(FRotator(-25, 180, 90)); //▶필요 시 추후 변경
	meshLeftHand->SetRelativeLocation(FVector(0, -15, 0)); //▶필요 시 추후 변경
	//로그(확인용)
// 	logLeft = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LeftLogText"));
// 	logLeft->SetupAttachment(compLeftCon);
// 	logLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //텍스트 180 수정
// 	logLeft->SetRelativeLocation(FVector(0.0f, 20.f, 0.0f)); //위치 수정
// 	logLeft->SetRelativeScale3D(FVector(0.25)); //스케일 수정
// 	logLeft->SetTextRenderColor(FColor::Yellow);
// 	logLeft->SetHorizontalAlignment(EHTA_Center);
// 	logLeft->SetVerticalAlignment(EVRTA_TextCenter);

	//왼손 위젯을 왼손 컨트롤러에 붙임-----------------------------------------------------------------------------> 왼손 메뉴 위젯
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

	//가구 메인 위젯을 카메라에 붙임--------------------------------------------------------------------------------> 왼손 제품 위젯
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
	
	//세팅 위젯을 카메라에 붙임-------------------------------------------------------------------------------------> 왼손 세팅 위젯
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
	
	//주문 위젯을 왼손 컨트롤러에 붙임-------------------------------------------------------------------------------> 왼손 장바구니 총 금액/주문하기 버튼 위젯
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
	//모션 소스 선택
	compLeftCon->MotionSource = "Left";

	//[오른손]
	//컨트롤러
	compRightCon = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	compRightCon->SetupAttachment(compScene);
	//메시
	meshRightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	meshRightHand->SetupAttachment(compRightCon);
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRihgtHand(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'")); //▶기본 여성 손. 필요 시 추후 변경
	if (tempRihgtHand.Succeeded())
	{
		meshRightHand->SetSkeletalMesh(tempRihgtHand.Object);
	}
	meshRightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision); //메시 노콜리전
	meshRightHand->SetRelativeRotation(FRotator(25, 0, 90)); //▶필요 시 추후 변경
	meshRightHand->SetRelativeLocation(FVector(0, 15, 0));
	//로그(확인용)
// 	logRight = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RightLogText"));
// 	logRight->SetupAttachment(compRightCon);
// 	logRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f)); //텍스트 180 수정
// 	logRight->SetRelativeLocation(FVector(0.0f, -20.f, 0.0f)); //위치 수정
// 	logRight->SetRelativeScale3D(FVector(0.25)); //스케일 수정
// 	logRight->SetTextRenderColor(FColor::Yellow);
// 	logRight->SetHorizontalAlignment(EHTA_Center);
// 	logRight->SetVerticalAlignment(EVRTA_TextCenter);
	//포인터
	compWidgetPointer_right = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	compWidgetPointer_right->SetupAttachment(compRightCon);
	compWidgetPointer_right->SetRelativeLocation(FVector(-1, 12, -1));
	compWidgetPointer_right->SetRelativeRotation(FRotator(-90, 0, 0));
	compWidgetPointer_right->bShowDebug = true; //디버그라인
	//모션 소스 선택
	compRightCon->MotionSource = "Right";


	//axis 값을 이용해서 캐릭터(컨트롤러)를 회전
	bUseControllerRotationPitch = true;
	//플레이어 지정...?
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	

	//[플레이어에 액터 컴포넌트 추가]
	//이동, 텔레포트 관련
	compMove = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	//위젯(포인터) 관련
	compWidget = CreateDefaultSubobject<UWidgetPointerComponent>(TEXT("WidgetComponent"));


	// 캐릭터 맵핑 생성자에서 찾기
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempCharMap(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/SS_Final/CharacterInput/IMC_CharacterMapping.IMC_CharacterMapping'"));
	if (tempCharMap.Succeeded())
	{
		CharacterMapping = tempCharMap.Object;
	}

	// 디버그 맵핑 생성자에서 찾기
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempDebugMap(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/SS_Final/CharacterInput/IMC_CharacterDebug.IMC_CharacterDebug'"));
	if (tempDebugMap.Succeeded())
	{
		DebugMapping = tempDebugMap.Object;
	}

	// 라인트레이스 쏘는 컴프
	compInteraction = CreateDefaultSubobject<UJS_InteractionComp>(TEXT("COMP INTERACTION"));

	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	//1. 플레이어 컨트롤러를 가져온다.
	playerCon = GetWorld()->GetFirstPlayerController();

	//2. 플레이어 컨트롤러에서 EnhancedInputLocalPlayerSubsystem 을 가져온다.
	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	//3. 가져온 Subsystem 에 IMC 를 등록한다.(우선순위 0번) , selectInput 변수에 따른 context 선택
	subsys->AddMappingContext(CharacterMapping, selectInput);
	subsys->AddMappingContext(DebugMapping, 1-selectInput);
	
	
	


	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
	// 고스트 미리 스폰
	
	if (productManager != nullptr)
	{
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		productGhost = GetWorld()->SpawnActor<AJS_ProductGhost>(AJS_ProductGhost::StaticClass(), productManager->GetActorTransform(), spawnParams);
		productGhost->SetActive(false);
		// 탑뷰 카메라 스폰
		topViewCam = GetWorld()->SpawnActor<AJS_CameraTopView>(AJS_CameraTopView::StaticClass(), FVector(0), FRotator(0));
		// 위젯 컴포넌트 배열 초기화 함수
	}

	SetWidgetArr();
	VisibleOrderWidget(); //왼손 주문금액 위젯 실행
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
		//이동 함수 실행
		compMove->SetupPlayerInputComponent(EnhancedInputComponent);
		//위젯 포인터 실행
		compWidget->SetupPlayerInputComponent(EnhancedInputComponent);

		//[오른손]
		//오른손 버튼 A ---> 오른손 위젯 열기, 닫기 ---> 왼손으로 옮김(삭제NO) ---> 위젯에서 가구 놓기
		EnhancedInputComponent->BindAction(rightA, ETriggerEvent::Started, this, &ACharacterBase::StartedA);

		//[왼손]
		//왼손 버튼 X ---> 오른손 위젯 열기, 닫기
		FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		//현재 01_Title 레벨 이면
		if (levelName.Contains("01_Title"))
		{
			return;
		}
		else
		{
/*			EnhancedInputComponent->BindAction(LeftX, ETriggerEvent::Started, this, &ACharacterBase::SetLeftHandWidget);*/
		}



		// 디버그용 키 바인딩
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Started, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(cameraAction, ETriggerEvent::Triggered, this, &ACharacterBase::CameraRotate);
		EnhancedInputComponent->BindAction(mouseXY, ETriggerEvent::Triggered, this, &ACharacterBase::HandRotate);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Triggered, this, &ACharacterBase::TriggerA);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Started, this, &ACharacterBase::StartedA);
		EnhancedInputComponent->BindAction(pressA, ETriggerEvent::Completed, this, &ACharacterBase::ReleaseA);
		EnhancedInputComponent->BindAction(pressB, ETriggerEvent::Started, this, &ACharacterBase::StartedB);


		// 디버그용 키 바인딩 2
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

// 디버그용 캐릭터 움직이는 함수(WASD)
void ACharacterBase::Move(const FInputActionValue& value)
{
	// 카메라 모드면
	if (currState == EPlayerState::CameraMode)
	{
	
	}
	// 카메라 모드가 아니면
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
			// 고스트 상태라면
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
		// Y 버튼 대용

		switch (currState)
		{

			case EPlayerState::Idle:
			{
				SetLeftHandWidget();
			}
			break;
			// 만약 플레이어의 상태가 고스트라면
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

		// 카메라 모드면
		if (currState == EPlayerState::CameraMode)
		{
			
			// 카메라를 원래의 것으로
			playerCon->SetViewTarget(this);
			
			// Idle 상태로
			ChangeState(EPlayerState::Idle);
		}
		// 카메라 모드가 아니면
		else
		{
			// 카메라를 탑뷰로
			playerCon->SetViewTarget(topViewCam);
		
			// 카메라 모드로
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
	// 현재 상태 뷰포트에 띄우기
	UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerState"), true);
	if (enumPtr != nullptr)
	{
		stateName = *enumPtr->GetNameStringByIndex((int32)(currState));
	}
	GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, stateName, true, FVector2D(3));
}


void ACharacterBase::SpawnProduct()
{
	
	// 만약 배치가 가능하면 (canplace)
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
	// 만약 배치가 불가능하다면
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
	// 스폰한 제품 위젯 변수
	smallWidget = Cast<AJS_WidgetActor>(productManager->spawnedSmallWidget);

	// 플레이어와 액터의 사이값 구하기
	smallWidgetLoc = UKismetMathLibrary::VLerp(GetActorLocation(),  compInteraction->actorLoc, 0.7f);


	// 위젯을 맞은 액터의 위치로
	smallWidget->SetActorLocation(smallWidgetLoc);



	if (value)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTIVE PRODUCT WIDGET"))

		// 위젯 활성화
		smallWidget->SetActive(value);

		// 캐릭터 상태를 위젯 상태로
		ChangeState(EPlayerState::OpenProductWidget);

	}
	else
	{
		// 위젯을 비활성화
		smallWidget->SetActive(false);

		// 캐릭터 상태를 기본 상태로
		ChangeState(EPlayerState::Idle);
	}
}

//왼손 버튼 X ---> 왼손 위젯 열기, 닫기
void ACharacterBase::SetLeftHandWidget()
{
// 	ACSVLoader* csv = Cast<ACSVLoader>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSVLoader::StaticClass())); //----->장바구니 테스트(선생님)
// 	csv->CreateProductInCart(); //----->장바구니 테스트(선생님)
// 	return; //----->장바구니 테스트(선생님)
	
	if (isWidgetOpen == false) //위젯이 닫혀있을 때 = 안 보일 때
	{
		UE_LOG(LogTemp, Warning, TEXT("Lefthand Widget ---> Pressed ---> Open"));
		SetWidgetActive(0,true); //버튼 X 를 누르면 위젯이 보인다
		ChangeState(EPlayerState::OpenWidget);
	}
	else //위젯이 열려있을 때 = 보일 때
	{
		UE_LOG(LogTemp, Warning, TEXT("Lefthand Widget ---> Pressed ---> Close"));
		SetWidgetActive(0,false); //버튼 X 를 누르면 위젯이 안 보인다
		
		// 가구를 선택했다면
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
	//위젯 컴포넌트 배열에 넣어놓기
	arrWidgetComp.Add(compLefthandWidget); //0
	arrWidgetComp.Add(compAssetMainWidget); //1
	arrWidgetComp.Add(compScreenShotWidget); //2
	arrWidgetComp.Add(compSettingWidget); //3


	// 위젯 컴포넌트 그림자 끄기
	for (int32 i = 0; i < arrWidgetComp.Num(); i++)
	{
		arrWidgetComp[i]->SetCastShadow(false);
		arrWidgetComp[i]->SetCollisionProfileName("NoCollision");
	}
}

void ACharacterBase::ChangeDayNight(bool value)
{
	// 배치되어있는 디렉셔널 라이트 액터 가져오기
	sunLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(),ADirectionalLight::StaticClass()));

	if (sunLight != nullptr)
	{
		if (value)
		{
			// 액터를 낮의 각도로 변경
			sunLight->SetActorRotation(FRotator(250.f, 220.f, 120.f));
			
			// 라이트 컬러를 흰색으로 (기본값)
			sunLight->SetLightColor(FLinearColor(1,1,1));
		}
		else
		{
			// 액터를 밤의 각도로 변경
			sunLight->SetActorRotation(FRotator(3.f,-160.f,260.f));

			// 라이트 컬러를 보라색으로
			sunLight->SetLightColor(FLinearColor(0.2,0.2,0.4));
			
		}
	}	


}

//(정림 추가) 왼손에 주문 금액 위젯 노출
void ACharacterBase::VisibleOrderWidget()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//현재 03_Cart 레벨 이면
	if (levelName.Contains("03_Cart"))
	{
		//위젯 노출 시킨다
		compOrderWidget->SetVisibility(true);
	}
}

void ACharacterBase::TakeScreenShot()
{
	// 스크린샷 찍기
	const FDateTime Now = FDateTime::Now();

	// 스크린샷 저장
#if WITH_EDITOR
	const FString imgDir = FString::Printf(TEXT("%s/%s"), *FPaths::ProjectDir(),TEXT("Screenshots"));
#else
	const FString imgDir = FString::Printf(TEXT("%s/../%s"), *FPaths::ProjectDir(),TEXT("Screenshots"));
#endif

	const FString imgFilename = FString::Printf(TEXT("%s/Screenshot_%d%02d%02d_%02d%02d.png"), *imgDir, Now.GetYear(), Now.GetMonth(), Now.GetDay(), Now.GetHour(), Now.GetMinute());

	FScreenshotRequest::RequestScreenshot(imgFilename, false, false);
}


//(정림 추가) 타이틀 레벨에서 왼손 메뉴 위젯 미노출
void ACharacterBase::VisibleHandMenuWidget()
{
	FString levelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//현재 01_Title 레벨 이면
	if (levelName.Contains("01_Title"))
	{
		//손 메뉴 위젯 안 보인다
		SetWidgetActive(0, false);

	}
}

