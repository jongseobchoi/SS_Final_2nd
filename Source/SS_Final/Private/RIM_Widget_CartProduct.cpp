// Fill out your copyright notice in the Description page of Project Settings.


#include "RIM_Widget_CartProduct.h"
#include <Kismet/GameplayStatics.h>
#include "CharacterBase.h"
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/Button.h>
#include "RIM_CartProduct.h"

//BeginPlay 와 같은 동작
void URIM_Widget_CartProduct::NativeConstruct()
{
	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld()));

	//[버튼 클릭]
	btn_Delete->OnPressed.AddDynamic(this, &URIM_Widget_CartProduct::Bind_btn_Delete);

}

void URIM_Widget_CartProduct::SetProductInfoWidgetInCart(FWidgetProductInfo info)
{
// 	FString str = FString::Printf(TEXT("productName"));
// 	arrProductName.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str 위젯 검색해서 UTextBlock 으로 캐스팅 후 arrProductName 에 넣음 -----> 1개 이니까 어레이로 할 필요 없음
// 
// 	str = FString::Printf(TEXT("productPrice"));
// 	arrProductPrice.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str 위젯 검색해서 UTextBlock 으로 캐스팅 후 arrProductPrice 에 넣음 -----> 1개 이니까 어레이로 할 필요 없음
// 
// 	arrProductName[0]->SetText(FText::FromString(info.name));
// 	arrProductPrice[0]->SetText(FText::AsNumber(info.price));

	//위의 코드 어레이 수정
	FString str = FString::Printf(TEXT("productName"));
	productName = Cast<UTextBlock>(GetWidgetFromName(*str));

	str = FString::Printf(TEXT("productPrice"));
	productPrice = Cast<UTextBlock>(GetWidgetFromName(*str));

	productName->SetText(FText::FromString(info.name));
	productPrice->SetText(FText::AsNumber(info.price));

}

//제품 삭제 버튼
void URIM_Widget_CartProduct::Bind_btn_Delete()
{
	//장바구니에 담겨 있는 제품 삭제
	//ㄴ스폰 되어있는 해당 스테틱메시 삭제
	//ㄴ어레이에서 해당 제품 정보 삭제
	//ㄴ합계에서 빼야해...

// 	1101 삭제 버튼을 클릭했다면
// 	위젯 버튼이 1101 이라는 것을 알아야한다
// 	그래서 삭제 누르면
// 	월드에서 1101 제품 id 를 찾아서 스태틱메시 삭제
// 	어떤 어레이에서 1101 찾아서 삭제
// 	합계에서 뺌


	//TArray<FWidgetProductInfo> id = csvLoader->GetProductInfoInCart(); //id = 제품 정보

}