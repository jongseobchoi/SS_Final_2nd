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
 	
 	// ������ �̸����� ã�� (���� ���� �����)
 	TArray<FName> socketNames = compProductMesh->GetAllSocketNames();
	for (int32 i = 0; i < socketNames.Num(); i++)
	{
		// ����Ʈ ������Ʈ �̸� ���س���
		FString compName = FString::Printf(TEXT("COMP LIGHT %d"), i);
		// �� �ν��Ͻ� ����
		compLight = NewObject<USpotLightComponent>(this, USpotLightComponent::StaticClass(), *compName);
		lightComponents.Add(compLight);
		// ������Ʈ�� ���Ͽ� ���̱�
		lightComponents[i]->AttachToComponent(compProductMesh, FAttachmentTransformRules::KeepRelativeTransform, socketNames[i]);
		// �����Ƽ ����
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
