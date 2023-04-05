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

	//위젯 추가
	widget_Righthand = CreateDefaultSubobject<UWidgetComponent>(TEXT("Righthand Widget Comp"));
	widget_Righthand->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AWidgetActor_Righthand::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 가져와서 캐스트해서 넣어준다

	//액터의 함수를 위젯이 실행 할 수 있게 해주는 코드
	if (widget_Righthand != nullptr) //액터에 위젯이 있으면
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

//[버튼 클릭하면 액터에서 함수 실행]
void AWidgetActor_Righthand::Righthand01()
{
	UE_LOG(LogTemp, Warning, TEXT("Righthand01"));

	/* --------------------------------------------------------------------------------> 오류나서 캐릭터로 옮김
	//왼손 위젯이 닫힌다
	player->compLefthandWidget->SetVisibility(false);
	//가구 메인 위젯이 열린다/보인다
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