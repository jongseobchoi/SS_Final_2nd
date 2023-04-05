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

//BeginPlay �� ���� ����
void UWidget_AssetMain::NativeConstruct()
{

	csvLoader = Cast<UCSVLoader>(UGameplayStatics::GetGameInstance(GetWorld())); //Cast<ACSVLoader>(UGameplayStatics::GetActorOfClass(GetWorld(), ACSVLoader::StaticClass()));

	player = Cast<ACharacterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ACharacterBase::StaticClass())); //ĳ���͸� ã�ƿͼ� ĳ��Ʈ �� �־��ش�
	cartManager = Cast<ARIM_CartManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARIM_CartManager::StaticClass()));
	productManager = Cast<AJS_ProductManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AJS_ProductManager::StaticClass()));

	//[��ư Ŭ��]
	//���� ī�װ� ��ư ����
	btn_Category01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category01);
	btn_Category02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category02);
	btn_Category03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category03);
	btn_Category04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Category04);

	//���� ī�װ� ��ư ����
	btn_SubCategory1->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory1);
	btn_SubCategory2->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory2);
	btn_SubCategory3->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory3);
	btn_SubCategory4->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory4);
	btn_SubCategory5->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory5);
	btn_SubCategory6->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory6);
	btn_SubCategory7->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory7);
	btn_SubCategory8->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_SubCategory8);

	//��ǰ ��ư ����
	btn_Product01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product01);
	btn_Product02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product02);
	btn_Product03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product03);
	btn_Product04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Product04);

	//�ݱ� ��ư ����
	btn_Close->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_Close);

	//��ٱ��� ��� ��ư ����
	btn_AddCart01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart01);
	btn_AddCart02->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart02);
	btn_AddCart03->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart03);
	btn_AddCart04->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_AddCart04);

	//�ڼ������� ��ư(��ũ) ����
	btn_detail01->OnPressed.AddDynamic(this, &UWidget_AssetMain::Bind_btn_detail01);
		


	//���� ī�װ� ����(�������ƮUI)�� �ؽ�Ʈ�ڽ� ����
	for (int32 i = 0; i < 8; i++) //0 1 2 3 4 5 6 7. ���� ī�װ� �ؽ�Ʈ�ڽ� �� 8��
	{
		FString str = FString::Printf(TEXT("SubCategory%d"), i + 1); //���� ī�װ�. ���� �������Ʈ�� �ؽ�Ʈ��

			// 0 + 1 = 1 ---> SubCatetoriy%d ---> SubCategory1
			// 1 + 1 = 2 ---> SubCatetoriy%d ---> SubCategory2
			// 2 + 1 = 3 ---> SubCatetoriy%d ---> SubCategory3
			// 3 + 1 = 4 ---> SubCatetoriy%d ---> SubCategory4
			// 4 + 1 = 5 ---> SubCatetoriy%d ---> SubCategory5
			// 5 + 1 = 6 ---> SubCatetoriy%d ---> SubCategory6
			// 6 + 1 = 7 ---> SubCatetoriy%d ---> SubCategory7
			// 7 + 1 = 8 ---> SubCatetoriy%d ---> SubCategory8

		arrSubCategory.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //GetWidgetFromName �� ���� str ���� �˻�. �˻� �� ������ UTextBlock ���� ĳ����. arrSubCategory �迭�� �߰�
	}


	//��ǰ ���� ����(�������ƮUI)�� �ؽ�Ʈ�ڽ�, �̹��� ����
	for (int32 i = 0; i < 4; i++) //0 1 2 3
	{
		FString str = FString::Printf(TEXT("Name%d"), i + 1);
		arrProductName.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str ���� �˻��ؼ� UTextBlock ���� ĳ���� �� arrProductName �� ����

		str = FString::Printf(TEXT("Price%d"), i + 1); 
		arrProductPrice.Add(Cast<UTextBlock>(GetWidgetFromName(*str))); //str ���� �˻��ؼ� UTextBlock ���� ĳ���� �� arrProductPrice �� ����

		str = FString::Printf(TEXT("Thumb%d"), i + 1);
		arrProductThumbnail.Add(Cast<UImage>(GetWidgetFromName(*str))); //str ���� �˻��ؼ� UImage �� ĳ���� �� arrProductThumbnail �� ����


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


//[��ư Ŭ���ϸ� (���Ϳ���) �Լ� ����]
//���� ī�װ� ��ư ���� ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Category01()
{
	SetSubCategory(0); //Ŭ���� ī�װ� = ����
	subCategoryStartIdx = 0; //���� Ŭ�� ���� �� ���� �Ǵ� ����ī�װ� ������

		//���� 0 -> ����/��Ź/����/ħ�� = 0123
		//���� 1 -> ���ĵ� = 4
		//������ǰ 2 -> TV/���ڰ� = 56
		//��Ÿ 3 -> 7
}

void UWidget_AssetMain::Bind_btn_Category02()
{
	SetSubCategory(1); //Ŭ���� ī�װ� = ����
	subCategoryStartIdx = 4; //���� Ŭ�� ���� �� ���� �Ǵ� ����ī�װ� ������
}

void UWidget_AssetMain::Bind_btn_Category03()
{
	SetSubCategory(2); //Ŭ���� ī�װ� = ������ǰ
	subCategoryStartIdx = 5; //������ǰ Ŭ�� ���� �� ���� �Ǵ� ����ī�װ� ������
}

void UWidget_AssetMain::Bind_btn_Category04()
{
	SetSubCategory(3); //Ŭ���� ī�װ� = ��Ÿ
	subCategoryStartIdx = 7; //��Ÿ Ŭ�� ���� �� ���� �Ǵ� ����ī�װ� ������
}


//���� ī�װ� ��ư ���� ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_SubCategory1()
{
	SetProductInfo(subCategoryStartIdx); //�ڡڡڡڡڿ� �̷��� �ϴ°��� ���� �ȳ�... �� �� �� ��
}

void UWidget_AssetMain::Bind_btn_SubCategory2()
{
	SetProductInfo(subCategoryStartIdx + 1); //�ڡڡڡڡڿ� �̷��� �ϴ°��� ���� �ȳ�... �� �� �� ��
}

void UWidget_AssetMain::Bind_btn_SubCategory3()
{
	SetProductInfo(subCategoryStartIdx + 2); //�ڡڡڡڡڿ� �̷��� �ϴ°��� ���� �ȳ�... �� �� �� ��
}

void UWidget_AssetMain::Bind_btn_SubCategory4()
{
	SetProductInfo(subCategoryStartIdx + 3); //�ڡڡڡڡڿ� �̷��� �ϴ°��� ���� �ȳ�... �� �� �� ��
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


//��ǰ ��ư ���� ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Product01()
{
	//�׽�Ʈ
	player->SetWidgetActive(1,false);
  	selectedProductIdx = subCategoryStartIdx * 4; //Bind_btn_cart1 �ڸ� ��ǰ
	SelectProduct(selectedProductIdx);
	player->productGhost->SetInit(selectedProductIdx);
	player->ChangeState(EPlayerState::SelectedProduct);
//  		
//  		// n = ����(Ŭ��)�� ��ǰ�� ���� �� ��ȣ 
//  		//0 * 4 = ���� ������ 0��° ---> ����1 ---> n = 0
//  		//1 * 4 = ���� ������ 4��° ---> ��Ź1 ---> n = 4
//  		//2 * 4 = ���� ������ 8��°---> ����1 ---> n = 8
//  		//3 * 4 = ���� ������ 12��°---> ħ��1 ---> n = 12
//  		//4 * 4 = ���� ������ 16��°---> ���ĵ�1 ---> n = 16
//  		//5 * 4 = ���� ������ 20��°---> TV1 ---> n = 20
//  		//6 * 4 = ���� ������ 24��°---> �����1 ---> n = 24
//  		//7 * 4 = ���� ������ 28��°---> ȭ��1 ---> n = 28
//  



}

void UWidget_AssetMain::Bind_btn_Product02()
{
	//�׽�Ʈ
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


//[���� �ݱ�] ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_Close()
{	
	//���� ������ �� ���δ�. �ݸ����� ���ݸ������� �Ѵ�
	player->SetWidgetActive(1,false);

	//�޼� �޴� ������ ���δ�. �ݸ����� UI �� �Ѵ�
	player->SetWidgetActive(0, true);

	//�׽�Ʈ(������). ���� ���� �� CreateProductInCart ����. Ŭ���� ��ǰ ����
	//csvLoader->CreateProductInCart();
}


//[��ٱ��Ͽ� ��ǰ �߰��ϱ�] ----------------------------------------------------------------------------------------------------------
void UWidget_AssetMain::Bind_btn_AddCart01() 
{
	int n = subCategoryStartIdx * 4; //Bind_btn_cart1 �ڸ� ��ǰ
		
		// n = ����(Ŭ��)�� ��ǰ�� ���� �� ��ȣ 
		//0 * 4 = ���� ������ 0��° ---> ����1 ---> n = 0
		//1 * 4 = ���� ������ 4��° ---> ��Ź1 ---> n = 4
		//2 * 4 = ���� ������ 8��°---> ����1 ---> n = 8
		//3 * 4 = ���� ������ 12��°---> ħ��1 ---> n = 12
		//4 * 4 = ���� ������ 16��°---> ���ĵ�1 ---> n = 16
		//5 * 4 = ���� ������ 20��°---> TV1 ---> n = 20
		//6 * 4 = ���� ������ 24��°---> �����1 ---> n = 24
		//7 * 4 = ���� ������ 28��°---> ȭ��1 ---> n = 28
	
	csvLoader->AddCart(n); //AddCart(0) ---> ���� ��0 ��ǰ�� id, ��ǰ ������ csvLoader �� AddCart ���� �����´�.
}

void UWidget_AssetMain::Bind_btn_AddCart02()
{
	int n = (subCategoryStartIdx * 4) + 1; //Bind_btn_cart2 �ڸ� ��ǰ

		// n = ����(Ŭ��)�� ��ǰ�� ���� �� ��ȣ 
		//(0 * 4) + 1 = ���� ������ 0��° ---> ����1 ---> n = 1
		//(1 * 4) + 1 = ���� ������ 4��° ---> ��Ź1 ---> n = 5
		//(2 * 4) + 1 = ���� ������ 8��°---> ����1 ---> n = 9
		//(3 * 4) + 1 = ���� ������ 12��°---> ħ��1 ---> n = 13
		//(4 * 4) + 1 = ���� ������ 16��°---> ���ĵ�1 ---> n = 17
		//(5 * 4) + 1 = ���� ������ 20��°---> TV1 ---> n = 22
		//(6 * 4) + 1 = ���� ������ 24��°---> �����1 ---> n = 25
		//(7 * 4) + 1 = ���� ������ 28��°---> ȭ��1 ---> n = 29

	csvLoader->AddCart(n);
}

void UWidget_AssetMain::Bind_btn_AddCart03()
{
	int n = (subCategoryStartIdx * 4) + 2; //Bind_btn_cart3 �ڸ� ��ǰ

		// n = ����(Ŭ��)�� ��ǰ�� ���� �� ��ȣ 
		//(0 * 4) + 2 = ���� ������ 0��° ---> ����1 ---> n = 2

	csvLoader->AddCart(n);
}

void UWidget_AssetMain::Bind_btn_AddCart04()
{
	int n = (subCategoryStartIdx * 4) + 3; //Bind_btn_cart4 �ڸ� ��ǰ

		// n = ����(Ŭ��)�� ��ǰ�� ���� �� ��ȣ 
		//(0 * 4) + 3 = ���� ������ 0��° ---> ����1 ---> n = 3

	csvLoader->AddCart(n);
}


//[��ٱ��Ͽ� ��ǰ �߰��ϱ�] ----------------------------------------------------------------------------------------------------------
void  UWidget_AssetMain::Bind_btn_detail01()
{
	UE_LOG(LogTemp, Warning, TEXT("Click -----> AssetMain ----->detail01"));

				
}


//-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------


//[���� ī�װ� �����ϴ� �Լ�]
void UWidget_AssetMain::SetSubCategory(int32 category) //category = �Ű�����. ����/����/������ǰ/��Ÿ �߿� ������ Ŭ���� ������ �𸣴ϱ� �㱸�� ����
{
	//csvLoader ���� GetCategoryItem �Լ� ȣ���ؼ� items �迭�� ����? ���� ī�װ� ������ ���� arr �迭 ���� ��? //�ڡڡ� �� �̷��� �ؾ� ��?
	TArray<FString> items = csvLoader->GetCategoryItem(category);

		// start = category �Ű����� * 4
		// 0 * 4 = 0 ---> 0 = ����
		// 1 * 4 = 4 ---> 4 = ���ĵ� 
		// 2 * 4 = 8 ---> 8 = TV
		// 3 * 4 = 12 ---> 12 = ȭ��

	for (int32 i = 0; i < arrSubCategory.Num(); i++) //0 1 2 3 4 5 6 7. �� 8��. arrSubCategory(���� �������Ʈ UTextBlock SubCategory1 2 3 4 5 6 7 8 ���� �迭)
	{
		arrSubCategory[i]->SetText(FText::FromString("")); //�ڡڡڡڡ� FromString("") �� ���? �� ���ڿ��� ����?
		
		//�ڡڡڡڡ� �Ʒ� if �� ��ü ���� �� ��. i �� 0 �̸� SubCategory �� SubCategory1 �� �ʹ� �����ߴµ�, items[i] �� ��� ��Ī �Ǵ� ������ ������
		if (i < items.Num())
		{
			arrSubCategory[i]->SetText(FText::FromString(items[i])); 
		}
	}
}


//[��ǰ ���� �����ϴ� �Լ�]
void UWidget_AssetMain::SetProductInfo(int32 subCategory) //subcategory = �Ű�����. ����/��Ź/���ĵ�/TV ... �߿� ������ Ŭ���� ������ �𸣴ϱ� �㱸�� ����
{
	TArray<FWidgetProductInfo> items = csvLoader->GetProductInfo(subCategory);

		// 0 * 4 = 0 ---> 0 = ����1
		// 1 * 4 = 4 ---> 4 = ��Ź1
		// 2 * 4 = 8 ---> 8 = ����1
		// 3 * 4 = 12 ---> 12 = ħ��1
		// 4 * 4 = 16 ---> 16 = ���ĵ�1
		// 5 * 4 = 20 ---> 20 = TV1
		// 6 * 4 = 24 ---> 24 = �����1
		// 7 * 4 = 28 ---> 28 = ȭ��1

	//�ڡڡڡڡ� �Ʒ� for �� ��ü ���� �� ��. i �� 0 �̸� arrProductName �� Name1 �� �Ŵ� �����ߴµ�, items[0].name �� ��� ��Ī �Ǵ� ������ ������
	for (int32 i = 0; i < items.Num(); i++)
	{
		arrProductName[i]->SetText(FText::FromString(items[i].name));
		arrProductPrice[i]->SetText(FText::AsNumber(items[i].price)); //items[i].price ���� ���� ������ �����ͼ� ���ڷ� ����, AsNumber �� ���ڿ��� ��ȯ
		arrProductThumbnail[i]->SetBrushFromTexture(items[i].thumbnail);
	}
}

void UWidget_AssetMain::SelectProduct(int32 value)
{
	productManager->SelectedProduct(value);
	player->productGhost->SetInit(value);
	player->currState = EPlayerState::SelectedProduct;
}


