
#include "Prop/ABFountain.h"
#include "Components/StaticMeshComponent.h"
// CDO에서 생성한 컴포넌트는 자동으로 월드에 등록이 된다.
// NewObject로 생선한 컴포넌트는 반드시 등록절차를 거쳐야한다.
// 등록된 컴포넌트는 월드의 기능을 사용할 수 있으며, 물리와 렌더링 처리에 합류한다.

// 컴포넌트 확장 설계
// - 에디터 편집 및 BP로의 승계를 위한 설정
// - UPROPERTY() 지정자 설정 가능.

// 컴포넌트 지정자.
// Visible/Edit -> 크게 객체타입과 값타입으로 사용.
// anywhere, DefaultsOnly, InstanceOnly => 에디터 편집 가능영역.
// BlueprintReadOnly / BlueprintReadWrite => BP로 확장시 읽기 혹은 읽기 쓰기 권한 부여
// Category => 에디터 편집 영역에서의 카테고리 지정.


AABFountain::AABFountain()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Water->SetRelativeLocation(FVector(0.f, 0.f, 132.f));

	//생성자 안의 코드이기에 constructorHelpers를 사용함.
	ConstructorHelpers::FObjectFinder<UStaticMesh>BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	if (BodyMeshRef.Object)
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WaterMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (WaterMeshRef.Object)
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}
}

void AABFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

