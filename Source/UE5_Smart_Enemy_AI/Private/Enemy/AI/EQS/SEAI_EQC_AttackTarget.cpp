#include "Enemy/AI/EQS/SEAI_EQC_AttackTarget.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Enemy/AI/SEAI_EnemyAIController_Base.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void USEAI_EQC_AttackTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	if (!QueryOwner) return;
	
	if (APawn* QueryPawn = Cast<APawn>(QueryOwner))
	{
		if (ASEAI_EnemyAIController_Base* AIC = Cast<ASEAI_EnemyAIController_Base>(QueryPawn->GetController()))
		{
			AActor* TargetActor = AIC->GetAttackTarget();
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
		}
	}
}