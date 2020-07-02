#include "high_scores.h"
#include <fstream>

HighScores::HighScores(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& trenderer) :File(file), Srenderer(srenderer), Trenderer(trenderer), NewHighScore(false)
{
	//load highscores.txt into ScoreList[]
	std::ifstream infile(File);
	for (int it = 0; it < sizeof(ScoreList) / sizeof(*ScoreList); it++)
	{
		infile >> ScoreList[it].first >> ScoreList[it].second;
	}
	ScoreListSize = sizeof(ScoreList) / sizeof(*ScoreList);
}
std::string HighScores::AddInitials(GLint& keycode, int& keyaction, GLuint new_high_score)
{
	//define transitions of the state machine
	if (InitialState && keycode == 257) { InitialStateComplete = true; InitialState = false; }
	if (InitialStateComplete && LetterNumber == 0) { FirstLetter = true; }
	if (InitialStateComplete && LetterNumber == 1) { SecondLetter = true; }
	if (InitialStateComplete && LetterNumber == 2) { ThirdLetter = true; }
	if (InitialStateComplete && LetterNumber == 3) { AllLettersReady = true; }

	if (!keyaction) ButtonReleased = true;
	if (keyaction) ButtonPressed = true;
	if (InitialState)
	{
		Trenderer.RenderText("Press Enter", 303.0f, 450.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
	}

	if (FirstLetter)
	{
		Trenderer.RenderText("1st initial", 303.0f, 450.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
		if (!keyaction && ButtonPressed && ButtonReleased && keycode >= 65 && keycode <= 90)
		{
			Initials[0] = std::string(1, keycode);
			LetterNumber++;
			FirstLetter = false;
			ButtonPressed = false;
			ButtonReleased = false;
		}
	}
	if (SecondLetter)
	{
		Trenderer.RenderText("2nd initial", 303.0f, 450.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
		if (!keyaction && ButtonPressed && ButtonReleased && keycode >= 65 && keycode <= 90)
		{
			Initials[1] = std::string(1, keycode);
			LetterNumber++;
			SecondLetter = false;
			ButtonPressed = false;
			ButtonReleased = false;
		}
	}
	if (ThirdLetter)
	{
		Trenderer.RenderText("3rd initial", 303.0f, 450.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
		if (!keyaction && ButtonPressed && ButtonReleased && keycode >= 65 && keycode <= 90)
		{
			Initials[2] = std::string(1, keycode);
			LetterNumber++;
			ThirdLetter = false;
			ButtonPressed = false;
			ButtonReleased = false;
			this->InsertNewScore(new_high_score);
		}
	}
	if (AllLettersReady)
	{
		Trenderer.RenderText(" Complete! ", 303.0f, 450.0f, 1.0f, glm::vec3(.7f, .7f, 1.0f));
		NewHighScore = true;
		
	}
	//End of state machine

	//display initials
	Trenderer.RenderText("New High Score", 282.0f, 400.0f, 1.0f, glm::vec3(1.0f, .7f, .7f));

	for (int i = 0; i < 3; i++)
	{
		Trenderer.RenderText(Initials[i], 350.0f + i * 20, 490.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	}
	//TODO - remove, used for debugging
	//Trenderer.RenderText(std::to_string(keyaction), 250.0f, 700.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	//Trenderer.RenderText(std::to_string(ButtonPressed), 250.0f, 750.0f, 1.5f, glm::vec3(1.0f, .1f, .1f));
	//Trenderer.RenderText(std::string(1, keycode), 250.0f, 600.0f, 1.5f, glm::vec3(.1f, .1f, 1.0f));
	return "XYZ";
}

void HighScores::Draw()
{
	//render highscores
	for (int it = 0; it < ScoreListSize; it++)
	{
		std::string dhs = std::to_string(ScoreList[it].second);
		while (dhs.length() < 9) //adding leading zeroes for alignment
		{
			dhs = "0" + dhs;
		}
		if (ScoreList[it].second > 0)
		{
			Trenderer.RenderText(ScoreList[it].first, 270.0f, 150.0f + it * 50, 1.0f, glm::vec3(.7f, .7f, 1.0f));
			Trenderer.RenderText(dhs, 400.0f, 150.0f + it * 50, 1.0f, glm::vec3(.7f, 1.0f, .7f));
		}
	}
	Trenderer.RenderText("HIGH SCORES", 310.0f, 80.0f, 1.0f, glm::vec3(.3f, .9f, .7f));
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
			ScoreList[it].first = Initials[0]+Initials[1]+Initials[2];
			ScoreList[it].second = new_high_score;
			break;
		}
	}

	// Write to the file
	std::ofstream MyFile(File);
	for (int i = 0; i < ScoreListSize; i++)
	{
		if (ScoreList[i].second>0) MyFile << ScoreList[i].first << " " << ScoreList[i].second << "\n";
	}
	MyFile.close();
}