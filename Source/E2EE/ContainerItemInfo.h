#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "ContainerItemInfo.generated.h"

class UItemInfo;
class ULockItemInfo;
class UKeyItemInfo;
class UContainerItemWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnOccupied );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnVacated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnLocked );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnUnlocked );

/**
 * 
 */
UCLASS()
class E2EE_API UContainerItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	UContainerItemInfo();

public:

	UPROPERTY( BlueprintAssignable )
	FOnOccupied OnOccupied;

	UPROPERTY( BlueprintAssignable )
	FOnVacated OnVacated;

	UPROPERTY( BlueprintAssignable )
	FOnLocked OnLocked;

	UPROPERTY( BlueprintAssignable )
	FOnUnlocked OnUnlocked;
	

public:

	UFUNCTION( BlueprintCallable )
	UItemInfo* GetContainedItem();

	UFUNCTION( BlueprintCallable )
	int GetLockId();

	UFUNCTION( BlueprintCallable )
	ULockItemInfo* GetLock();

protected:

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	UItemInfo* ContainedItem;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ULockItemInfo* CurrentLock;

	UPROPERTY()
	UContainerItemWidget* ContainerItemWidget;

public:

	virtual UContainerItemInfo* Duplicate() override;

	virtual FText Describe() override;

	virtual bool IsEquivalentTo( UItemInfo* OtherItem ) override;

public:

	UFUNCTION( BlueprintCallable )
	void ContainItem( UItemInfo* TargetItem );

	UFUNCTION( BlueprintCallable )
	UItemInfo* ReleaseItem();

	UFUNCTION( BlueprintCallable )
	void LockUp( ULockItemInfo* InLock );

	UFUNCTION( BlueprintCallable )
	void Unlock();

	UFUNCTION( BlueprintCallable )
	bool IsOccupied();

	UFUNCTION( BlueprintCallable )
	bool IsLocked();
	
};
