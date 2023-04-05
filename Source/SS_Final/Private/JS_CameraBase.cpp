// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_CameraBase.h"

AJS_CameraBase::AJS_CameraBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJS_CameraBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AJS_CameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}