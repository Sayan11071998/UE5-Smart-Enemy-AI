#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SEAI_EnemyAIController_Base.generated.h"

class UBehaviorTree;

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyAIController_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	ASEAI_EnemyAIController_Base();
	
	void SetStateAsPassive();
	void SetStateAsAttacking(TObjectPtr<AActor> Target);
	
protected:
	// ~ Begin AController interface
	virtual void OnPossess(APawn* InPawn) override;
	// ~ End AController interface
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName StateKeyName = FName("AIState");

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AttackTargetKeyName = FName("AttackTarget");
};