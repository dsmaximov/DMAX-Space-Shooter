#include "power_up.h"

glm::vec2 PowerUp::Move(GLfloat dt, GLuint window_height)
{
	//movement down
	glm::vec2 DeltaPos = this->Velocity * dt;
	this->Position += DeltaPos;
	//pulsation
	glm::vec2 DeltaSize;
	if (this->Size.x > 1.2f * OriginalSize.x) //increase size until 1.2 original
	{
		PulseCoeff = -PulseCoeff;
		this->Size = 1.2f * OriginalSize;
	}
	if (this->Size.x < OriginalSize.x) //decrease size until back to original
	{
		PulseCoeff = -PulseCoeff;
		this->Size = OriginalSize;
	}
	DeltaSize = glm::vec2(DeltaPos.y / 5, DeltaPos.y / 5) * PulseCoeff; //speed of pulsations
	this->Size += DeltaSize;
	this->Position += - DeltaSize / 2.0f; //compensate displacement during size change
	
	return this->Position;
}