// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include <MotionControllerComponent.h>

// Sets default values for this component's properties
UWidgetPointerComponent::UWidgetPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ACharacterBase>(GetOwner());
	
}


// Called every frame
void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//[SetupPlayerInputComponent] 가상합수
void UWidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	//오른손 트리거 ---> 위젯 클릭
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Started, this, &UWidgetPointerComponent::WidgetClickPressed);
	PlayerInputComponent->BindAction(rightTrigger, ETriggerEvent::Completed, this, &UWidgetPointerComponent::WidgetClickReleased);

}


//오른손 트리거 ---> UI 요소에 대한 버튼 Pressed 때 함수
void UWidgetPointerComponent::WidgetClickPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Pressed"));

	player->compWidgetPointer_right->PressPointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Press 처리)
	
}

//오른손 트리거 ---> UI 요소에 대한 버튼 Released 때 함수
void UWidgetPointerComponent::WidgetClickReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Pointer ---> Release"));

	player->compWidgetPointer_right->ReleasePointerKey(EKeys::LeftMouseButton); //마우스 왼쪽과 동일하게 처리(Release 처리)
	
}