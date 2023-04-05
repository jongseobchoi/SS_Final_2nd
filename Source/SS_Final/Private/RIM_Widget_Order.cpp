// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_Order.h"
#include <UMG/Public/Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include "CSVLoader.h"

//BeginPlay �� ���� ����
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
		total += id[i].price; //��ǰ ���� ���ϱ� ���

	}

	FString str = FString::Printf(TEXT("TotalPrice"));
	totalPrice = Cast<UTextBlock>(GetWidgetFromName(*str)); //str ���� �˻��ؼ� UTextBlock ���� ĳ���� �� totalPrice �� ����
	totalPrice->SetText(FText::AsNumber(total));

}