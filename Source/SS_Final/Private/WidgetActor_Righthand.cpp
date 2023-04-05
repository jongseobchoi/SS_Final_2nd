// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor_Righthand.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Widget_Righthand.h"
#include "CharacterBase.h"

// Sets default values
AWidgetActor_Righthand::AWidgetActor_Righthand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���� �߰�
	widget_Righthand = CreateDefaultSubobject<UWidgetComponent>(TEXT("Righthand Widget Comp"));
	widget_Righthand->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AWidgetActor_Righthand::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� �����ͼ� ĳ��Ʈ�ؼ� �־��ش�

	//������ �Լ��� ������ ���� �� �� �ְ� ���ִ� �ڵ�
	if (widget_Righthand != nullptr) //���Ϳ� ������ ������
	{
		UWidget_Righthand* righthandWidget = Cast<UWidget_Righthand>(widget_Righthand->GetWidget());

		if (righthandWidget != nullptr)
		{
			righthandWidget->widgetActor_Righthand = this;
		}
	}
	
}

// Called every frame
void AWidgetActor_Righthand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//[��ư Ŭ���ϸ� ���Ϳ��� �Լ� ����]
void AWidgetActor_Righthand::Righthand01()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand01"));

	/* --------------------------------------------------------------------------------> �������� ĳ���ͷ� �ű�
	//�޼� ������ ������
	player->compLefthandWidget->SetVisibility(false);
	//���� ���� ������ ������/���δ�
	player->compAssetMainWidget->SetVisibility(true);
	*/
}

void AWidgetActor_Righthand::Righthand02()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand02"));
}

void AWidgetActor_Righthand::Righthand03()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand03"));
}

void AWidgetActor_Righthand::Righthand04()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand04"));
}

void AWidgetActor_Righthand::Righthand05()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand05"));
}

void AWidgetActor_Righthand::Righthand06()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand06"));
}

void AWidgetActor_Righthand::Righthand07()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand07"));
}

void AWidgetActor_Righthand::Righthand08()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand08"));
}