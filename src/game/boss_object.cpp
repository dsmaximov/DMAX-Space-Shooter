#include "boss_object.h"

BossObject::BossObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D* sprite)
	:Strength(100){}
void BossObject::Init()
{
	InitialTime = std::chrono::steady_clock::now();
	glm::vec2 pos(200.0f, 200.0f);
	
	this->BossTurrets.push_back(new EnemyObject(pos, ENEMYRADIUS1, ENEMYVELOCITY1, ENEMYTEXTURE1, ENEMYSTRENGHT1, SCOREPOINTS1, 1, 0, SHOTVELOCITY1));
}
std::chrono::duration<GLint> BossObject::BossTimer()
{
	CurrentTime = std::chrono::steady_clock::now();
	auto a = std::chrono::duration_cast<std::chrono::duration<GLint>> (CurrentTime - InitialTime);
	return a;
}
void BossObject::Draw(TextRenderer& trenderer, SpriteRenderer& renderer)
{
	std::string TimerString = std::to_string(BossTimer().count());
	for (auto n : this->BossTurrets)
	{
		renderer.DrawSprite(n->Sprite, n->Position, n->Size, n->Rotation, n->Color);
	}

	trenderer.RenderText(TimerString, 310.0f, 80.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
}