// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Order.h"
#include <UMG/Public/Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include "CSVLoader.h"

//BeginPlay 와 같은 동작
void URIM_Widget_Order::NativeConstruct()
{
	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld()));

	SetTotalPriceWidgetInCart();
}

void URIM_Widget_Order::SetTotalPriceWidgetInCart()
{
	TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart();

	for (int32 i = 0; i < id.Num(); i++)
	{
		total += id[i].price; //제품 가격 더하기 계산

	}

	FString str = FString::Printf(TEXT("TotalPrice"));
	totalPrice = Cast<UTextBlock>(GetWidgetFromName(*str)); //str 위젯 검색해서 UTextBlock 으로 캐스팅 후 totalPrice 에 넣음
	totalPrice->SetText(FText::AsNumber(total));

}