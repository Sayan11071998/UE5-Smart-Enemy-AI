#include "Enemy/AI/Notifies/SEAI_AN_EquipWeapon.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"

void USEAI_AN_EquipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(MeshComp->GetOwner()))
		{
			Enemy->HandleEquipNotify();
		}
	}
}
