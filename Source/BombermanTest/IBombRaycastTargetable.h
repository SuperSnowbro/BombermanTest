#pragma once

#include "IBombRaycastTargetable.generated.h"

// Interface implemented in blueprints by those who are susceptible to Bomb's linetrace test for valid explosion tiles
// AKA those who block the explosion but still suffer from it, like the destructible walls.
UINTERFACE(BlueprintType)
class UBombRaycastTargetable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IBombRaycastTargetable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	bool NotifyBombRaycastHit();
};