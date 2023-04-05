// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetActor_Order.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_Widget_Order.h"

// Sets default values
ARIM_WidgetActor_Order::ARIM_WidgetActor_Order()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� �߰�
	widget_Order = CreateDefaultSubobject<UWidgetComponent>(TEXT("Order Widget Comp"));
	widget_Order->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ARIM_WidgetActor_Order::BeginPlay()
{
	Super::BeginPlay();

	//������ �Լ��� ������ ���� �� �� �ְ� ���ִ� �ڵ�
	if (widget_Order != nullptr) //���Ϳ� ������ ������
	{
		URIM_Widget_Order* tempWidget = Cast<URIM_Widget_Order>(widget_Order->GetWidget());

		if (tempWidget != nullptr) //tempWidget �����̸�
		{
			tempWidget->widgetActor_Order = this;
		}
	}

}

// Called every frame
void ARIM_WidgetActor_Order::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

