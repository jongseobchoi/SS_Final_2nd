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
	
	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� �����ͼ� ĳ��Ʈ�ؼ� �־��ش�

	//��ǰ ��ư �迭�� ���
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

	// ��� �� �ʱ�ȭ


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
	
	// ���õ� ��ǰ �̸� ����
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

		// ����Ʈ off �Լ� ����� ����
		selectedLight->SwitchLights();
	
	}
	break;
	case 2:
	{
		// ���� ��Ȱ��ȭ
		player->smallWidget->SetActive(false);
		// ���õ� ��ǰ ����
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