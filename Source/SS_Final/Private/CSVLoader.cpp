// Fill out your copyright notice in the Description page of Project Settings.

#include "CSVLoader.h"
#include "Containers/Map.h"
#include <Engine/StaticMesh.h>
#include "RIM_CartProduct.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
UCSVLoader::UCSVLoader()
{

}

// Called when the game starts or when spawned
void UCSVLoader::Init()
{
	Super::Init();

	//[메인 카테고리 ---> 클릭 ---> 서브 카테고리]

	//FString 형태의 FilePath 변수 선언. FilePath 에 save 폴더에 있는 프로덕트타입.csv 파일 저장
	FString FilePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("프로덕트타입.csv"));

	//FString 형태의 FileContent 변수 선언
	FString FileContent;

	//FileContent 에 FilePath(csv 파일) 로드되면... 데이터를 TArray 형태로 저장(아래 코드) 
	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		//UE_LOG(LogTemp, Error, TEXT("%s"), *FileContent); //프로덕트타입.csv 의 데이터 들어왔는지 확인

		TArray<FString> Rows; //가로(행)
		FileContent.ParseIntoArrayLines(Rows); //가로(행). FileContent(프로덕트타입.csv) 를 행 단위로 분리하여 Rows 배열에 넣음 

		for (int32 i = 0; i < Rows.Num(); i++) //가로(행)를 for 문 으로 돌림. 0 1 2 3 4 (총 5행)
		{
			//UE_LOG(LogTemp, Error, TEXT("%s"), *Rows[i]); //가로(행) 으로 데이터 들어오는지 확인

			TArray<FString> Columns; //세로(열)
			Rows[i].ParseIntoArray(Columns, TEXT(",")); //가로(행)을 ,(콤마) 기준으로 열로 분할 ★★★이해 안 됨. 그림이 잘 안 그려진다

			//아래 코드로 서브 카테고리 데이터만 선별 한다
			if (i == 0) //i 가 0 일 때는 필요 없으니까 i 가 0이면 (Category, string1, string2, string3, string4 ---> 해당 행)
			{
				columMax = Columns.Num() - 1; //4 = 5 - 1. 세로(열) 첫번째 줄 제외하고 세로(서브 카테고리)의 최대 열수 구함
			}
			else //i 가 0이 아니면. 첫번째 가로(행) 버린 상태
			{
				for (int32 j = 1; j < columMax + 1; j++) //첫번째 세로(열) 버리기 위해 1부터 for 문 돌림. 1 2 3 4 
				{
					if (j < Columns.Num()) //j < 5. i 가 1 2 3 4 이면
					{
						arrCategory.Add(Columns[j]); //arrCategory 배열에 서브 카테고리 데이터 담음
					}
					else
					{
						arrCategory.Add(""); //세로(열)에서 데이터 안 들어있는 열을 빈 값으로 처리
					}
				}
			}
		}
	}
	else //FileContent 에 FilePath(csv 파일)을 로드 못하면
	{
		//아래 로그 출력
		UE_LOG(LogTemp, Error, TEXT("Failed to load file %s"), *FilePath);
	}



	//[서브 카테고리 ---> 클릭 ---> 제품]

	//FString 형태의 FileProductInfoPath 변수 선언. FileProductInfoPath 에 save 폴더에 있는 프로덕트정보.csv 파일 저장
	FString FileProductInfoPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("프로덕트정보.csv"));

	//FString 형태의 FileContentProductInfo 변수 선언
	FString FileContentProductInfo;

	//FileContentProductInfo 에 FileProductInfoPath(csv 파일) 로드되면... 데이터를 TArray 형태로 저장(아래 코드) 
	if (FFileHelper::LoadFileToString(FileContentProductInfo, *FileProductInfoPath))
	{
		//UE_LOG(LogTemp, Error, TEXT("%s"), *FileContentProductInfo); //가로(행) 으로 데이터 들어오는지 확인 ---> 잘 나옴

		TArray<FString> ProductInfoRows; //가로(행)
		FileContentProductInfo.ParseIntoArrayLines(ProductInfoRows); //가로(행). FileContentProductInfo(프로덕트정보.csv) 를 행 단위로 분리하여 Rows 배열에 넣음 

		for (int32 i = 0; i < ProductInfoRows.Num(); i++) //가로(행)를 for 문 으로 돌림. 0 1 2 3 ~ 30 31 32 (총 33행)
		{
			//UE_LOG(LogTemp, Error, TEXT("%s"), *ProductInfoRows[i]); //가로(행) 으로 데이터 들어오는지 확인 ---> 잘 나옴

			TArray<FString> ProductInfoColumns; //세로(열)
			ProductInfoRows[i].ParseIntoArray(ProductInfoColumns, TEXT(","));  //가로(행)을 ,(콤마) 기준으로 열로 분할 ★★★이해 안 됨. 그림이 잘 안 그려진다

			//아래 코드 제품 정보 데이터만 선별한다
			if (i == 0) //i 가 0 일 때는 필요 없으니까 i 가 0이면 (Product, Name, Price, Thumbnail ---> 해당 행)
			{
				productInfoColumMax = ProductInfoColumns.Num() - 1; //3 = 4 - 1. 세로(열) 첫번째 줄 제외하고 세로(제품 정보)의 최대 열수 구함
			}
			else //i 가 0이 아니면. 첫번째 가로(행) 버린 상태
			{
				FWidgetProductInfo info; //★★★왜 필요한 것인지 모르겠다. FWidgetProductInfo(구조체) 형태의 변수 info 선언...?
				
				for (int32 j = 1; j < productInfoColumMax + 1; j++) //첫번째 세로(열) 버리기 위해 1부터 for 문 돌림. 1 2 3
				{
					if (j == 1) info.name = ProductInfoColumns[j]; //j1(열) = 제품 이름. info(구조체 변수)의 멤버 변수에 제품 이름 데이터 담음
					if (j == 2) info.price = FCString::Atoi(*ProductInfoColumns[j]); //j2(열) = 제품 가격. info(구조체 변수)의 멤버 변수에 제품 가격 데이터 담음. FCString::Atoi 를 이용해서 ProductInfoColumns[j]의 값을 숫자로 변환해서 담음			

					if (j == 3) //j3(열) = 제품 썸네일. FString(문자열) 을 UTexture2D 로 변환 필요
					{
						FSoftObjectPath thumbnailObject(ProductInfoColumns[j]); //FString 을 UObject 로 변환

						UObject* object = thumbnailObject.TryLoad();
						UTexture2D* thumbnailTexture = Cast<UTexture2D>(object); //UObject 를 UTexture2D 로 변환

						if (thumbnailTexture)
						{
							info.thumbnail = thumbnailTexture;
						}
					}

					if (j == 4)
					{
						FSoftObjectPath productObject(ProductInfoColumns[j]); //FString 을 UObject 로 변환
						UObject* object = productObject.TryLoad();
						UStaticMesh* productStacticMesh = Cast<UStaticMesh>(object); //UObject 를 UStaticMesh 로 변환

						if (productStacticMesh)
						{
							info.mesh = productStacticMesh;
						}
					}

					if (j == 5) info.id = FCString::Atoi(*ProductInfoColumns[j]);
					//if (j == 6) info.lightLoc = FVector();

				}
				arrProductInfo.Add(info); //위의 데이터를 arrProductInfo(배열)에 저장
				mapProdutInfo.Add(info.id, info); //info.id = 키, info = 값
			}
			

		}


		/*FWidgetProductInfo* iii = mapProdutInfo.Find(1101);
		UE_LOG(LogTemp, Error, TEXT("----------------------- : %d"), iii->id);*/
	}
	else  //FileContent 에 FileProductInfoPath(csv 파일)을 로드 못하면
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Product file %s"), *FileProductInfoPath);
	}



}


