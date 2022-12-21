#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

Tank::Tank() {

	visible = true;
	disabled = false;

}

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	Bug* target = nullptr;
	float min_distance = std::numeric_limits<float>::max();

	for (auto& object : g_Game->objects)
		if (object->GetRTTI() == Bug::s_RTTI) {

			float distance = position.Distance2(object->position);

			if (distance < min_distance)
			{
				min_distance = distance;
				target = static_cast<Bug*>(object);
			}
		}

	return target;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	auto distance = target_pos - position;
	auto velocity = target_dir * target_vel;

	auto a = velocity.Length2() - bullet_vel * bullet_vel;
	auto b = 2 * (velocity.x * distance.x + velocity.y * distance.y);
	auto c = distance.Length2();

	auto det = b * b - 4 * a * c;

	if (det <= 0)
		return distance;

	auto detSqrt = sqrtf(det);

	auto correctDirection = std::max((-b - detSqrt) / (2 * a), (-b + detSqrt) / (2 * a));
	
	return velocity * correctDirection + distance;
}
