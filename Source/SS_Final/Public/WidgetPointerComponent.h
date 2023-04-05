// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetPointerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SS_FINAL_API UWidgetPointerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetPointerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//EnhancedInput. �Է�
	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

public:
	//Input Action. ������ Ʈ���� ---> ���� Ŭ��
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UInputAction* rightTrigger;

public:
	UPROPERTY()
	class ACharacterBase* player;

public:
	//Input Action. ������ Ʈ����. ---> UI ��ҿ� ���� ��ư Pressed �� �Լ�
	void WidgetClickPressed();

	//Input Action. ������ Ʈ����. ---> UI ��ҿ� ���� ��ư Released �� �Լ�
	void WidgetClickReleased();


};
