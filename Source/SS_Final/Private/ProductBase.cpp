// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductBase.h"
#include "CharacterBase.h"
#include <Kismet/GameplayStatics.h>
#include "JS_ProductGhost.h"
#include "JS_ProductManager.h"
#include "JS_InteractionComp.h"

// Sets default values
AProductBase::AProductBase()
{
	// ��ü�� �����ɋ�  �Է���
	// ��������� �޴´�
	// 
    //�Ŵ����� Product�� ��������
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compProductMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	SetRootComponent(compProductMesh);

	// �̰� �迭�� �����ϰ� 
	// ����Ʈ ������ ���̽� ��������� light soket
	//compProductMesh->GetAllSocketNames()

	
}

// Called when the game starts or when spawned
void AProductBase::BeginPlay()
{
	Super::BeginPlay();
	
	
	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AJS_ProductManager::StaticClass()));
}

// Called every frame
void AProductBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProductBase::RotateProduct()
{
	UE_LOG(LogTemp, Warning, TEXT("RotateProduct"))
	FRotator currRot = GetActorRotation();
	float angle = 89.9f;
	currRot.Yaw += angle;
	UE_LOG(LogTemp, Warning, TEXT("newRot.Yaw : %f"), currRot.Yaw)
	SetActorRotation(FRotator(currRot.Pitch, currRot.Yaw, currRot.Roll));
}

void AProductBase::SetInit(FWidgetProductInfo value)
{
	info = value;
	compProductMesh->SetStaticMesh(info.mesh);
	compProductMesh->SetCollisionProfileName("ProductState");
}

