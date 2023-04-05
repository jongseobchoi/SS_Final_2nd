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
	// 객체가 생성될떄  입력함
	// 멤버변수로 받는다
	// 
    //매니저가 Product로 생성하자
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compProductMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("COMP MESH"));
	SetRootComponent(compProductMesh);

	// 이거 배열에 저장하고 
	// 라이트 있으면 베이스 멤버변수로 light soket
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

