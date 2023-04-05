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

	//SetProductInfoInCart(); //시작할 때 제품 3D 이미지, 위젯 스폰 되게 한다

	id = csvLoader->GetProductInfoInCart();

}

// Called every frame
void ARIM_CartManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//제품 스폰(2차. 아래 SetProductInfoInCart())
// 	currentTime += DeltaTime;
// 
// 	if (currentTime > 5)
// 	{
// 		//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //---> 한 번만 호출되게 수정 완료
// 
// 		if (x < id.Num()) //id = 장바구니 담기 버튼 클릭한 제품(정보). x = 장바구니에 담은 수량
// 		{
// 			FVector pos(1600, 1230, 100); //위치 수정
// 
// 			ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos, FRotator::ZeroRotator); // 제품 스테틱메시 스폰
// 			obj->SetInit(id[x]); //SetInit(FWidgetProductInfo info)
// 
// 			currentTime = 0; //초기화
// 
// 			x++; // x = x+1. 1개씩 증가
// 		}
// 	}

	SetProductInfoInCart();

}


//제품 스폰(1차)
/*
void ARIM_CartManager::SetProductInfoInCart()
{
	TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart();

	FVector pos(1600, 1230, 200); //위치 수정

	for (int32 i = 0; i < id.Num(); i++)
	{
		if (currentTime < 5)
		{
			//ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos + FVector::RightVector * 100 * (i + 1), FRotator::ZeroRotator); //---> 선생님
			obj->SetInit(id[i]);

			//total += id[i].price; //여기서 계산하거나 Order 위젯에서 계산
		}
	}
}*/

//제품 스폰(3차)
void ARIM_CartManager::SetProductInfoInCart() // -----> 틱에 있던 코드 함수로 만듬
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > 5)
	{
		//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //---> 한 번만 호출되게 수정 완료

		if (x < id.Num()) //id = 장바구니 담기 버튼 클릭한 제품(정보). x = 장바구니에 담은 수량
		{
			FVector pos(1600, 1230, 100); //위치 수정

			ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos, FRotator::ZeroRotator); // 제품 스테틱메시 스폰
			obj->SetInit(id[x]); //SetInit(FWidgetProductInfo info)

			currentTime = 0; //초기화

			x++; // x = x+1. 1개씩 증가
		}
	}
}





//삭제 테스트
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