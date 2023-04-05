// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_CartProduct.h"
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/Button.h>
#include "RIM_CartProduct.h"

//BeginPlay �� ���� ����
void URIM_Widget_CartProduct::NativeConstruct()
{
	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld()));

	//[��ư Ŭ��]
	btn_Delete->OnPressed.AddDynamic(this, &URIM_Widget_CartProduct::Bind_btn_Delete);

}

void URIM_Widget_CartProduct::SetProductInfoWidgetInCart(FWidgetProductInfo info)
{
// 	FString str = FString::Printf(TEXT("productName"));
// 	arrProductName.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str ���� �˻��ؼ� UTextBlock ���� ĳ���� �� arrProductName �� ���� -----> 1�� �̴ϱ� ��̷� �� �ʿ� ����
// 
// 	str = FString::Printf(TEXT("productPrice"));
// 	arrProductPrice.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str ���� �˻��ؼ� UTextBlock ���� ĳ���� �� arrProductPrice �� ���� -----> 1�� �̴ϱ� ��̷� �� �ʿ� ����
// 
// 	arrProductName[0]->SetText(FText::FromString(info.name));
// 	arrProductPrice[0]->SetText(FText::AsNumber(info.price));

	//���� �ڵ� ��� ����
	FString str = FString::Printf(TEXT("productName"));
	productName = Cast<UTextBlock>(GetWidgetFromName(*str));

	str = FString::Printf(TEXT("productPrice"));
	productPrice = Cast<UTextBlock>(GetWidgetFromName(*str));

	productName->SetText(FText::FromString(info.name));
	productPrice->SetText(FText::AsNumber(info.price));

}

//��ǰ ���� ��ư
void URIM_Widget_CartProduct::Bind_btn_Delete()
{
	//��ٱ��Ͽ� ��� �ִ� ��ǰ ����
	//������ �Ǿ��ִ� �ش� ����ƽ�޽� ����
	//����̿��� �ش� ��ǰ ���� ����
	//���հ迡�� ������...

// 	1101 ���� ��ư�� Ŭ���ߴٸ�
// 	���� ��ư�� 1101 �̶�� ���� �˾ƾ��Ѵ�
// 	�׷��� ���� ������
// 	���忡�� 1101 ��ǰ id �� ã�Ƽ� ����ƽ�޽� ����
// 	� ��̿��� 1101 ã�Ƽ� ����
// 	�հ迡�� ��


	//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //id = ��ǰ ����

}