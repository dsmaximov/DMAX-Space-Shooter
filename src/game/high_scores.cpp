#include "high_scores.h"

HighScores::HighScores() 
{
	for (size_t i = 0; i < 10; i++)
	{
		ScoreList[0].first = "AAA";
		ScoreList[0].second = 0;
	}
}


void HighScores::Draw(SpriteRenderer& srenderer, TextRenderer& trenderer)
{
	std::string hs = std::to_string(ScoreList[0].second);
	trenderer.RenderText(ScoreList[0].first, 100.0f, 100.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	trenderer.RenderText(hs, 300.0f, 100.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}