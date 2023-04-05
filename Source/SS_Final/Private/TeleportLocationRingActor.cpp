// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportLocationRingActor.h"
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>

// Sets default values
ATeleportLocationRingActor::ATeleportLocationRingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//[�ڷ���Ʈ(�̵�) ��ġ ��]
	//���̾ư���(����Ʈ) �߰�
	compNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport Ring"));
	compNiagara->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ATeleportLocationRingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportLocationRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

