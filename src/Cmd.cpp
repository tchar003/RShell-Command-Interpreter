#include "Cmd.h"

std::string Cmd::print() {
	std::string s = "";

	for (unsigned i = 0; i < argc - 1; ++i) {
		s += args[i];
		s += ' ';
	}

	// Remove the last space
	if (!s.empty()) {
		s.pop_back();
	}

	return s;
}

bool Cmd::execute() {
	if (strcmp(args[0], "test") == 0) {
		struct stat path_stat;

		// Check if the argument is a directory
		if (strcmp(args[1], "-d") == 0) {
			if (stat(args[2], &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
				std::cout << "(TRUE)\n";
			} else {
				std::cout << "(FALSE)\n";
				exeFailed = true;
			}
		}

		// Check if the argument is a file
		if (strcmp(args[1], "-f") == 0) {
			if (stat(args[2], &path_stat) == 0 && S_ISREG(path_stat.st_mode)) {
				std::cout << "(TRUE)\n";
			} else {
				std::cout << "(FALSE)\n";
				exeFailed = true;
			}
		}

		// Check if the argument exists (file or directory)
		if ((strcmp(args[1], "-e") == 0) || argc == 2) {
			if (stat(args[2], &path_stat) == 0 && (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode))) {
				std::cout << "(TRUE)\n";
			} else {
				std::cout << "(FALSE)\n";
				exeFailed = true;
			}
		}

		return exeFailed;
	} else {
		char exitCmd[] = "exit";

		// Handle the "exit" command
		if (strcmp(args[0], exitCmd) == 0) {
			exit(0);
		}

		pid_t cpid, endpid;
		int wstatus;

		// Fork a child process
		if ((cpid = fork()) < 0) {
			perror("fork");
			exeFailed = true;
			return exeFailed;
		}

		if (cpid == 0) {
			// Execute the command in the child process
			if (execvp(args[0], args) == -1) {
				perror(args[0]);
				exeFailed = true;
				exit(EXIT_FAILURE);
			}
		} else if (cpid > 0) {
			// Wait for the child process to finish
			do {
				endpid = waitpid(cpid, &wstatus, 0);
				if (endpid == -1) {
					perror("waitpid");
					exeFailed = true;
					exit(EXIT_FAILURE);
				}
				if (WEXITSTATUS(wstatus) != 0) {
					exeFailed = true;
				}
				if (WIFSIGNALED(wstatus)) {
					exeFailed = true;
				}
				if (WIFSTOPPED(wstatus)) {
					exeFailed = true;
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		}

		return exeFailed;
	}
}
