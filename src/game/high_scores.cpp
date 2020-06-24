#include "high_scores.h"
#include <fstream>

HighScores::HighScores(const GLchar* file) :File(file)
{
	for (size_t i = 0; i < 9; i++)
	{
		ScoreList[i].first = "AAA";
		ScoreList[i].second = 0;
	}
}


void HighScores::Draw(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& trenderer) //TODO remove 'file', use 'File'
{
	//load highscores.txt into ScoreList[]
	std::ifstream infile(File);
	for (int it = 0; it < sizeof(ScoreList) / sizeof(*ScoreList); it++)
	{
		infile >> ScoreList[it].first >> ScoreList[it].second;
	}

	//render highscores
	for (int it = 0; it < sizeof(ScoreList) / sizeof(*ScoreList); it++)
	{
		std::string dhs = "";
		for (GLuint hs = ScoreList[it].second; hs < 999999999; hs = hs * 10)
		{
			dhs = "0" + dhs;
		}
		dhs = dhs + std::to_string(ScoreList[it].second);
		trenderer.RenderText(ScoreList[it].first, 250.0f, 150.0f + it * 50, 1.0f, glm::vec3(.7f, .7f, 1.0f));
		trenderer.RenderText(dhs, 400.0f, 150.0f + it * 50, 1.0f, glm::vec3(.7f, 1.0f, .7f));
	}
}
GLuint HighScores::LowestEntry()
{
	return ScoreList[(sizeof(ScoreList) / sizeof(*ScoreList)) - 1].second; //return last member of ScoreList[]
}
void HighScores::InsertNewScore(GLuint)
{
	std::ofstream outfile;
	int i = 5;
	outfile.open("res/high_scores/test.txt");
	outfile << i;
	outfile.close();
}