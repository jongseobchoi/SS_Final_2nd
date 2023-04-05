// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBase.h"
#include <Components/SpotLightComponent.h>


ALightBase::ALightBase()
{
	PrimaryActorTick.bCanEverTick = true;




}

void ALightBase::BeginPlay()
{
	Super::BeginPlay();

	SetLights();
	kindProduct = 1;
	bLight = false;
	SwitchLights();
}

void ALightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALightBase::SetLights()
{
 	
 	// 소켓의 이름들을 찾음 (소켓 갯수 몇개인지)
 	TArray<FName> socketNames = compProductMesh->GetAllSocketNames();
	for (int32 i = 0; i < socketNames.Num(); i++)
	{
		// 라이트 컴포넌트 이름 정해놓음
		FString compName = FString::Printf(TEXT("COMP LIGHT %d"), i);
		// 새 인스턴스 생성
		compLight = NewObject<USpotLightComponent>(this, USpotLightComponent::StaticClass(), *compName);
		lightComponents.Add(compLight);
		// 컴포넌트를 소켓에 붙이기
		lightComponents[i]->AttachToComponent(compProductMesh, FAttachmentTransformRules::KeepRelativeTransform, socketNames[i]);
		// 모빌리티 설정
		lightComponents[i]->SetMobility(EComponentMobility::Movable);

	}
}

void ALightBase::SwitchLights()
{
	if (bLight == false)
	{
		for (int32 i = 0; i < lightComponents.Num(); i++)
		{
			lightComponents[i]->AttenuationRadius = 1000.f;
			lightComponents[i]->Intensity = 10.f;
			UE_LOG(LogTemp, Warning, TEXT("LightOn"))
		}
		bLight = true;
		
	}
	else
	{
		for (int32 i = 0; i < lightComponents.Num(); i++)
		{
			lightComponents[i]->AttenuationRadius = 15.f;
			lightComponents[i]->Intensity = 0;
			UE_LOG(LogTemp, Warning, TEXT("LightOff"))
		}
		bLight = false;
	}
}
