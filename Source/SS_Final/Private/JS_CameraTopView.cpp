// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_CameraTopView.h"
#include <Components/SceneComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

AJS_CameraTopView::AJS_CameraTopView()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	SetRootComponent(compScene);

	compArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	compArm->SetupAttachment(compScene);
	compArm->SetRelativeRotation(FRotator(-90,0,0));

	compCam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	compCam->SetupAttachment(compArm);
	compCam->SetRelativeLocation(FVector(-900,0,0));

}

// Called when the game starts or when spawned
void AJS_CameraTopView::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJS_CameraTopView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}