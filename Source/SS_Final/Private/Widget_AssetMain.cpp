// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_AssetMain.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "WidgetActor_AssetMain.h"
#include "CharacterBase.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Components/Image.h>
#include "CSVLoader.h"
#include <UMG/Public/Components/TextBlock.h>
#include "JS_ProductManager.h"
#include "RIM_CartManager.h"
#include "JS_ProductGhost.h"
#include <HeadMountedDisplayFunctionLibrary.h>

//BeginPlay 와 같은 동작
void UWidget_AssetMain::NativeConstruct()
{

	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld())); //Cast<ACSVLoader>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSVLoader::StaticClass()));

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //캐릭터를 찾아와서 캐스트 후 넣어준다
	cartManager = Cast<ARIM_CartManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARIM_CartManager::StaticClass()));
	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AJS_ProductManager::StaticClass()));

	//[버튼 클릭]
	//메인 카테고리 버튼 연결
	btn_Category01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category01);
	btn_Category02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category02);
	btn_Category03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category03);
	btn_Category04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category04);

	//서브 카테고리 버튼 연결
	btn_SubCategory1->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory1);
	btn_SubCategory2->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory2);
	btn_SubCategory3->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory3);
	btn_SubCategory4->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory4);
	btn_SubCategory5->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory5);
	btn_SubCategory6->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory6);
	btn_SubCategory7->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory7);
	btn_SubCategory8->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory8);

	//제품 버튼 연결
	btn_Product01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product01);
	btn_Product02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product02);
	btn_Product03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product03);
	btn_Product04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product04);

	//닫기 버튼 연결
	btn_Close->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Close);

	//장바구니 담기 버튼 연결
	btn_AddCart01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart01);
	btn_AddCart02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart02);
	btn_AddCart03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart03);
	btn_AddCart04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart04);

	//자세히보기 버튼(링크) 연결
	btn_detail01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_detail01);
		


	//서브 카테고리 위젯(블루프린트UI)의 텍스트박스 연결
	for (int32 i = 0; i < 8; i++) //0 1 2 3 4 5 6 7. 서브 카테고리 텍스트박스 총 8개
	{
		FString str = FString::Printf(TEXT("SubCategory%d"), i + 1); //서브 카테고리. 위젯 블루프린트의 텍스트명

			// 0 + 1 = 1 ---> SubCatetoriy%d ---> SubCategory1
			// 1 + 1 = 2 ---> SubCatetoriy%d ---> SubCategory2
			// 2 + 1 = 3 ---> SubCatetoriy%d ---> SubCategory3
			// 3 + 1 = 4 ---> SubCatetoriy%d ---> SubCategory4
			// 4 + 1 = 5 ---> SubCatetoriy%d ---> SubCategory5
			// 5 + 1 = 6 ---> SubCatetoriy%d ---> SubCategory6
			// 6 + 1 = 7 ---> SubCatetoriy%d ---> SubCategory7
			// 7 + 1 = 8 ---> SubCatetoriy%d ---> SubCategory8

		arrSubCategory.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //GetWidgetFromName 를 통해 str 위젯 검색. 검색 된 위젯을 UTextBlock 으로 캐스팅. arrSubCategory 배열에 추가
	}


	//제품 정보 위젯(블루프린트UI)의 텍스트박스, 이미지 연결
	for (int32 i = 0; i < 4; i++) //0 1 2 3
	{
		FString str = FString::Printf(TEXT("Name%d"), i + 1);
		arrProductName.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str 위젯 검색해서 UTextBlock 으로 캐스팅 후 arrProductName 에 넣음

		str = FString::Printf(TEXT("Price%d"), i + 1); 
		arrProductPrice.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str 위젯 검색해서 UTextBlock 으로 캐스팅 후 arrProductPrice 에 넣음

		str = FString::Printf(TEXT("Thumb%d"), i + 1);
		arrProductThumbnail.Add(Cast<UImage>(GetWidgetFromName(*str))); //str 위젯 검색해서 UImage 로 캐스팅 후 arrProductThumbnail 에 넣음


		// 0 + 1 = 1 ---> Name%d ---> Name1
		// 1 + 1 = 2 ---> Name%d ---> Name2
		// 2 + 1 = 3 ---> Name%d ---> Name3
		// 3 + 1 = 4 ---> Name%d ---> Name4

		// 0 + 1 = 1 ---> Price%d ---> Price1
		// 1 + 1 = 2 ---> Price%d ---> Price2
		// 2 + 1 = 3 ---> Price%d ---> Price3
		// 3 + 1 = 4 ---> Price%d ---> Price4

		// 0 + 1 = 1 ---> Thumb%d ---> Thumb1
		// 1 + 1 = 2 ---> Thumb%d ---> Thumb2
		// 2 + 1 = 3 ---> Thumb%d ---> Thumb3
		// 3 + 1 = 4 ---> Thumb%d ---> Thumb4
	}
		


}


