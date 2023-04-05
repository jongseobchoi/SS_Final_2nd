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

	//���� �߰�
	widget_AssetMain = CreateDefaultSubobject<UWidgetComponent>(TEXT("Asset Main Widget Comp"));
	widget_AssetMain->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AWidgetActor_AssetMain::BeginPlay()
{
	Super::BeginPlay();

	//������ �Լ��� ������ ���� �� �� �ְ� ���ִ� �ڵ�
	if (widget_AssetMain != nullptr) //���Ϳ� ������ ������
	{
		UWidget_AssetMain* assetMainWidget = Cast<UWidget_AssetMain>(widget_AssetMain->GetWidget());

		if (assetMainWidget != nullptr) //assetMainWidget �����̸�
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

//[�������� ��ư�� Ŭ�� ���� �� ���� �� �Լ�]
//��з� ��ư
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

//�Һз� ��ư
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

//��ǰ ��ư
void AWidgetActor_AssetMain::product01()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product01"));

	//Ŭ���� ��ǰ�� ���� �ȴ�
	//�������� �� ���δ�(�ı��Ѵ�)

}

void AWidgetActor_AssetMain::product02()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product02"));

	//Ŭ���� ��ǰ�� ���� �ȴ�
	//�������� �� ���δ�(�ı��Ѵ�)

}

void AWidgetActor_AssetMain::product03()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product03"));

	//Ŭ���� ��ǰ�� ���� �ȴ�
	//�������� �� ���δ�(�ı��Ѵ�)
}

void AWidgetActor_AssetMain::product04()
{
	UE_LOG(LogTemp, Warning, TEXT("AssetMain ---> Click  ---> Product04"));

	//Ŭ���� ��ǰ�� ���� �ȴ�
	//�������� �� ���δ�(�ı��Ѵ�)
}