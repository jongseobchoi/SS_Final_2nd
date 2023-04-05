// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_WidgetActor_CartProduct.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RIM_Widget_CartProduct.h"

// Sets default values
ARIM_WidgetActor_CartProduct::ARIM_WidgetActor_CartProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� �߰�
	widget_CartProduct = CreateDefaultSubobject<UWidgetComponent>(TEXT("Cart Product Widget Comp"));
	widget_CartProduct->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ARIM_WidgetActor_CartProduct::BeginPlay()
{
	Super::BeginPlay();

	//������ �Լ��� ������ ���� �� �� �ְ� ���ִ� �ڵ�
	if (widget_CartProduct != nullptr) //���Ϳ� ������ ������
	{
		URIM_Widget_CartProduct* tempWidget = Cast<URIM_Widget_CartProduct>(widget_CartProduct->GetWidget());

		if (tempWidget != nullptr) //tempWidget �����̸�
		{
			tempWidget->widgetActor_CartProduct = this;
		}
	}
	
}

// Called every frame
void ARIM_WidgetActor_CartProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

