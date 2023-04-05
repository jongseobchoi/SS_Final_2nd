// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"

AFinalGameModeBase::AFinalGameModeBase() //추가
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFinalGameModeBase::BeginPlay() //추가 
{
	Super::BeginPlay();

}

void AFinalGameModeBase::Tick(float DeltaTime) //추가
{
	Super::Tick(DeltaTime);

}

