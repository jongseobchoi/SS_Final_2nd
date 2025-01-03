// ©Copyright 2021 XID

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JS_DoorBase.generated.h"

UCLASS()
class SS_FINAL_API AJS_DoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJS_DoorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere)
	class ACharacterBase* player;

	UPROPERTY(EditAnywhere)
	class USceneComponent* compScene;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	FRotator initRot;

	UPROPERTY(EditAnywhere)
	bool canDoorOpen = false;

	UPROPERTY(EditAnywhere)
	bool bDoorOpen = false;


	void OpenDoor();
};