//[메인 카테고리 ---> 클릭 ---> 서브 카테고리]
TArray<FString> UCSVLoader::GetCategoryItem(int32 category) //category = 매개변수. 가구/조명/가전제품/기타 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음
{
	TArray<FString> arr;

	//서브 카테고리에서 각 서브 카테고리를 구분하는 시작점 구하기
	//category(매개변수. 총 4개)에 columMax(최대 열 수) 곱해서 start 에 담음
	int32 start = category * columMax;
	
		// start = category 매개변수 * 4
		// 0 * 4 = 0 ---> 0 = 소파
		// 1 * 4 = 4 ---> 4 = 스탠드
		// 2 * 4 = 8 ---> 8 = TV
		// 3 * 4 = 12 ---> 12 = 화분

	for (int32 i = 0; i < columMax; i++) //0 1 2 3
	{
		//arrCategory 배열(선별 된 서브 카테고리 데이터) 가 빈 문자열일 때 나감
		if (arrCategory[start + i].Len() == 0) break; //★★★★★ 이해 안 됨.그림이 잘 안 그려진다
			
		//arrCategory 배열(선별 된 서브 카테고리 데이터) 가 빈 문자열이 아니면 arr 배열에 추가
		arr.Add(arrCategory[start + i]); //★★★★★ 이해 안 됨.그림이 잘 안 그려진다
	}
	return arr;
}


