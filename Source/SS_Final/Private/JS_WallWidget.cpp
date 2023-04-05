// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_WallWidget.h"
#include <UMG/Public/Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include "JS_WallBase.h"
#include "WidgetPointerComponent.h"
#include <UMG/Public/Components/TextBlock.h>
#include "JS_WidgetActor.h"


void UJS_WallWidget::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 가져와서 캐스트해서 넣어준다

	//제품 버튼 배열에 담기
	for (int32 i = 0; i < 4; i++)
	{
		FString ButtonName = FString::Printf(TEXT("Button%d"), i);
		ButtonArr.Add(Cast<UButton>(GetWidgetFromName(*ButtonName)));
	}
	for (int32 i = 0; i < ButtonArr.Num(); i++)
	{
		if (ButtonArr[i] != nullptr)
		{
			// 누르는 버튼 바인딩
			FScriptDelegate PressDelegate;
			PressDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("PressBTN%d"), i)));
			ButtonArr[i]->OnPressed.Add(PressDelegate);

			// 떼는 버튼 바인딩
			FScriptDelegate ReleaseDelegate;
			ReleaseDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("ReleaseBTN%d"), i)));
			ButtonArr[i]->OnReleased.Add(ReleaseDelegate);

			// 닿았을때 버튼 바인딩
			FScriptDelegate HoveredDelegate;
			HoveredDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("OnHoveredBTN%d"), i)));
			ButtonArr[i]->OnHovered.Add(HoveredDelegate);

			// 떨어졌을때 버튼 바인딩
			FScriptDelegate UnhoveredDelegate;
			HoveredDelegate.BindUFunction(this, FName(*FString::Printf(TEXT("UnHoveredBTN%d"), i)));
			ButtonArr[i]->OnUnhovered.Add(HoveredDelegate);

			// 배경 색 초기화
			ButtonArr[i]->SetBackgroundColor(FLinearColor::Gray);
		}
	}
}

void UJS_WallWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);



}


// 기본
void UJS_WallWidget::PressBTN0()
{
	player->selectedWall->ChangeWallMat(0);
	player->smallWidget->SetActive(false);
}
// 대리석
void UJS_WallWidget::PressBTN1()
{
	player->selectedWall->ChangeWallMat(1);
	player->smallWidget->SetActive(false);
}
// 나무
void UJS_WallWidget::PressBTN2()
{
	player->selectedWall->ChangeWallMat(2);
	// 위젯 비활성화
	player->smallWidget->SetActive(false);

}
// 타일
void UJS_WallWidget::PressBTN3()
{
	player->selectedWall->ChangeWallMat(3);
	player->smallWidget->SetActive(false);
}

void UJS_WallWidget::ReleaseBTN0()
{

}

void UJS_WallWidget::ReleaseBTN1()
{

}

void UJS_WallWidget::ReleaseBTN2()
{

}

void UJS_WallWidget::ReleaseBTN3()
{

}

void UJS_WallWidget::OnHoveredBTN0()
{
	// 컬러 바꾸기
	Button0->SetBackgroundColor(FLinearColor::Yellow);
	// 아이콘 이름 바꾸기
	FString str = Button0->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
	/*	HoverdName.Broadcast(this->GetName());*/

}

void UJS_WallWidget::OnHoveredBTN1()
{
	Button1->SetBackgroundColor(FLinearColor::Yellow);

	// 아이콘 이름 바꾸기
	FString str = Button1->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_WallWidget::OnHoveredBTN2()
{
	Button2->SetBackgroundColor(FLinearColor::Yellow);

	FString str = Button2->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_WallWidget::OnHoveredBTN3()
{
	Button3->SetBackgroundColor(FLinearColor::Yellow);

	FString str = Button3->GetChildAt(0)->GetName();
	MatNameTex->SetText(FText::FromString(str));
}

void UJS_WallWidget::UnHoveredBTN0()
{
	Button0->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_WallWidget::UnHoveredBTN1()
{
	Button1->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_WallWidget::UnHoveredBTN2()
{
	Button2->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}

void UJS_WallWidget::UnHoveredBTN3()
{
	Button3->SetBackgroundColor(FLinearColor::Gray);

	MatNameTex->SetText(FText::FromString(TEXT(" ")));
}