#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemWidget;

UCLASS( BlueprintType )
class E2EE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION( BlueprintCallable )
	UItemWidget* GetItemWidget();

	UFUNCTION( BlueprintCallable )
	void SetItemWidget( UItemWidget* ItemWidgetToSet );

	UFUNCTION( BlueprintCallable )
	TArray<EItemUsage> GetItemUsages();

protected:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY( BlueprintReadWrite )
	UItemWidget* ItemWidget;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray<EItemUsage> ItemUsages;

public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	AItem* Duplicate();

};
