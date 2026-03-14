#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"
#include "SEAI_EnemyAIController_Base.generated.h"

class UAISenseConfig_Damage;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
struct FAIStimulus;
class UBehaviorTree;

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyAIController_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	ASEAI_EnemyAIController_Base();
	
	void SetStateAsPassive();
	void SetStateAsAttacking(TObjectPtr<AActor> Target);
	void SetStateAsInvestigating(FVector Location);
	
protected:
	// ~ Begin AController interface
	virtual void OnPossess(APawn* InPawn) override;
	// ~ End AController interface
	
	bool CanSenseActor(TObjectPtr<AActor> Actor, ESEAI_AISense Sense, FAIStimulus& OutStimulus) const;
	ESEAI_AIState GetCurrentState() const;
	
	void HandleSensedSight(TObjectPtr<AActor> Actor);
	void HandleSensedSound(FVector Location);
	void HandleSensedDamage(TObjectPtr<AActor> Actor);
	
	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName StateKeyName = FName("AIState");

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AttackTargetKeyName = FName("AttackTarget");
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PointOfInterestKeyName = FName("PointOfInterest");
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AttackRadiusKeyName = FName("AttackRadius");
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName DefendRadiusKeyName = FName("DefendRadius");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> AttackTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Damage> DamageConfig;
	
public:
	FORCEINLINE TObjectPtr<AActor> GetAttackTarget() const { return AttackTarget; }
};