// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UMG/Public/Components/Button.h>
#include "Blueprint/UserWidget.h"
#include "JS_WallWidget.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API UJS_WallWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// 버튼 담을 배열
	TArray<UButton*> ButtonArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Button0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Button1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Button2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Button3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* MatNameTex;

	UPROPERTY(EditAnywhere)
		class ACharacterBase* player;


	UFUNCTION(BlueprintCallable)
		void PressBTN0();
	UFUNCTION(BlueprintCallable)
		void PressBTN1();
	UFUNCTION(BlueprintCallable)
		void PressBTN2();
	UFUNCTION(BlueprintCallable)
		void PressBTN3();

	UFUNCTION(BlueprintCallable)
		void ReleaseBTN0();
	UFUNCTION(BlueprintCallable)
		void ReleaseBTN1();
	UFUNCTION(BlueprintCallable)
		void ReleaseBTN2();
	UFUNCTION(BlueprintCallable)
		void ReleaseBTN3();

	// 스칠때 색 바뀌는 함수
	UFUNCTION(BlueprintCallable)
		void OnHoveredBTN0();
	UFUNCTION(BlueprintCallable)
		void OnHoveredBTN1();
	UFUNCTION(BlueprintCallable)
		void OnHoveredBTN2();
	UFUNCTION(BlueprintCallable)
		void OnHoveredBTN3();
	UFUNCTION(BlueprintCallable)
		void UnHoveredBTN0();
	UFUNCTION(BlueprintCallable)
		void UnHoveredBTN1();
	UFUNCTION(BlueprintCallable)
		void UnHoveredBTN2();
	UFUNCTION(BlueprintCallable)
		void UnHoveredBTN3();
};

