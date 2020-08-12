#include "boss_object.h"



BossObject::BossObject(glm::vec2* ship_position)
	:ShipPosition(ship_position), Strength(InitialStrenght), Stage(0), Stage6Angle(0){}
void BossObject::Init()
{
	InitialTime = std::chrono::steady_clock::now();
	glm::vec2 pos(0.0f, -300.0f); //BOSS starting position
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
	this->CurrentTime = std::chrono::steady_clock::now();
	auto a = std::chrono::duration_cast<std::chrono::duration<GLint>> (CurrentTime - InitialTime);
	return a;
}
void BossObject::Move(GLfloat dt, GLuint window_width, GLuint window_height)
{
	GLint TimerStage0 = 3;
	GLint TimerStage2 = 20;
	GLint TimerStage7 = 3;
	GLint TimerStage8 = 5;
	GLint TimerStage9 = 5;

	switch (this->Stage)
	{
	case 0: 	// initial movement into the screen
		if (BossTimer().count() >= TimerStage0) this->Stage = 1;
		break;
	case 1: 	// initial movement into the screen
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityY = 50.0f;
			n->Position.y += dt * InitialBossVelocityY;
		}
		if (this->BossTurrets[0]->Position.y > 50) this->Stage = 2;
		break;
	case 2:
		// wobbling in x
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityX = 50.0f;
			if (LeftReached) n->Position.x += dt * InitialBossVelocityX;
			if (RightReached) n->Position.x -= dt * InitialBossVelocityX;
		}
		for (auto n : BossTurrets)
		{
			if (n->Position.x + n->Radius * 2 > window_width)
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
		if ((this->Strength < InitialStrenght * 0.7) || (BossTimer().count() >= TimerStage2)) this->Stage = 3;
		break;
	case 3:
		// wobbling in x & y
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityX = 60.0f;
			GLfloat InitialBossVelocityY = 60.0f;
			if (LeftReached) n->Position.x += dt * InitialBossVelocityX;
			if (RightReached) n->Position.x -= dt * InitialBossVelocityX;
			if (TopReached) n->Position.y += dt * 2 * InitialBossVelocityY;
			if (BottomReached) n->Position.y -= dt * InitialBossVelocityY;
		}
		for (auto n : BossTurrets)
		{
			if (n->Position.x + n->Radius * 2 > window_width)
			{
				RightReached = true;
				LeftReached = false;
			}
			if (n->Position.x < 0)
			{
				RightReached = false;
				LeftReached = true;
			}
			if (n->Position.y + n->Radius * 2 > window_height / 2)
			{
				BottomReached = true;
				TopReached = false;
			}
			if (n->Position.y < 50)
			{
				BottomReached = false;
				TopReached = true;
			}
		}
		if (this->Strength < InitialStrenght / 2) this->Stage = 4;
		break;
	case 4:
	{
		std::vector <GLint> DestroyedTurrets{ 0,1,4,5, 20, 23, 25 };
		for (auto it = DestroyedTurrets.begin(); it != DestroyedTurrets.end(); it++)
		{
			this->BossTurrets[*it]->Strength = 0;
		}
		this->Stage = 5;
		break;
	}
	case 5:
	{
		GLfloat Stage6StartingPositionX = 150;
		if (this->BossTurrets[0]->Position.x >= Stage6StartingPositionX)
		{
			for (auto n : BossTurrets)
			{

				GLfloat InitialBossVelocityX = -150.0f;
				n->Position.x += dt * InitialBossVelocityX;
			}
			if (this->BossTurrets[0]->Position.x < 150) this->Stage = 6;
		}
		else
		{
			for (auto n : BossTurrets)
			{
				GLfloat InitialBossVelocityX = 150.0f;
				n->Position.x += dt * InitialBossVelocityX;
			}
			if (this->BossTurrets[0]->Position.x >= Stage6StartingPositionX) this->Stage = 6;
		}
	}
		break;
	case 6:
		//circular motion
		Stage6Angle += dt;
		for (auto n : BossTurrets)
		{
			GLfloat InitialBossVelocityX = 100.0f;
			n->Position.x += dt * InitialBossVelocityX * 2.0f * sin(Stage6Angle);
			n->Position.y += dt * InitialBossVelocityX * cos(Stage6Angle);
		}
		if (this->Strength < 1)
		{
			this->InitialTime = std::chrono::steady_clock::now();
			for (auto n : this->BossTurrets)
			{
				n->Strength = 0;
			}
			this->Stage = 7;
		}
		break;
	case 7:
		if (BossTimer().count() >= TimerStage7)
		{
			this->Stage = 8;
			this->InitialTime = std::chrono::steady_clock::now();
		}
		break;
	case 8:
		if (BossTimer().count() >= TimerStage8)
		{
			this->Stage = 9;
			this->InitialTime = std::chrono::steady_clock::now();
		}
		break;
	case 9:
		if (BossTimer().count() >= TimerStage9)
		{
			this->Stage = 10;
			this->InitialTime = std::chrono::steady_clock::now();
		}
		break;
	}
	UpdateShots(dt, window_width, window_height);
}
void BossObject::UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height)
{
	for (auto n : this->BossTurrets)
	{
		switch (this->Stage)
		{
		case 2: //BOSS stage 2 shots
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
		case 3:
			switch (n->Type)
			{
			case 2:
			{
				if (this->Stage > 0 && BossTimer().count() % 3 == 0 && !n->ShotTaken)
				{
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2 * 2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(-SHOTVELOCITY2.x, 0.7f * SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x + SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x, 0.7f * SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(0.0f, SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
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
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1, 1, ShotVelocity1, ResourceManager::GetTexture("shot2")));
					n->ShotTaken = true;
				}
				if (BossTimer().count() % 2 != 0) n->ShotTaken = false;
				break;
			}
			break;
		case 6 :
			switch (n->Type)
			{
			case 2:
			{
				GLfloat Speed = sqrt(SHOTVELOCITY2.x * SHOTVELOCITY2.x + SHOTVELOCITY2.y * SHOTVELOCITY2.y); //determine the magnitude of velocity
				GLfloat DistX = ShipPosition->x - n->Position.x;
				GLfloat DistY = ShipPosition->y - n->Position.y;
				glm::vec2 Direction = glm::vec2(DistX / sqrt(DistX * DistX + DistY * DistY), DistY / sqrt(DistX * DistX + DistY * DistY)); //determine the direction of velocity - aim towards the ship
				glm::vec2 ShotVelocity2 = glm::vec2(Speed * Direction);
				if (this->Stage > 0 && BossTimer().count() % 2 == 0 && !n->ShotTaken)
				{
					//auto-target shot
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1+1.0f, 1, ShotVelocity2, ResourceManager::GetTexture("shot2")));
					//spreading shots
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2 * 2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(-SHOTVELOCITY2.x, 0.7f * SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x + SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x, 0.7f * SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(0.0f, SHOTVELOCITY2.y), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - SHOTRADIUS2 * 2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(-1.4*SHOTVELOCITY2.x, 0.0f), ResourceManager::GetTexture("shot1")));
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x + SHOTRADIUS2, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(1.4 * SHOTVELOCITY2.x, 0.0f), ResourceManager::GetTexture("shot1")));
					n->ShotTaken = true;
				}
				if (BossTimer().count() % 2 != 0) n->ShotTaken = false;
				break;
			}
			case 1:
				if (BossTimer().count() % 3 == 0)
				{
					Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1+5.0f, 2, glm::vec2(0.0f, 1000.0f), ResourceManager::GetTexture("laser")));
					if (!n->ShotTaken) SoundEngineBoss->play2D("res/audio/boss_laser.wav", GL_FALSE);
					n->ShotTaken = true;
				}
				if (BossTimer().count() % 3 != 0) n->ShotTaken = false;
				break;
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
	//draw boss structure (turrets)
	for (auto n : this->BossTurrets)
	{
		renderer.DrawSprite(n->Sprite, n->Position, n->Size, n->Rotation, n->Color);
	}
	//draw messages
	switch (this->Stage)
	{
	case 0:
		trenderer.RenderText("WARNING!", 330.0f, 250.0f, 1.0f, glm::vec3(.9f, .5f, .1f));
		trenderer.RenderText("LARGE MASS DETECTED", 250.0f, 280.0f, 1.0f, glm::vec3(.9f, .5f, .1f));
		break;
	case 8:
		trenderer.RenderText("CONGRATULATIONS!", 280.0f, 250.0f, 1.0f, glm::vec3(0.5f, 1.0f, .1f));
		trenderer.RenderText("YOU HAVE SAVED THE GALAXY", 220.0f, 280.0f, 1.0f, glm::vec3(0.5f, 1.0f, .1f));
		break;
	default:
		trenderer.RenderText("Boss: ", 5.0f, 30.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		GLfloat BossShieldSizeSprite = 1.0f;
		for (GLint i = 0; i < this->Strength; i++)
		{
			renderer.DrawSprite(ResourceManager::GetTexture("player_shields"), glm::vec2(95.0f + i * BossShieldSizeSprite, 30.0f), glm::vec2(BossShieldSizeSprite, 20.0f));
		}
	}

	//draw strenght and timer for debugging do not delete: can be used for future boss changes
	//std::string StrengthString = std::to_string(this->Strength);
	//std::string TimerString = std::to_string(BossTimer().count());
	//trenderer.RenderText(TimerString, 310.0f, 80.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
	//trenderer.RenderText(StrengthString, 310.0f, 120.0f, 1.0f, glm::vec3(.3f, .9f, .7f));

	//draw boss shots
	for (auto n : this->Shots)
	{
		if (n->Power>1) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		n->Draw(renderer);
		if (n->Power > 1) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
bool BossObject::Clean()
{
	auto last = std::remove_if(this->BossTurrets.begin(), this->BossTurrets.end(), [](EnemyObject* enemy)->bool {return enemy->Strength < 1; });
	if (last == this->BossTurrets.end())
	{
		return false;
	}
	else
	{
		this->BossTurrets.erase(last, this->BossTurrets.end());
		return true;
	}
}