//[버튼 클릭하면 (액터에서) 함수 실행]
//메인 카테고리 버튼 연결 ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Category01()
{
	SetSubCategory(0); //클릭한 카테고리 = 가구
	subCategoryStartIdx = 0; //가구 클릭 했을 때 노출 되는 서브카테고리 시작점

		//가구 0 -> 소파/식탁/의자/침대 = 0123
		//조명 1 -> 스탠드 = 4
		//가전제품 2 -> TV/냉자고 = 56
		//기타 3 -> 7
}

void UWidget_AssetMain::Bind_btn_Category02()
{
	SetSubCategory(1); //클릭한 카테고리 = 조명
	subCategoryStartIdx = 4; //조명 클릭 했을 때 노출 되는 서브카테고리 시작점
}

void UWidget_AssetMain::Bind_btn_Category03()
{
	SetSubCategory(2); //클릭한 카테고리 = 가전제품
	subCategoryStartIdx = 5; //가전제품 클릭 했을 때 노출 되는 서브카테고리 시작점
}

void UWidget_AssetMain::Bind_btn_Category04()
{
	SetSubCategory(3); //클릭한 카테고리 = 기타
	subCategoryStartIdx = 7; //기타 클릭 했을 때 노출 되는 서브카테고리 시작점
}


//서브 카테고리 버튼 연결 ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_SubCategory1()
{
	SetProductInfo(subCategoryStartIdx); //★★★★★왜 이렇게 하는건지 생각 안나... ㅠ ㅠ ㅠ ㅠ
}

void UWidget_AssetMain::Bind_btn_SubCategory2()
{
	SetProductInfo(subCategoryStartIdx + 1); //★★★★★왜 이렇게 하는건지 생각 안나... ㅠ ㅠ ㅠ ㅠ
}

void UWidget_AssetMain::Bind_btn_SubCategory3()
{
	SetProductInfo(subCategoryStartIdx + 2); //★★★★★왜 이렇게 하는건지 생각 안나... ㅠ ㅠ ㅠ ㅠ
}

void UWidget_AssetMain::Bind_btn_SubCategory4()
{
	SetProductInfo(subCategoryStartIdx + 3); //★★★★★왜 이렇게 하는건지 생각 안나... ㅠ ㅠ ㅠ ㅠ
}

void UWidget_AssetMain::Bind_btn_SubCategory5()
{

}

void UWidget_AssetMain::Bind_btn_SubCategory6()
{
	
}

void UWidget_AssetMain::Bind_btn_SubCategory7()
{
	
}

void UWidget_AssetMain::Bind_btn_SubCategory8()
{
	
}


//제품 버튼 연결 ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Product01()
{
	//테스트
	player->SetWidgetActive(1,false);
  	selectedProductIdx = subCategoryStartIdx * 4; //Bind_btn_cart1 자리 제품
	SelectProduct(selectedProductIdx);
	player->productGhost->SetInit(selectedProductIdx);
	player->ChangeState(EPlayerState::SelectedProduct);
//  		
//  		// n = 선택(클릭)한 제품의 엑셀 열 번호 
//  		//0 * 4 = 엑셀 열에서 0번째 ---> 소파1 ---> n = 0
//  		//1 * 4 = 엑셀 열에서 4번째 ---> 식탁1 ---> n = 4
//  		//2 * 4 = 엑셀 열에서 8번째---> 의자1 ---> n = 8
//  		//3 * 4 = 엑셀 열에서 12번째---> 침대1 ---> n = 12
//  		//4 * 4 = 엑셀 열에서 16번째---> 스탠드1 ---> n = 16
//  		//5 * 4 = 엑셀 열에서 20번째---> TV1 ---> n = 20
//  		//6 * 4 = 엑셀 열에서 24번째---> 냉장고1 ---> n = 24
//  		//7 * 4 = 엑셀 열에서 28번째---> 화분1 ---> n = 28
//  



}

