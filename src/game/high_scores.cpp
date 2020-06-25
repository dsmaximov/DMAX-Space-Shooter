#include "high_scores.h"
#include <fstream>

HighScores::HighScores(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& trenderer) :File(file), Srenderer(srenderer), Trenderer(trenderer) //Initials({"","",""})
{
	//load highscores.txt into ScoreList[]
	std::ifstream infile(File);
	for (int it = 0; it < sizeof(ScoreList) / sizeof(*ScoreList); it++)
	{
		infile >> ScoreList[it].first >> ScoreList[it].second;
	}
	ScoreListSize = sizeof(ScoreList) / sizeof(*ScoreList);

}


std::string HighScores::AddInitials(GLint& keycode, int& keyaction)
{
	Trenderer.RenderText("New High Score", 250.0f, 500.0f, 1.0f, glm::vec3(1.0f, .7f, .7f));
	Trenderer.RenderText("Enter your initials", 250.0f, 550.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
	Trenderer.RenderText(std::string(1, keycode), 250.0f, 600.0f, 1.5f, glm::vec3(.7f, .7f, 1.0f));

	//for (int i = 0; i < 3; )
	//{
	//	if (keyaction == GLFW_PRESS)
	//	{
	//		Initials[i] = std::string(1, keycode);
	//		i++;
	//	}
	//}
	//if (keyaction == GLFW_RELEASE) Initials[0] = std::string(1, keycode);
	if (keyaction) ButtonPressed = true;
	if (!keyaction && ButtonPressed && InitialNumber == 0)
	{
		Initials[InitialNumber] = std::string(1, keycode);
		ButtonPressed = false;
		InitialNumber++;
	}
	if (!keyaction && ButtonPressed && InitialNumber == 1)
	{
		Initials[InitialNumber] = std::string(1, keycode);
		ButtonPressed = false;
		InitialNumber++;
	}
	if (!keyaction && ButtonPressed && InitialNumber == 2)
	{
		Initials[InitialNumber] = std::string(1, keycode);
		ButtonPressed = false;
		InitialNumber++;
	}
	Trenderer.RenderText(Initials[0], 250.0f, 650.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	Trenderer.RenderText(Initials[1], 270.0f, 650.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	Trenderer.RenderText(Initials[2], 290.0f, 650.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	Trenderer.RenderText(std::to_string(keyaction), 250.0f, 700.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	Trenderer.RenderText(std::to_string(ButtonPressed), 250.0f, 750.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));

	return "XYZ";
}

void HighScores::Draw(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& trenderer) //TODO remove 'file', use 'File'
{
	//render highscores
	for (int it = 0; it < ScoreListSize; it++)
	{
		std::string dhs = "";
		for (GLuint hs = ScoreList[it].second + 1; hs < 999999999; hs = hs * 10) //adding leading zeroes for alignment
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
	return ScoreList[ScoreListSize - 1].second; //return last member of ScoreList[]
}
void HighScores::InsertNewScore(GLuint new_high_score)
{
	for (int it = 0; it < ScoreListSize; it++)
	{
		if (new_high_score > ScoreList[it].second)
		{
			for (int i = ScoreListSize - 1; i > it; i--)
			{
				ScoreList[i] = ScoreList[i - 1]; //move all highscores one position down in order to leave a position for the new highscore
			}
			ScoreList[it].first = "SHP";
			ScoreList[it].second = new_high_score;
			break;
		}
	}

	// Write to the file
	std::ofstream MyFile("res/high_scores/highscores.txt");
	for (int i = 0; i < ScoreListSize; i++)
	{
		MyFile << ScoreList[i].first << " " << ScoreList[i].second << "\n";
	}
	MyFile.close();
}