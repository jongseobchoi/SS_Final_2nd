// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor_AssetMain.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Widget_AssetMain.h"

// Sets default values
AWidgetActor_AssetMain::AWidgetActor_AssetMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//위젯 추가
	widget_AssetMain = CreateDefaultSubobject<UWidgetComponent>(TEXT("Asset Main Widget Comp"));
	widget_AssetMain->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AWidgetActor_AssetMain::BeginPlay()
{
	Super::BeginPlay();

	//액터의 함수를 위젯이 실행 할 수 있게 해주는 코드
	if (widget_AssetMain != nullptr) //액터에 위젯이 있으면
	{
		UWidget_AssetMain* assetMainWidget = Cast<UWidget_AssetMain>(widget_AssetMain->GetWidget());

		if (assetMainWidget != nullptr) //assetMainWidget 위젯이면
		{
			assetMainWidget->widgetActor_AssetMain = this;
		}
	}
	
}

// Called every frame
void AWidgetActor_AssetMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//[위젯에서 버튼을 클릭 했을 떄 실행 될 함수]
//대분류 버튼
void AWidgetActor_AssetMain::Category01()
{
	
}

void AWidgetActor_AssetMain::Category02()
{

}

void AWidgetActor_AssetMain::Category03()
{

}

void AWidgetActor_AssetMain::Category04()
{

}

//소분류 버튼
void AWidgetActor_AssetMain::type01()
{

}

void AWidgetActor_AssetMain::type02()
{

}

void AWidgetActor_AssetMain::type03()
{

}

void AWidgetActor_AssetMain::type04()
{

}

void AWidgetActor_AssetMain::type05()
{

}

void AWidgetActor_AssetMain::type06()
{

}

void AWidgetActor_AssetMain::type07()
{

}

void AWidgetActor_AssetMain::type08()
{

}

//제품 버튼
void AWidgetActor_AssetMain::product01()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product01"));

	//클릭한 제품이 노출 된다
	//위젯액터 안 보인다(파괴한다)

}

void AWidgetActor_AssetMain::product02()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product02"));

	//클릭한 제품이 노출 된다
	//위젯액터 안 보인다(파괴한다)

}

void AWidgetActor_AssetMain::product03()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product03"));

	//클릭한 제품이 노출 된다
	//위젯액터 안 보인다(파괴한다)
}

void AWidgetActor_AssetMain::product04()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product04"));

	//클릭한 제품이 노출 된다
	//위젯액터 안 보인다(파괴한다)
}