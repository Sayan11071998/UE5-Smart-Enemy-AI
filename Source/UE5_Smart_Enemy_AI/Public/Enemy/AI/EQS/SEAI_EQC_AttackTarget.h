#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SEAI_EQC_AttackTarget.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_EQC_AttackTarget : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	// ~ Begin UEnvQueryContext interface
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	// ~ End UEnvQueryContext interface
};