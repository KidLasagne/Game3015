#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Juggernaut.h"

int main()
{
	bool ContinueLoop = true;
	Juggernaut *Jugg;

	while (ContinueLoop == true)
	{
		bool exiting = false;
		Jugg = NULL;
		Jugg = new Juggernaut();
		exiting = Jugg->Subterfuge();

		if (exiting == true)
		{
			ContinueLoop = true;
		}
		else
		{
			ContinueLoop = false;
		}
	}

	return 0;
}