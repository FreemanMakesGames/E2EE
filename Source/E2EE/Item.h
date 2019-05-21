#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemInfo;

class UUserWidget;

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
	virtual UItemInfo* GetItemInfo() PURE_VIRTUAL( , return ItemInfo; );

	UFUNCTION( BlueprintCallable )
	virtual void SetItemInfo( UItemInfo* InItemInfo ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual UUserWidget* GetItemWidget() PURE_VIRTUAL( , return ItemWidget; );

	UFUNCTION( BlueprintCallable )
	virtual void SetItemWidget( UUserWidget* ItemWidgetToSet ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	TArray<EItemUsage> GetItemUsages();

protected:

	UPROPERTY()
	UItemInfo* ItemInfo;

	UPROPERTY( BlueprintReadWrite )
	UUserWidget* ItemWidget;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray<EItemUsage> ItemUsages;

public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	AItem* Duplicate();

};
