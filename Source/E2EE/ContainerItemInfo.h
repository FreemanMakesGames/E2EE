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

protected:

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	UItemInfo* ContainedItem;

	UPROPERTY( VisibleInstanceOnly, BlueprintReadWrite )
	ULockItemInfo* CurrentLock;

	UPROPERTY()
	UContainerItemWidget* ContainerItemWidget;

public:

	virtual UContainerItemInfo* Duplicate() override;

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

// protected:
// 
// 	UFUNCTION( BlueprintCallable )
// 	void LockVisually();
// 
// 	UFUNCTION( BlueprintCallable )
// 	void UnlockVisually();
// 
// 	UFUNCTION( BlueprintCallable )
// 	void ContainVisually();
// 
// 	UFUNCTION( BlueprintCallable )
// 	void OpenVisually();
	
};
