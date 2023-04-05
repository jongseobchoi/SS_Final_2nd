// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_JSonObjectManager.h"
#include "Dom/JsonObject.h"
#include <Kismet/GameplayStatics.h>
#include "ProductBase.h"
#include <EngineUtils.h>
#include <Dom/JsonValue.h>
#include <Dom/JsonObject.h>
#include <Serialization/JsonSerializer.h>
#include <Serialization/JsonWriter.h>
#include <Misc/FileHelper.h>

// Sets default values
AJS_JSonObjectManager::AJS_JSonObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJS_JSonObjectManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 디버그용 인풋 등록
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	
	EnableInput(playerCon);

	InputComponent->BindAction(TEXT("9"),IE_Pressed,this,&AJS_JSonObjectManager::SaveObject);
	InputComponent->BindAction(TEXT("0"),IE_Pressed,this,&AJS_JSonObjectManager::LoadObject);
}

// Called every frame
void AJS_JSonObjectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJS_JSonObjectManager::SaveObject()
{


	// 현재 월드에서 AProductBase 액터만 찾기
	for (TActorIterator<AProductBase> It(GetWorld()); It; ++It)
	{
		// 로그 찍어보기
		UE_LOG(LogTemp,Warning, TEXT("AProductBase : %s"), *It->GetName())
		product = *It;
		int32 count = 0;

		FObjectInfo info;
		info.idx = count;
		info.obj = product;
		infoArr.Add(info);
		count++;
	}

	TArray<TSharedPtr<FJsonValue>> jsonArr;
	
	for (int32 i = 0; i < infoArr.Num(); i++)
	{
		TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());

		jsonObject->SetNumberField("Idx",infoArr[i].idx);
		jsonObject->SetNumberField("pos_x",infoArr[i].obj->GetActorLocation().X);
		jsonObject->SetNumberField("pos_y",infoArr[i].obj->GetActorLocation().Y);
		jsonObject->SetNumberField("pos_z",infoArr[i].obj->GetActorLocation().Z);
		jsonObject->SetNumberField("rot_pitch",infoArr[i].obj->GetActorRotation().Pitch);
		jsonObject->SetNumberField("rot_yaw",infoArr[i].obj->GetActorRotation().Yaw);
		jsonObject->SetNumberField("rot_roll",infoArr[i].obj->GetActorRotation().Roll);

		jsonArr.Add(MakeShareable(new FJsonValueObject(jsonObject)));
	}
	
	// JsonObject ----> FString 으로

	// json 스트링 선언
	FString jsonString;
	TSharedRef<TJsonWriter<>> jsonWrite = TJsonWriterFactory<>::Create(&jsonString);

	// jsonWrite에 jsonArr을 직렬화
	FJsonSerializer::Serialize(jsonArr, jsonWrite);


	UE_LOG(LogTemp,Warning, TEXT("%s"),*jsonString)
	
	const FDateTime Now = FDateTime::Now();
	// 변경된 FString을 파일로 저장
	FString fileName = FString::Printf(TEXT("product_info_%d%02d%02d_%02d%02d.txt"), Now.GetYear(), Now.GetMonth(), Now.GetDay(), Now.GetHour(), Now.GetMinute());

	// 저장할 경로와 파일 이름 지정
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), fileName);


	// 저장하기
	FFileHelper::SaveStringToFile(jsonString, *filePath);
	
	

}

void AJS_JSonObjectManager::LoadObject()
{
	DeleteAll();
	
	TArray<TSharedPtr<FJsonValue>> jsonArr;
	FString jsonString;
	// 불러올 경로와 파일 이름 지정
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("product_info.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);

	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	FJsonSerializer::Deserialize(jsonReader, jsonArr);

// 	// 제품 생성
// 	for (int32 i = 0; i < jsonArr.Num(); i++)
// 	{
// 		GetWorld()->SpawnActor()
// 	}
}

void AJS_JSonObjectManager::DeleteAll()
{

	// 현재 월드에서 AProductBase 액터만 찾기
	for (TActorIterator<AProductBase> It(GetWorld()); It; ++It)
	{
		product = *It;
		/*product->RemoveAt();*/
	}
	
}


