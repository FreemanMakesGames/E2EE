#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DropItemComponent.generated.h"

class AItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class E2EE_API UDropItemComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	UDropItemComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void DropItem( AItem* ItemToDrop );

};
