#include "Cmd.h"

std::string Cmd::print() {
	std::string s = "";
		
	for (unsigned i = 0; i < argc - 1; ++i) {
		s+= args[i];
		s+= ' ';
	}
	
	return s;
}

bool Cmd::execute() {

	//char testCmd[] = "test\0";
	//struct stat path_stat;	
/*
		std::cout << "-----------COMMAND-------------\n\n";
		std::cout << "args: " << argc << "\n";
		for (unsigned i = 0; i < argc - 1; ++i) {
			std::cout << i << " " << args[i] << "\n";
		}
		std::cout << "-------------------------------\n\n";*/
        if (strcmp(args[0],"test") == 0) {
                struct stat path_stat;
               // std::cout << "T: \n" << args[0] << "\n" << args[1] << "\n";
                if (strcmp(args[1],"-d")== 0) {
			//std::cout << "TEST FOR DIR:\n";
                        if(stat(args[2], &path_stat) == 0  && S_ISDIR(path_stat.st_mode)){
                                std::cout << "(TRUE)\n";
                        }

                        else {std::cout << "(FALSE)\n"; exeFailed = true;}


                }
                if (strcmp(args[1],"-f") == 0) {
			//std::cout << "TEST FOR FILE:\n";
                        if(stat(args[2], &path_stat) == 0  && S_ISREG(path_stat.st_mode)){
                                std::cout << "(TRUE)\n";
                        }
                        else {std::cout << "(FALSE)\n"; exeFailed = true;}


                }
                if (strcmp(args[1], "-e") == 0) {
			//std::cout << "TEST IF EXIST:\n";
                        if(stat(args[2], &path_stat) == 0 && (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode))){
                                std::cout << "(TRUE)\n";
                        }
                        else {std::cout << "(FALSE)\n"; exeFailed = true;}

                }
                if (argc == 2){
			//std::cout << "TEST IF EXSIT:\n";
                        if(stat(args[1], &path_stat) == 0 && (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode))){
                                std::cout << "(TRUE)\n";
                        }
                        else {std::cout << "(FALSE)\n"; exeFailed = true;}
                }
		return exeFailed;
	}

	else {
	
    		char exitCmd[] = "exit";
	
    		if (strcmp(args[0],exitCmd) == 0) {exit(0);}

   		pid_t cpid, endpid;
		int wstatus;
		if ( ( cpid = fork() ) < 0) {
			perror("fork");
			exeFailed = true;
			return exeFailed;
		}
		if (cpid == 0) {
			if (execvp(args[0], args) == -1) {
				perror(args[0]);
				exeFailed = true;
				exit(EXIT_FAILURE);
			}
		
		}
		else if (cpid > 0) {
			do { 
				if (endpid = waitpid(cpid, &wstatus,0) == -1) {
					perror("waitpid");
					exeFailed = true;
					exit (EXIT_FAILURE);
				}
				if (WEXITSTATUS(wstatus)!= 0 ) {exeFailed = true;}
				if (WIFSIGNALED(wstatus)) {exeFailed = true;}
				if (WIFSTOPPED(wstatus)) {exeFailed = true;}
			}while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		if (WEXITSTATUS(wstatus) != 0) {exeFailed = true;}
		}
	
		return exeFailed;	
	}
}
