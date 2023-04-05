// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_ProductManager.h"
#include "Widget_AssetMain.h"
#include "JS_WidgetActor.h"
#include "CSVLoader.h"
#include <Engine/GameInstance.h>
#include "ProductBase.h"
#include "LightBase.h"

// Sets default values
AJS_ProductManager::AJS_ProductManager()
{




	
	
	ConstructorHelpers::FClassFinder<AJS_WidgetActor> tempSmallWidget(TEXT("/Script/CoreUObject.Class'/Script/SS_Final.JS_WidgetActor'"));
	if (tempSmallWidget.Succeeded())
	{
		smallWidgetFactory = tempSmallWidget.Class;
	}
}

// Called when the game starts or when spawned
void AJS_ProductManager::BeginPlay()
{
	Super::BeginPlay();

	CSVLoader = Cast<UCSVLoader>(GetWorld()->GetGameInstance());
	TArray<FWidgetProductInfo> data;
	TArray<FWidgetProductInfo> csvData;
	csvData = CSVLoader->arrProductInfo;
	UE_LOG(LogTemp, Warning, TEXT("__"))
	for (int32 i = 0; i < csvData.Num(); i++)
	{
		UE_LOG(LogTemp, Error, TEXT("CSV %d"),i)
			
		data.Add(csvData[i]);
		if (csvData[i].id % 2000 < 200 && csvData[i].id < 3000)
		{
			lightProduct = NewObject<ALightBase>(this, ALightBase::StaticClass());
			lightProduct->SetInit(data[i]);
			productArr.Add(lightProduct);
		}
		else
		{
			product = NewObject<AProductBase>(this, AProductBase::StaticClass());
			product->SetInit(data[i]);
			productArr.Add(product);
		}
	


		UE_LOG(LogTemp,Warning,TEXT("%d"),productArr[i]->info.id)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *productArr[i]->info.name)


	}

	// Product Widget 스폰 시켜놓기
 	spawnedSmallWidget = GetWorld()->SpawnActor<AJS_WidgetActor>(FVector(0,0,1000),FRotator::ZeroRotator);
	spawnedSmallWidget->SetActive(false);
}

// Called every frame
void AJS_ProductManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	// UI에 따라 선택된 메쉬

}

void AJS_ProductManager::SelectedProduct(int32 value)
{
	selectedProduct = productArr[value];
}

