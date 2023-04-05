// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UMG/Public/Components/Button.h>
#include "JS_ProductWidget.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API UJS_ProductWidget : public UUserWidget
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
	class UTextBlock* ProductNameTex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* IconNameTex;

	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;
	UPROPERTY(EditAnywhere)
	class AProductBase* selectedProduct;
	UPROPERTY(EditAnywhere)
	class ALightBase* selectedLight;

	void PressBTN(int32 btnIndex);
	void ReleaseBTN(int32 btnIndex);
	void OnHoveredBTN(int32 btnIndex);
	void UnHoveredBTN(int32 btnIndex);

// 
// 	UFUNCTION()
// 	void SetHoveredColor(FString name);
// 
// 	UFUNCTION()
// 	void SetUnhoveredColor(FString ame);

	
};


UCLASS()
class USelectedButton : public UObject
{
	GENERATED_BODY()
public:
	USelectedButton() {}

	int32 index;

	UPROPERTY()
	UJS_ProductWidget* target;

	void Init(int32 n, UJS_ProductWidget* t)
	{
		index = n;
		target = t;
	}
	UFUNCTION()
	void OnPressed() {
		target->PressBTN(index);
	}

	UFUNCTION()
	void OnReleased() {
		target->ReleaseBTN(index);
	}

	UFUNCTION()
	void OnHovered() {
		target->OnHoveredBTN(index);
	}

	UFUNCTION()
	void UnHovered() {
		target->UnHoveredBTN(index);
	}
	


};