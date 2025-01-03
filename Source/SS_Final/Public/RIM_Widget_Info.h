// ©Copyright 2021 XID

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RIM_Widget_Info.generated.h"

/**
 * 
 */
UCLASS()
class SS_FINAL_API URIM_Widget_Info : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextBlock;

public:
	void SetLink();

	TSharedPtr<class IWebBrowserWindow> WebBrowserWindow;

};
