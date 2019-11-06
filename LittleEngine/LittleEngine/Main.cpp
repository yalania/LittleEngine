#include "Globals.h"
#include "Log.h"
#include "LittleEngine.h"

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

LittleEngine* Engine = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("LittleEngine Creation --------------");
			Engine = new LittleEngine();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Application Init --------------");
			if (Engine->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = Engine->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------");
			if (Engine->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;


		}

	}
	//delete Engine;
	LOG("Bye :)\n");
	return main_return;
}
