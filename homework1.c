#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{


        pid_t pid, pid1;

        int n;

        if (argc == 1) {
                fprintf(stderr,"Usage: ./a.out <starting value>\n");

                return -1;
        } 

        n = atoi(argv[1]);

                pid = fork();

		if (pid < 0) {
			fprintf(stderr, "Fork Failed"); 
			return -1; 
		}

                else if (pid == 0)
                {
			pid1 = getpid(); 
                        
			printf("child: pid = %d\n", pid); 
			printf("child: pid1 = %d\n", pid1); 
                        printf("n is: %d\n",n);


			printf("Sequence: \n"); 
			printf("%d\n",n); 

                        while (n!=1)
                        {
                                if (n%2 == 0)
                                {
                                        n = n/2;
                                }
                                else if (n%2 == 1)
                                {
                                        n = 3 * (n) + 1;
                                }
				
                                printf("%d\n",n);
                        }

                        
                }
                else
                {
			pid1 = getpid(); 
			printf("parent: pid = %d\n",pid); 
			printf("parent: pid1 = %d\n",pid1); 
                       
                        wait(NULL);
                        
                }

              


    return 0;
}
