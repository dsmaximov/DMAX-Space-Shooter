#include "boss_object.h"

BossObject::BossObject(glm::vec2* ship_position)
	:ShipPosition(ship_position), Strength(100), Stage(0){}
void BossObject::Init()
{
	InitialTime = std::chrono::steady_clock::now();
	glm::vec2 pos(0.0f, -100.0f); //BOSS starting position

	//BOSS turret coordinate constants
	const GLfloat DistanceBetweenRows = 40.0f;
	const int StructureCountRow0 = 6;
	const GLfloat StructureStartRow0 = 220.0;
	const GLfloat StructureSpacingRow0 = 60.0;
	const int StructureCountRow1 = 7;
	const GLfloat StructureStartRow1 = 190.0;
	const GLfloat StructureSpacingRow1 = 60.0;
	const int StructureCountRow2 = 2;
	const GLfloat StructureStartRow2 = 175.0;
	const GLfloat StructureSpacingRow2 = 395.0;
	const int StructureCountRow3 = 5; //intermediate row
	const GLfloat StructureStartRow3 = 250.0;
	const GLfloat StructureSpacingRow3 = 60.0;
	const int TurretCount1 = 4;
	const GLfloat TurretStart1 = 191.0;
	const GLfloat TurretSpacing1 = 120.0;
	const int TurretCount2 = 3;
	const GLfloat TurretStart2 = 227.0;
	const GLfloat TurretSpacing2 = 146.0;

	//set up all BOSS structure

	for (int i = 0; i < StructureCountRow0; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + StructureStartRow0 + i * StructureSpacingRow0, pos.y), 
			TURRETRADIUS0, TURRETVELOCITY0, TURRETTEXTURE0, TURRETSTRENGHT0, SCOREPOINTS0, 0, 0, SHOTVELOCITY0));
	}
	for (int i = 0; i < StructureCountRow1; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + StructureStartRow1 + i * StructureSpacingRow1, pos.y + DistanceBetweenRows), 
			TURRETRADIUS0, TURRETVELOCITY0, TURRETTEXTURE0, TURRETSTRENGHT0, SCOREPOINTS0, 0, 0, SHOTVELOCITY0));
	}
	for (int i = 0; i < StructureCountRow2; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + StructureStartRow2 + i * StructureSpacingRow2, pos.y + DistanceBetweenRows * 2), 
			TURRETRADIUS0, TURRETVELOCITY0, TURRETTEXTURE0, TURRETSTRENGHT0, SCOREPOINTS0, 0, 0, SHOTVELOCITY0));
	}
	for (int i = 0; i < StructureCountRow3; i++) //intermediate row
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + StructureStartRow3 + i * StructureSpacingRow3, pos.y + DistanceBetweenRows / 2),
			TURRETRADIUS0, TURRETVELOCITY0, TURRETTEXTURE0, TURRETSTRENGHT0, SCOREPOINTS0, 0, 0, SHOTVELOCITY0));
	}
	for (int i = 0; i < TurretCount1; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + TurretStart1 + i * TurretSpacing1, pos.y + DistanceBetweenRows), 
			TURRETRADIUS1, TURRETVELOCITY1, TURRETTEXTURE1, TURRETSTRENGHT1, SCOREPOINTS1, 1, 1, SHOTVELOCITY1));
	}
	for (int i = 0; i < TurretCount2; i++)
	{
		this->BossTurrets.push_back(new EnemyObject(glm::vec2(pos.x + TurretStart2 + i * TurretSpacing2, pos.y + DistanceBetweenRows*2 - 10),
			TURRETRADIUS2, TURRETVELOCITY2, TURRETTEXTURE2, TURRETSTRENGHT2, SCOREPOINTS2, 2, 1, SHOTVELOCITY2));
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
		for (auto n : BossTurrets)
		{
			if (n->Position.x + n->Radius*2 > window_width)
			{
				RightReached = true;
				LeftReached = false;
			}
		}
		for (auto n : BossTurrets)
		{
			if (n->Position.x < 0)
			{
				RightReached = false;
				LeftReached = true;
			}
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

			if (this->Stage > 0 && BossTimer().count() % 3 == 0 && !n->ShotTaken)
			{
				Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2 * 2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(-SHOTVELOCITY2.x, SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
				Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x + SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, SHOTVELOCITY2, ResourceManager::GetTexture("shot1")));
				n->ShotTaken = true;
			}
			if (BossTimer().count() % 3 != 0) n->ShotTaken = false;
			break;
		}
		case 1:
			GLfloat Speed = sqrt(SHOTVELOCITY1.x * SHOTVELOCITY1.x + SHOTVELOCITY1.y * SHOTVELOCITY1.y); //determine the magnitude of velocity
			GLfloat DistX = ShipPosition->x - n->Position.x;
			GLfloat DistY = ShipPosition->y - n->Position.y;
			glm::vec2 Direction = glm::vec2(DistX / sqrt(DistX * DistX + DistY * DistY), DistY / sqrt(DistX * DistX + DistY * DistY)); //determine the direction of velocity - aim towards the ship
			glm::vec2 ShotVelocity1 = glm::vec2(Speed * Direction);
			if (this->Stage > 0 && BossTimer().count() % 2 == 0 && n->ShotTaken == false)
			{
				Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1, 1, ShotVelocity1, ResourceManager::GetTexture("shot1")));
				n->ShotTaken = true;
			}
			if (BossTimer().count() % 2 != 0) n->ShotTaken = false;
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
	std::string StrengthString = std::to_string(this->Strength);
	std::string TimerString = std::to_string(BossTimer().count());
	for (auto n : this->BossTurrets)
	{
		renderer.DrawSprite(n->Sprite, n->Position, n->Size, n->Rotation, n->Color);
	}

	trenderer.RenderText(TimerString, 310.0f, 80.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
	trenderer.RenderText(StrengthString, 310.0f, 120.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
	for (auto n : this->Shots)
	{
		n->Draw(renderer);
	}
}