void UWidget_AssetMain::Bind_btn_Product02()
{
	//테스트
	player->SetWidgetActive(1,false);

	selectedProductIdx = subCategoryStartIdx * 4+1;
	SelectProduct(selectedProductIdx);
}

void UWidget_AssetMain::Bind_btn_Product03()
{
	selectedProductIdx = subCategoryStartIdx * 4+2;
	SelectProduct(selectedProductIdx);
}

void UWidget_AssetMain::Bind_btn_Product04()
{
	selectedProductIdx = subCategoryStartIdx * 4+3;
	SelectProduct(selectedProductIdx);
}


//[위젯 닫기] ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Close()
{	
	//가구 위젯이 안 보인다. 콜리전을 노콜리전으로 한다
	player->SetWidgetActive(1,false);

	//왼손 메뉴 위젯이 보인다. 콜리전을 UI 로 한다
	player->SetWidgetActive(0, true);

	//테스트(선생님). 위젯 닫을 때 CreateProductInCart 실행. 클릭한 제품 스폰
	//csvLoader->CreateProductInCart();
}


//[장바구니에 제품 추가하기] ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_AddCart01() 
{
	int n = subCategoryStartIdx * 4; //Bind_btn_cart1 자리 제품
		
		// n = 선택(클릭)한 제품의 엑셀 열 번호 
		//0 * 4 = 엑셀 열에서 0번째 ---> 소파1 ---> n = 0
		//1 * 4 = 엑셀 열에서 4번째 ---> 식탁1 ---> n = 4
		//2 * 4 = 엑셀 열에서 8번째---> 의자1 ---> n = 8
		//3 * 4 = 엑셀 열에서 12번째---> 침대1 ---> n = 12
		//4 * 4 = 엑셀 열에서 16번째---> 스탠드1 ---> n = 16
		//5 * 4 = 엑셀 열에서 20번째---> TV1 ---> n = 20
		//6 * 4 = 엑셀 열에서 24번째---> 냉장고1 ---> n = 24
		//7 * 4 = 엑셀 열에서 28번째---> 화분1 ---> n = 28
	
	csvLoader->AddCart(n); //AddCart(0) ---> 엑셀 열0 제품의 id, 제품 정보를 csvLoader 의 AddCart 에서 가져온다.
}

void UWidget_AssetMain::Bind_btn_AddCart02()
{
	int n = (subCategoryStartIdx * 4) + 1; //Bind_btn_cart2 자리 제품

		// n = 선택(클릭)한 제품의 엑셀 열 번호 
		//(0 * 4) + 1 = 엑셀 열에서 0번째 ---> 소파1 ---> n = 1
		//(1 * 4) + 1 = 엑셀 열에서 4번째 ---> 식탁1 ---> n = 5
		//(2 * 4) + 1 = 엑셀 열에서 8번째---> 의자1 ---> n = 9
		//(3 * 4) + 1 = 엑셀 열에서 12번째---> 침대1 ---> n = 13
		//(4 * 4) + 1 = 엑셀 열에서 16번째---> 스탠드1 ---> n = 17
		//(5 * 4) + 1 = 엑셀 열에서 20번째---> TV1 ---> n = 22
		//(6 * 4) + 1 = 엑셀 열에서 24번째---> 냉장고1 ---> n = 25
		//(7 * 4) + 1 = 엑셀 열에서 28번째---> 화분1 ---> n = 29

	csvLoader->AddCart(n);
}

