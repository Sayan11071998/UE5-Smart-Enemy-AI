#include "Enemy/AI/Tasks/SEAI_BTT_SetStateAsPassive.h"
#include "AIController.h"
#include "Enemy/AI/SEAI_EnemyAIController_Base.h"

USEAI_BTT_SetStateAsPassive::USEAI_BTT_SetStateAsPassive()
{
	NodeName = TEXT("Set State As Passive");
}

EBTNodeResult::Type USEAI_BTT_SetStateAsPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASEAI_EnemyAIController_Base* AIC = Cast<ASEAI_EnemyAIController_Base>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		AIC->SetStateAsPassive();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}