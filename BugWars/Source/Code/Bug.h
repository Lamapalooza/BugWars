#pragma once
#include "GameBase/BugBase.h"

struct Bug : public BugBase
{

	Bug();

	DEFINE_RTTI;

	virtual void OnUpdate(float dt) override;
	virtual BugBase* FindBugToEat() const override;
	virtual void OnEat(BugBase& first, BugBase& second) override;
};