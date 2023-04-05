// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_ProductWidget.h"
#include <UMG/Public/Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include "ProductBase.h"
#include "WidgetPointerComponent.h"
#include <UMG/Public/Components/TextBlock.h>
#include "JS_WidgetActor.h"
#include "LightBase.h"

void UJS_ProductWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 가져와서 캐스트해서 넣어준다

	//제품 버튼 배열에 담기
	for (int32 i = 0; i < 4; i++)
	{
		FString ButtonName = FString::Printf(TEXT("Button%d"),i);
		ButtonArr.Add(Cast<UButton>(GetWidgetFromName(*ButtonName)));
		ButtonArr[i]->SetBackgroundColor(FLinearColor::Gray);
		ButtonArr[i]->SetBackgroundColor(FLinearColor::Gray);
		
	}

	for (int32 i = 0; i < ButtonArr.Num(); i++)
	{
		USelectedButton* selectedBtn = NewObject<USelectedButton>();
		selectedBtn->Init(i, this);
		ButtonArr[i]->OnPressed.AddDynamic(selectedBtn, &USelectedButton::OnPressed);
		ButtonArr[i]->OnReleased.AddDynamic(selectedBtn, &USelectedButton::OnReleased);
		ButtonArr[i]->OnHovered.AddDynamic(selectedBtn, &USelectedButton::OnHovered);
		ButtonArr[i]->OnUnhovered.AddDynamic(selectedBtn, &USelectedButton::UnHovered);


	}

	// 배경 색 초기화


}

void UJS_ProductWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	


	if (player->selectedProduct->kindProduct == 0)
	{
		Button1->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Button1->SetVisibility(ESlateVisibility::Visible);
		selectedLight = Cast<ALightBase>(player->selectedProduct);
	}
	
	// 선택된 제품 이름 띄우기
	if (player->selectedProduct != nullptr)
	{
		ProductNameTex->SetText(FText::FromString(player->selectedProduct->info.name));
	}
}


void UJS_ProductWidget::PressBTN(int32 btnIndex)
{
	switch (btnIndex)
	{
	case 0:
	{
		player->selectedProduct->RotateProduct();
		selectedLight->RotateProduct();
	}
	break;
	case 1:
	{

		// 라이트 off 함수 만들고 실행
		selectedLight->SwitchLights();
	
	}
	break;
	case 2:
	{
		// 위젯 비활성화
		player->smallWidget->SetActive(false);
		// 선택된 제품 삭제
		player->selectedProduct->Destroy();
		selectedLight->Destroy();
	}
	break;
	case 3:
	break;
	}

	UE_LOG(LogTemp, Error, TEXT("PressBTN - %d"), btnIndex);
}
void UJS_ProductWidget::ReleaseBTN(int32 btnIndex)
{
	UE_LOG(LogTemp, Error, TEXT("ReleaseBTN - %d"), btnIndex);
}
void UJS_ProductWidget::OnHoveredBTN(int32 btnIndex)
{
	ButtonArr[btnIndex]->SetBackgroundColor(FLinearColor::Yellow);

	FString str = ButtonArr[btnIndex]->GetChildAt(0)->GetName();
	IconNameTex->SetText(FText::FromString(str));
	UE_LOG(LogTemp, Error, TEXT("OnHoveredBTN - %d"), btnIndex);
}
void UJS_ProductWidget::UnHoveredBTN(int32 btnIndex)
{
/*	UE_LOG(LogTemp, Error, TEXT("UnHoveredBTN - %d"), btnIndex);*/
	ButtonArr[btnIndex]->SetBackgroundColor(FLinearColor::Gray);

	IconNameTex->SetText(FText::FromString(TEXT(" ")));
}