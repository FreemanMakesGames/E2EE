#pragma once

#include "ItemUsage.h"
#include "ItemInfo.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemInfo;
class UItemWidget;

UCLASS( Blueprintable, BlueprintType )
class E2EE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem( const FObjectInitializer& ObjectInitializer );

public:

	UFUNCTION( BlueprintCallable )
	UItemInfo* GetItemInfo();

	UFUNCTION( BlueprintCallable )
	void SetItemInfo( UItemInfo* InItemInfo );

protected:

	UPROPERTY( Replicated, BlueprintReadOnly )
	UItemInfo* ItemInfo;

public:

	virtual bool ReplicateSubobjects( class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags ) override;

};
