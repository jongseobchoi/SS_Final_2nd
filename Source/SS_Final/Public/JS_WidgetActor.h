// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JS_InteractionComp.h"
#include "GameFramework/Actor.h"
#include "JS_WidgetActor.generated.h"


UCLASS()
class SS_FINAL_API AJS_WidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_WidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;
	// ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* compWidget;
	// ��ǰ ���� ����Ŭ����
	TSubclassOf<UUserWidget> productWidgetFactroy;
	// �ٴ� ����
	TSubclassOf<UUserWidget> floorWidgetFactroy;
	// �� ����
	TSubclassOf<UUserWidget> wallWidgetFactroy;
	// Ȱ��ȭ �Լ�
	void SetActive(bool value);
	// ���� ������ ���¿� ���� ������ ���� ����
	void SetWidgetType(EHitActorState value);
	// ���� ���� ���� ���� �Ľ̿�
	EHitActorState actorState;
};
