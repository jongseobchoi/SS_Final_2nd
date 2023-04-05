// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_FloorWidget.h"
#include <UMG/Public/Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include "JS_FloorBase.h"
#include "WidgetPointerComponent.h"
#include <UMG/Public/Components/TextBlock.h>
#include "JS_WidgetActor.h"

void UJS_FloorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� �����ͼ� ĳ��Ʈ�ؼ� �־��ش�

	//��ǰ ��ư �迭�� ���
	for (int32 i = 0; i < 4; i++)
	{
		FString ButtonName = FString::Printf(TEXT("Button%d"), i);
		ButtonArr.Add(Cast<UButton>(GetWidgetFromName(*ButtonName)));
	}
	for (int32 i = 0; i < ButtonArr.Num(); i++)
	{
// 		if (ButtonArr[i] != nullptr)
// 		{
			// ������ ��ư ���ε�
			FScriptDelegate PressDelegate;
			PressDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("PressBTN%d"), i)));
			ButtonArr[i]->OnPressed.Add(PressDelegate);

			// ���� ��ư ���ε�
			FScriptDelegate ReleaseDelegate;
			ReleaseDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("ReleaseBTN%d"), i)));
			ButtonArr[i]->OnReleased.Add(ReleaseDelegate);

			// ������� ��ư ���ε�
			FScriptDelegate HoveredDelegate;
			HoveredDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("OnHoveredBTN%d"), i)));
			ButtonArr[i]->OnHovered.Add(HoveredDelegate);

			// ���������� ��ư ���ε�
			FScriptDelegate UnhoveredDelegate;
			HoveredDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("UnHoveredBTN%d"), i)));
			ButtonArr[i]->OnUnhovered.Add(HoveredDelegate);

			// ��� �� �ʱ�ȭ
			ButtonArr[i]->SetBackgroundColor(FLinearColor::Gray);
/*		}*/
	}
	UE_LOG(LogTemp, Warning, TEXT("FloorWidget Binded!"))
}

void UJS_FloorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

 }


// �⺻
void UJS_FloorWidget::PressBTN0()
{
	player->selectedFloor->ChangeFloorMat(0);
	player->smallWidget->SetActive(false);
}
// �븮��
void UJS_FloorWidget::PressBTN1()
{
	player->selectedFloor->ChangeFloorMat(1);
	player->smallWidget->SetActive(false);
}
// ����
void UJS_FloorWidget::PressBTN2()
{
	player->selectedFloor->ChangeFloorMat(2);
	// ���� ��Ȱ��ȭ
	player->smallWidget->SetActive(false);

}
// Ÿ��
void UJS_FloorWidget::PressBTN3()
{
	player->selectedFloor->ChangeFloorMat(3);
	player->smallWidget->SetActive(false);
}

void UJS_FloorWidget::ReleaseBTN0()
{

}

void UJS_FloorWidget::ReleaseBTN1()
{

}

void UJS_FloorWidget::ReleaseBTN2()
{

}

void UJS_FloorWidget::ReleaseBTN3()
{

}

void UJS_FloorWidget::OnHoveredBTN0()
{

	UE_LOG(LogTemp, Warning, TEXT("Onhovered"))
	// �÷� �ٲٱ�
	Button0->SetBackgroundColor(FLinearColor::Yellow);
	// ������ �̸� �ٲٱ�
	FString str = Button0->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));

}

void UJS_FloorWidget::OnHoveredBTN1()
{
	Button1->SetBackgroundColor(FLinearColor::Yellow);

	// ������ �̸� �ٲٱ�
	FString str = Button1->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_FloorWidget::OnHoveredBTN2()
{
	Button2->SetBackgroundColor(FLinearColor::Yellow);

	FString str = Button2->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_FloorWidget::OnHoveredBTN3()
{
	Button3->SetBackgroundColor(FLinearColor::Yellow);

	FString str = Button3->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_FloorWidget::UnHoveredBTN0()
{
	Button0->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_FloorWidget::UnHoveredBTN1()
{
	Button1->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_FloorWidget::UnHoveredBTN2()
{
	Button2->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_FloorWidget::UnHoveredBTN3()
{
	Button3->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}
