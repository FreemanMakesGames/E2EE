#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DropItemComponent.generated.h"

class AItem;
class UItemInfo;

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

protected:

	/** When spawning multiple items, increment this step with each spawn, to prevent spawn collision. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float SpawnCollisionPreventionStep = 50.0f;

public:

	UFUNCTION( Server, Reliable, WithValidation, BlueprintCallable )
	void ServerDropItem( UItemInfo* ItemToDrop );

	UFUNCTION( BlueprintCallable )
	void DropMultipleItems( TArray<UItemInfo*> ItemsToDrop );

};
