// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_CartManager.h"
#include "CSVLoader.h"
#include <Kismet/GameplayStatics.h>
#include "RIM_CartProduct.h"
#include "RIM_Widget_CartProduct.h"

// Sets default values
ARIM_CartManager::ARIM_CartManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ARIM_CartManager::BeginPlay()
{
	Super::BeginPlay();

	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld()));
	

//  	ConstructorHelpers::FClassFinder<ARIM_CartProduct> tempProduct(TEXT("/Script/Engine.Blueprint'/Game/SS_Final/BluePrints/BP_CartProduct.BP_CartProduct_C'"));
//  	if (tempProduct.Succeeded())
//  	{
// 		cartProductFactory = tempProduct.Class;
//  	}

	//SetProductInfoInCart(); //������ �� ��ǰ 3D �̹���, ���� ���� �ǰ� �Ѵ�

	id = csvLoader->GetProductInfoInCart();

}

// Called every frame
void ARIM_CartManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��ǰ ����(2��. �Ʒ� SetProductInfoInCart())
// 	currentTime += DeltaTime;
// 
// 	if (currentTime > 5)
// 	{
// 		//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //---> �� ���� ȣ��ǰ� ���� �Ϸ�
// 
// 		if (x < id.Num()) //id = ��ٱ��� ��� ��ư Ŭ���� ��ǰ(����). x = ��ٱ��Ͽ� ���� ����
// 		{
// 			FVector pos(1600, 1230, 100); //��ġ ����
// 
// 			ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos, FRotator::ZeroRotator); // ��ǰ ����ƽ�޽� ����
// 			obj->SetInit(id[x]); //SetInit(FWidgetProductInfo info)
// 
// 			currentTime = 0; //�ʱ�ȭ
// 
// 			x++; // x = x+1. 1���� ����
// 		}
// 	}

	SetProductInfoInCart();

}


//��ǰ ����(1��)
/*
void ARIM_CartManager::SetProductInfoInCart()
{
	TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart();

	FVector pos(1600, 1230, 200); //��ġ ����

	for (int32 i = 0; i < id.Num(); i++)
	{
		if (currentTime < 5)
		{
			//ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos + FVector::RightVector * 100 * (i + 1), FRotator::ZeroRotator); //---> ������
			obj->SetInit(id[i]);

			//total += id[i].price; //���⼭ ����ϰų� Order �������� ���
		}
	}
}*/

//��ǰ ����(3��)
void ARIM_CartManager::SetProductInfoInCart() // -----> ƽ�� �ִ� �ڵ� �Լ��� ����
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > 5)
	{
		//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //---> �� ���� ȣ��ǰ� ���� �Ϸ�

		if (x < id.Num()) //id = ��ٱ��� ��� ��ư Ŭ���� ��ǰ(����). x = ��ٱ��Ͽ� ���� ����
		{
			FVector pos(1600, 1230, 100); //��ġ ����

			ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos, FRotator::ZeroRotator); // ��ǰ ����ƽ�޽� ����
			obj->SetInit(id[x]); //SetInit(FWidgetProductInfo info)

			currentTime = 0; //�ʱ�ȭ

			x++; // x = x+1. 1���� ����
		}
	}
}





//���� �׽�Ʈ
/*
void ARIM_CartManager::DeleteProductInCart(FWidgetProductInfo id)
{
	TArray<AActor*> cartProductActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARIM_CartProduct::StaticClass(), cartProductActor);
	if (cartProductActor.IsValidIndex(id))
	{
		cartProductActor[id]->Destroy();
	}
}*/