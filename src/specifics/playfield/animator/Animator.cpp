#include "Animator.h"

void Animator::DrawAnimations(sf::RenderWindow& window)
{
	for (int i = 0; i < anims.size(); i++)
	{
		anims[i]->Draw(window);
	}
}

void Animator::StepAnimations(float dt)
{
	for (int i = 0; i < anims.size(); i++)
	{
		anims[i]->Step(dt);
	}
}

void Animator::AddAnimation(std::shared_ptr<Animation> anim)
{
	anims.push_back(anim);
}

void Animator::DeleteDoneAnimations()
{
	for (int i = 0; i < anims.size(); i++)
	{
		if (anims[i]->IsDone())
		{
			anims.erase(anims.begin() + i);
		}
	}
}