//[서브 카테고리 ---> 클릭 ---> 제품]
TArray<FWidgetProductInfo> UCSVLoader::GetProductInfo(int32 subCategory) //subcategory = 매개변수. 소파/식탁/스탠드/TV ... 중에 무엇을 클릭할 것인지 모르니까 허구로 넣음
{
	TArray<FWidgetProductInfo> arr;

	//제품에서 각 제품을 구분하는 시작점 구하기
	//subcategory(매개변수. 총 8개)에 4 곱해서 start 에 담음
	int32 start = subCategory * 4;

		// start = subCategory 매개변수 * 4
		// 0 * 4 = 0 ---> 0 = 소파1
		// 1 * 4 = 4 ---> 4 = 식탁1
		// 2 * 4 = 8 ---> 8 = 의자1
		// 3 * 4 = 12 ---> 12 = 침대1
		// 4 * 4 = 16 ---> 16 = 스탠드1
		// 5 * 4 = 20 ---> 20 = TV1
		// 6 * 4 = 24 ---> 24 = 냉장고1
		// 7 * 4 = 28 ---> 28 = 화분1

	for (int32 i = 0; i < 4; i++)  // 0 1 2 3
	{
		//arrCategory 배열(선별 된 서브 카테고리 데이터) 가 빈 문자열이 아니면 arr 배열에 추가
		arr.Add(arrProductInfo[start + i]); //★★★★★ 이해 안 됨.그림이 잘 안 그려진다
	}
	return arr;
}


//가구 위젯에서 장바구니 버튼을 클릭하면 클릭한 제품의 "id" 를 arrCart 에 담는다
// void UCSVLoader::AddCart(int32 productIndex)
// {
// 	FWidgetProductInfo selectProduct = arrProductInfo[productIndex]; //★★★★★ productIndex ???
// 	arrCart.Add(selectProduct.id); //★★★★★ 선택(클릭)한 제품의 id 들을 배열에 담는다...???
// }

//[위의 코드 수정1] 가구 위젯에서 장바구니 버튼을 클릭하면 클릭한 제품의 "id" 를 arrCart 에 담는다
// void UCSVLoader::AddCart(int32 productIndex)
// {
// 	FWidgetProductInfo selectProduct = arrProductInfo[productIndex]; //★★★★★ productIndex ???
// 	
// 	if (arrCart.Num() < 10)
// 	{
// 		arrCart.Add(selectProduct.id); //★★★★★ 선택(클릭)한 제품의 id 들을 배열에 담는다...???
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Cart is full !!!!!"));
// 
// 		//위젯으로 알럿 띄는 것 고려
// 	}
// }

//[위의 코드 수정2] 가구 위젯에서 장바구니 버튼을 클릭하면 클릭한 제품의 "id" 를 arrCart 에 담는다
void UCSVLoader::AddCart(int32 productIndex)
{
	FWidgetProductInfo selectProduct = arrProductInfo[productIndex]; //★★★★★ productIndex ???

	if (!arrCart.Contains(selectProduct.id))
	{
		if (arrCart.Num() < 10)
		{
			arrCart.Add(selectProduct.id); //★★★★★ 선택(클릭)한 제품의 id 들을 배열에 담는다...???
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cart is full !!!!!"));

			//위젯으로 알럿 띄는 것 고려
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Product is already in the cart !!!!!"));

		//위젯으로 알럿 띄는 것 고려
	}

}


/*
void UCSVLoader::CreateProductInCart() //테스트(선생님). ---> 다른 파일에 만들 것
{
	FVector pos(-429,  376, 130.000000); //테스트

	for (int32 i = 0; i < arrCart.Num(); i++) //arrCart =  선택(클릭)한 제품의 id 들
	{
		FWidgetProductInfo* info = mapProdutInfo.Find(arrCart[i]); //mapProdutInfo 에서 선택(클릭)한 제품의 id 들을 찾고 info 에 담는다
		
		UE_LOG(LogTemp, Warning, TEXT("-------------------------")); //테스트
		UE_LOG(LogTemp, Warning, TEXT("id : %d"), info->id); //테스트
		UE_LOG(LogTemp, Warning, TEXT("price : %d"), info->price); //테스트
		UE_LOG(LogTemp, Warning, TEXT("name : %s"), *info->name); //테스트
		UE_LOG(LogTemp, Warning, TEXT("-------------------------")); //테스트

		//테스트
		ARIM_CartProduct* obj = GetWorld()->SpawnActor<ARIM_CartProduct>(cartProductFactory, pos + FVector::RightVector * 100 * (i + 1), FRotator::ZeroRotator);
		//obj->SetActorScale3D(FVector(scale));
		obj->SetInit(info->product);

	}
}*/


//위에서 담은 "제품 id 의 정보를 찾아서 info 에 담고, arr 에 담는다 -----> 해당 함수 사용해서 장바구니에 제품 스폰 시킴
TArray<FWidgetProductInfo> UCSVLoader::GetProductInfoInCart()
{
	TArray<FWidgetProductInfo> arr;

	for (int32 i = 0; i < arrCart.Num(); i++) //arrCart =  선택(클릭)한 제품의 id 들
	{
		FWidgetProductInfo* info = mapProdutInfo.Find(arrCart[i]); //mapProdutInfo(id(키) - 정보(값)) 에서 arrCart(선택(클릭)한 제품의 id 들)을 찾고 info 에 담는다
		if (info)
		{
			arr.Add(*info); // info(id 와 id 에 해당하는 정보) 를 arr 배열에 담는다
		}
	}
	return arr; 
}