void UWidget_AssetMain::Bind_btn_AddCart03()
{
	int n = (subCategoryStartIdx * 4) + 2; //Bind_btn_cart3 자리 제품

		// n = 선택(클릭)한 제품의 엑셀 열 번호 
		//(0 * 4) + 2 = 엑셀 열에서 0번째 ---> 소파1 ---> n = 2

	csvLoader->AddCart(n);
}

void UWidget_AssetMain::Bind_btn_AddCart04()
{
	int n = (subCategoryStartIdx * 4) + 3; //Bind_btn_cart4 자리 제품

		// n = 선택(클릭)한 제품의 엑셀 열 번호 
		//(0 * 4) + 3 = 엑셀 열에서 0번째 ---> 소파1 ---> n = 3

	csvLoader->AddCart(n);
}


//[장바구니에 제품 추가하기] ----------------------------------------------------------------------------------------------------------
void  UWidget_AssetMain::Bind_btn_detail01()
{
	UE_LOG(LogTemp, Warning, TEXT("Click -----> AssetMain ----->detail01"));

				
}


//-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------


//[서브 카테고리 노출하는 함수]
void UWidget_AssetMain::SetSubCategory(int32 category) //category = 매개변수. 가구/조명/가전제품/기타 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음
{
	//csvLoader 에서 GetCategoryItem 함수 호출해서 items 배열에 담음? 서브 카테고리 데이터 담음 arr 배열 가져 옴? //★★★ 왜 이렇게 해야 함?
	TArray<FString> items = csvLoader->GetCategoryItem(category);

		// start = category 매개변수 * 4
		// 0 * 4 = 0 ---> 0 = 소파
		// 1 * 4 = 4 ---> 4 = 스탠드 
		// 2 * 4 = 8 ---> 8 = TV
		// 3 * 4 = 12 ---> 12 = 화분

	for (int32 i = 0; i < arrSubCategory.Num(); i++) //0 1 2 3 4 5 6 7. 총 8개. arrSubCategory(위젯 블루프린트 UTextBlock SubCategory1 2 3 4 5 6 7 8 담은 배열)
	{
		arrSubCategory[i]->SetText(FText::FromString("")); //★★★★★ FromString("") 왜 사용? 빈 문자열로 설정?
		
		//★★★★★ 아래 if 문 전체 이해 안 감. i 가 0 이면 SubCategory 는 SubCategory1 인 것는 이해했는데, items[i] 는 어떻게 매칭 되는 것인지 노이해
		if (i < items.Num())
		{
			arrSubCategory[i]->SetText(FText::FromString(items[i])); 
		}
	}
}


//[제품 정보 노출하는 함수]
void UWidget_AssetMain::SetProductInfo(int32 subCategory) //subcategory = 매개변수. 소파/식탁/스탠드/TV ... 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음
{
	TArray<FWidgetProductInfo> items = csvLoader->GetProductInfo(subCategory);

		// 0 * 4 = 0 ---> 0 = 소파1
		// 1 * 4 = 4 ---> 4 = 식탁1
		// 2 * 4 = 8 ---> 8 = 의자1
		// 3 * 4 = 12 ---> 12 = 침대1
		// 4 * 4 = 16 ---> 16 = 스탠드1
		// 5 * 4 = 20 ---> 20 = TV1
		// 6 * 4 = 24 ---> 24 = 냉장고1
		// 7 * 4 = 28 ---> 28 = 화분1

	//★★★★★ 아래 for 문 전체 이해 안 감. i 가 0 이면 arrProductName 는 Name1 인 거는 이해했는데, items[0].name 은 어떻게 매칭 되는 것인지 노이해
	for (int32 i = 0; i < items.Num(); i++)
	{
		arrProductName[i]->SetText(FText::FromString(items[i].name));
		arrProductPrice[i]->SetText(FText::AsNumber(items[i].price)); //items[i].price 에서 가격 정보를 가져와서 숫자로 전달, AsNumber 로 문자열로 변환
		arrProductThumbnail[i]->SetBrushFromTexture(items[i].thumbnail);
	}
}

void UWidget_AssetMain::SelectProduct(int32 value)
{
	productManager->SelectedProduct(value);
	player->productGhost->SetInit(value);
	player->currState = EPlayerState::SelectedProduct;
}


