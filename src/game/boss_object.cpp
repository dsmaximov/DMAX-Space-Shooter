#include "boss_object.h"

BossObject::BossObject(glm::vec2* ship_position)
	:ShipPosition(ship_position), Strength(100), Stage(0){}
void BossObject::Init()
{
	InitialTime = std::chrono::steady_clock::now();
	glm::vec2 pos(100.0f, -100.0f); //BOSS starting position
	for (int i = 0; i < TURRETCOUNT1; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + i*TURRETDISTANCE1, pos.y), TURRETRADIUS1, TURRETVELOCITY1, TURRETTEXTURE1, TURRETSTRENGHT1, SCOREPOINTS1, 1, 1, SHOTVELOCITY1));
	}	
	for (int i = 0; i < TURRETCOUNT2; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + 100 + i * TURRETDISTANCE2, pos.y + 70), TURRETRADIUS2, TURRETVELOCITY2, TURRETTEXTURE2, TURRETSTRENGHT2, SCOREPOINTS2, 2, 1, SHOTVELOCITY2));
	}
	
}
std::chrono::duration<GLint> BossObject::BossTimer()
{
	CurrentTime = std::chrono::steady_clock::now();
	auto a = std::chrono::duration_cast<std::chrono::duration<GLint>> (CurrentTime - InitialTime);
	return a;
}
void BossObject::Move(GLfloat dt, GLuint window_width, GLuint window_height)
{
	// initial movement into the screen
	GLint InitialTimerX = 3;
	if (BossTimer().count() < InitialTimerX) // initial movement into the screen
	{
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityY = 50.0f;
			n->Position.y += dt * InitialBossVelocityY;
		}
	}

	// wobbling in x
	else
	{
		this->Stage = 1;
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityX = 50.0f;
			if (LeftReached) n->Position.x += dt * InitialBossVelocityX;
			if (RightReached) n->Position.x -= dt * InitialBossVelocityX;
		}
		if (this->BossTurrets[0]->Position.x > window_width / 4)
		{
			RightReached = true;
			LeftReached = false;
		}
		if (this->BossTurrets[0]->Position.x < 10)
		{
			RightReached = false;
			LeftReached = true;
		}
	}
	UpdateShots(dt, window_width, window_height);
}
void BossObject::UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height)
{
	for (auto n : this->BossTurrets)
	{
		switch (n->Type)
		{
		case 2:
		{
			GLfloat Speed = sqrt(SHOTVELOCITY2.x * SHOTVELOCITY2.x + SHOTVELOCITY2.y * SHOTVELOCITY2.y); //determine the magnitude of velocity
			GLfloat DistX = ShipPosition->x - n->Position.x;
			GLfloat DistY = ShipPosition->y - n->Position.y;
			glm::vec2 Direction = glm::vec2(DistX / sqrt(DistX * DistX + DistY * DistY), DistY / sqrt(DistX * DistX + DistY * DistY)); //determine the direction of velocity - aim towards the ship
			glm::vec2 ShotVelocity2 = glm::vec2(Speed * Direction);
			if (this->Stage > 0 && BossTimer().count() % 2 == 0 && n->NumberOfShots > 0)
			{
				Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, ShotVelocity2, ResourceManager::GetTexture("shot1")));
				n->NumberOfShots--;
			}
			break;
		}
		case 1:
			if (this->Stage > 0 && BossTimer().count() % 3 == 0 && n->NumberOfShots > 0)
			{
				Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1, 1, SHOTVELOCITY1, ResourceManager::GetTexture("shot1")));
				n->NumberOfShots--;
			}
			break;
		}
	}
	for (auto n : Shots)
	{
		n->Move(dt);//TODO remove , window_width, glm::vec2(100.0f, 100.0f));
	}
	for (auto it = Shots.begin(); it != Shots.end(); /*nothing*/) //erase shots
	{
		if ((*it)->Position.y > window_height || (*it)->Position.y < 0 || (*it)->Position.x > window_width || (*it)->Position.x < 0 || (*it)->Power < 1)
		{
			it = Shots.erase(it);
		}
		else
		{
			it++;
		}
	}
}
void BossObject::Draw(TextRenderer& trenderer, SpriteRenderer& renderer)
{
	std::string TimerString = std::to_string(BossTimer().count());
	for (auto n : this->BossTurrets)
	{
		renderer.DrawSprite(n->Sprite, n->Position, n->Size, n->Rotation, n->Color);
	}

	trenderer.RenderText(TimerString, 310.0f, 80.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
	for (auto n : this->Shots)
	{
		n->Draw(renderer);
	}
}