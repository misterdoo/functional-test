
#include <iostream>
#include <atomic>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <filesystem>
#include <unistd.h>
#include <termios.h>

#include "misc_function.h"
#include "debug.h"
#include "monitor_app.h"

MonitorApp* 	gp_mon_app;

int help_print(void)
{
	std::cerr << "usage) \n";
	std::cerr << "      1: create LogManager class for Db.\n";
	std::cerr << "\n";
	std::cerr << "      3: create Thread add Manually.\n";
	std::cerr << "      4: Wake-up Manually Thread.\n";
	std::cerr << "      5: Destroy Manually Thread.\n";
	std::cerr << "\n";
	std::cerr << "      0: create Thread add Auto.\n";
	std::cerr << "      9: Wake-up Auto Thread.\n";
	std::cerr << "      8: Destroy Auto Thread.\n";
	std::cerr << "\n";
	std::cerr << "      d: delete db file.\n";
	std::cerr << "      h: help msg\n";
	std::cerr << "      q: quit\n";

	return 0;
}

int force_remove_db_file(void)
{
	std::string db_file_abs_path(std::filesystem::current_path() / "log.db");

	RemoveFile(db_file_abs_path);
	return TRUE;
}

int set_term_echo(struct termios& cur_termio, bool is_enable = true)
{
	if (is_enable == true) {
		cur_termio.c_lflag |= (ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &cur_termio);
	} else {
		cur_termio.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &cur_termio);
	}
	return TRUE;
}

int main (int argc, char* argv[])
{
	bool ret = true;
	bool valid_input = true;
	int input = 0;
	//int max_db_count;
	int add_field_count;
	int is_valid_logman = FALSE;
	//int is_valid_thread = FALSE;

	struct termios cur_termio;

	gp_mon_app = new MonitorApp;

	if (gp_mon_app == nullptr) {
		mgh_error("Failed to alloc class. \n");
		return FALSE;
	}

	help_print();

	tcgetattr(STDIN_FILENO, &cur_termio);

	set_term_echo(cur_termio, false);

	while (valid_input == true) {
		input = getchar();

		mgh_printf("keyin : (%c)\n", input);

		switch (input)
		{
			case '1':
				{
					set_term_echo(cur_termio);

					std::cerr << "Default Number of Fields is 2." << std::endl;
					std::cerr << "Enter the Number to Field, you want to Add :" ;
					std::cin >> add_field_count;

					ret = std::cin.fail();
					if (ret == true) {
						std::cin.clear();
						std::cin.ignore(1000, '\n');

						mgh_warn("invalid input. clear!! \n");
					}

					set_term_echo(cur_termio, false);

					is_valid_logman = gp_mon_app->AllocationLogManager(COUNT_DEFAULT_FIELD + add_field_count);
				}
				break;

			case '3': // thread create & start
				{
					is_valid_logman = gp_mon_app->IsValidLogMan();

					if (is_valid_logman == FALSE) {
						mgh_warn("Not alloc Log-manager class.\n");
						break;
					}

					gp_mon_app->CreateManuallyAddThread();
				}
				break;
			case '4': // thread wake up. 
				{
					is_valid_logman = gp_mon_app->IsValidLogMan();

					if (is_valid_logman == FALSE) {
						mgh_warn("Not alloc Log-manager class.\n");
						break;
					}

					gp_mon_app->WakeUpManuallyAddThread();
				}
				break;
			case '5': // thread destroy
				{
					gp_mon_app->DestroyManuallyAddThread();
				}
				break;
			case '0':
				{
					gp_mon_app->CreateAutoAddThread();
				}
				break;
			case '9':
				{
					gp_mon_app->WakeUpAutoAddThread();
				}
				break;
			case '8':
				{
					gp_mon_app->DestroyAutoAddThread();
				}
				break;
			case 'd':
				{
					force_remove_db_file();
				}
				break;
			case 'q':
				{
					valid_input = false;
				}
				break;
			case 'h':
			default:
				{
					help_print();
				}
				break;
		}
	}

	set_term_echo(cur_termio);

	delete gp_mon_app;

	return TRUE;
}
