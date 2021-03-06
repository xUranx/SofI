#include "GATextDemo.h"
#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
GATextDemo::GATextDemo()
{
}


GATextDemo::~GATextDemo()
{
}

bool GATextDemo::start()
{
	int popu;
	std::cout << "Population: "; std::cin >> popu;
	
	pop.setPop(popu);


	srand(time(NULL));

	for (int i = 0; i < pop.Members.size(); i++)
	{
		pop.Members.at(i).DNA.resize(DNA.size());
		for (int j = 0;j < DNA.size();j++)
		{
			pop.Members.at(i).DNA.at(j) = (unsigned char)rand() % 96 + 36;
		}
		pop.Members.at(i).fitnes = 0;
	}
	return false;
}


void GATextDemo::run()
{
	generation++;
	Parents.clear();
	for (int i = 0; i < pop.Members.size(); i++)
	{
		pop.Members.at(i).fitnes = 0;
		for (int j = 0;j < pop.Members.at(i).DNA.size();j++)
		{
			if (pop.Members.at(i).DNA.at(j) == DNA.at(j))
				pop.Members.at(i).fitnes += 10;
		}
		if (pop.Members.at(i).fitnes == DNA.size() * 10)
			SeqFound = true;
	}
	std::sort(pop.Members.begin(), pop.Members.end(), 
		[](Member &a, Member &b) {return a.fitnes > b.fitnes; });

	Parents.push_back(pop.Members.at(0));
	Parents.push_back(pop.Members.at(1));

	for (int i = 0; i < pop.Members.size(); i++)
	{
		for (int j = 0; j < pop.Members.at(i).DNA.size(); j++)
		{
			int tempSelection = rand() % Parents.size();
			pop.Members.at(i).DNA.at(j) = Parents.at(tempSelection).DNA.at(j);
			if (rand() % 1000 < mutRate)
				pop.Members.at(i).DNA.at(j) = (unsigned char)rand() % 96 + 32;
		}
	}
}

void GATextDemo::print(Engine::GLSpriteBatch& sBatch, Engine::SpriteFont& sFont)
{
#ifdef WIN32
	Engine::ColourRGBA8 colour;
	char buffer[256];
	char buffer2[256];
	char buffer3[256];
	int dnaz = DNA.size() * 10;
	sprintf_s(buffer, "Gen: %d Population: %d Highest Fitness: %d FitnessTo: %d", generation, pop.Members.size(), Parents[0].fitnes, dnaz);
	sFont.draw(sBatch, buffer, glm::vec2(20, 132), glm::vec2(1.1f), 0.0f, colour);
	sprintf_s(buffer2, "Text to get: %s", DNA.c_str());
	sFont.draw(sBatch, buffer2, glm::vec2(20, 164), glm::vec2(1.1f), 0.0f, colour);
	sprintf_s(buffer3, "Strongest Text: %s", Parents.at(0).DNA.c_str());
	sFont.draw(sBatch, buffer3, glm::vec2(20, 196), glm::vec2(1.1f), 0.0f, colour);
#endif
}
