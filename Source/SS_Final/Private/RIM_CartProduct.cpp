// Fill out your copyright notice in the Description page of Project Settings.

#include "RIM_CartProduct.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "RIM_Widget_CartProduct.h"
#include <Components/BoxComponent.h>

// Sets default values
ARIM_CartProduct::ARIM_CartProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SetRootComponent(compMesh);
	compMesh->SetSimulatePhysics(true);
	compMesh->SetGenerateOverlapEvents(true);

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	compBox->SetupAttachment(compMesh);
	compBox->SetRelativeScale3D(FVector(2.5f, 2.5f, 1.5f));

	//Widget_CartProduct 위젯 등록
	compProductInfo = CreateDefaultSubobject<UWidgetComponent>(TEXT("ProductInfo Widget"));
	compProductInfo->SetupAttachment(compMesh);
	ConstructorHelpers::FClassFinder<UUserWidget> temp(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SS_Final/BluePrints/BP_WG_CartProduct.BP_WG_CartProduct_C'"));
	if (temp.Succeeded())
	{
		compProductInfo->SetWidgetClass(temp.Class);
	}
// 	compProductInfo->SetRelativeLocation(FVector(15, 0, -5));
// 	compProductInfo->SetRelativeRotation(FRotator(110, 180, 0));
// 	compProductInfo->SetRelativeScale3D(FVector(0.05));



}

// Called when the game starts or when spawned
void ARIM_CartProduct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARIM_CartProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

//스태틱메시 생성
void ARIM_CartProduct::SetInit(FWidgetProductInfo info) //매개변수 info ---> CartManager 에서 실행
{
	productInfo = info;

	//compMesh->SetStaticMesh(mesh); //어떤 메시가 들어갈지 모르니까...
	//compMesh->SetStaticMesh(imfo.product); //메시가 제품 이미지(3D) 뿐만 아니라 정보 다 들고 있다
	compMesh->SetStaticMesh(info.mesh); 

	URIM_Widget_CartProduct* ui = Cast<URIM_Widget_CartProduct>(compProductInfo->GetUserWidgetObject()); //위젯 가져와서
	ui->SetProductInfoWidgetInCart(info); //제품에 해당하는 정보를 위젯으로 뿌려준다
}

