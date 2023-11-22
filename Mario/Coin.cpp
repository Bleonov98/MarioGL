#include "Coin.h"

void Coin::PlayAnimation()
{
	SetTexture(ResourceManager::GetTexture("coin_" + std::to_string(frame)));

	if (animToggle) frame--;
	else frame++;

	if (frame == 0 || frame == 2) animToggle = !animToggle; // change from 0 to 2 and back
}

void Coin::FlipAnimation() // animation for flip coins while it's moving
{
	if (!reached && !madeOnce) {
		SetTexture(ResourceManager::GetTexture("flip_coin_0"));
		madeOnce = true; // change texture once and then just skip
	}
	else if (reached) {
		SetTexture(ResourceManager::GetTexture("flip_coin_1"));
		madeOnce = false;
	}
	else if (reached && !madeOnce) {
		SetTexture(ResourceManager::GetTexture("flip_coin_2"));
		madeOnce = false;
	}
}

void Coin::Move(float dt)
{
	if (coinType == COIN_REGULAR) return;

	if (position.y > startPos.y - size.y * 3.0f && !reached) position.y -= speed * dt; // go to top
	else if (position.y <= startPos.y - size.y && !reached) reached = true; // on top
	else if (position.y <= startPos.y && reached) position.y += speed * dt; // go to bot
	else if (position.y >= startPos.y && reached) DeleteObject(); // delete when back to start position
}
