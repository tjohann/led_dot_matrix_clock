/*
  GPL                                                                        
  (c) 2015, thorsten.johannvorderbrueggen@t-online.de
  
  This program is free software; you can redistribute it and/or modify       
  it under the terms of the GNU General Public License as published by       
  the Free Software Foundation; either version 2 of the License, or          
  (at your option) any later version.                                        
  
  This program is distributed in the hope that it will be useful,            
  but WITHOUT ANY WARRANTY; without even the implied warranty of             
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#include "clock_broker.h"


static void
usage(void)
{
	fprintf(stdout,
		"\nusage: ./clock_broker -d /etc/led_dot_matrix_clock/ \n");
	fprintf(stdout,
		"                      -d -> config directory          \n");
}


static void
__attribute__((noreturn)) usage_exit(void)
{
	usage();
	exit(EXIT_SUCCESS);
}


static void
cleanup(void)
{
	config_destroy(&cfg);
	
	fprintf(stdout, "in cleanup -> cheers %s\n\n", getenv("USER"));
}


static
void signal_handler(int signo)
{
	/*
	 * fprintf is not reentrant!
	 */
	switch (signo)
	{
	case SIGINT:
		fprintf(stdout,"caught SIGINT\n");
		exit(EXIT_SUCCESS);
		break;
	case SIGTERM:
		fprintf(stdout,"caught SIGTERM\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		error_msg("no valid signal handler for %d\n", signo);
	}
	
}


static
void read_daemon_conf(struct conf_obj *conf)
{
	const char *str;

	/* 
	 * common parts -> clock_broker
	 */
	if (config_lookup_string(&cfg, "common.message_file", &str)) 
		conf->message_file = str;
	else
		error_msg("No 'common.message_file' setting in config file!");
       	

	if (config_lookup_string(&cfg, "common.kdo_msg_queue", &str))
		conf->kdo_msg_queue = str;
        else
		error_msg("No 'common.kdo_msg_queue' setting in config file!");

	
	if (config_lookup_string(&cfg, "common.common_output_dir", &str)) 
		conf->common_output_dir = str;
        else 
                error_msg("No 'common.common_outpur_dir' setting in config file!");
}


void
print_config_content(struct conf_obj *conf)
{
	fprintf(stdout, "\n************************************************* \n");

	/* 
	 * common parts -> clock_broker
	 */
	printf("message_file@addr: %p with content %s\n",
	       conf->message_file, conf->message_file);
	
	printf("kdo_msg_queue@addr: %p with content %s\n",
	       conf->kdo_msg_queue, conf->kdo_msg_queue);
	
	printf("common_output_dir@addr: %p with content %s\n",
	       conf->common_output_dir, conf->common_output_dir);

	fprintf(stdout, "************************************************* \n\n");
}


int main(int argc, char *argv[])
{
        const char *str;
	const char *conf_dir = NULL;
	int c;
	
	if (argc == 1) 
		usage_exit();

	while ((c = getopt(argc, argv, "hd:")) != -1) {
		switch (c) {
		case 'd':
			conf_dir = optarg;
			break;
		case 'h':		
			usage_exit();
			break;
		default:
			fprintf(stderr,"ERROR: no valid argument");
			usage_exit();
		}
	}

	if (atexit(cleanup) != 0)
		exit(EXIT_FAILURE);

	if (signal(SIGINT, signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);

	if (signal(SIGTERM, signal_handler) == SIG_ERR)
		exit(EXIT_FAILURE);

	/*
	 * read config
	 */
	int cur_dir = -1;
	cur_dir = open(".", O_RDONLY);
	if (cur_dir == -1)
		error_exit("can't open actual dir -> %s",
			  strerror(errno));

	if (chdir(conf_dir) == -1)
		error_exit("can't change to dir %s -> %s",
			  conf_dir,
			  strerror(errno));
	
        config_init(&cfg);	
        if (config_read_file(&cfg, CONF_FILE) != CONFIG_TRUE)
        {
                fprintf(stderr, "%s:%d - %s\n",
                        config_error_file(&cfg),
                        config_error_line(&cfg),
                        config_error_text(&cfg));
                
                config_destroy(&cfg);
                exit(EXIT_FAILURE);
        }

        if (config_lookup_string(&cfg, "name", &str))
                fprintf(stdout, "config-file for %s\n", str);
        else
                error_exit("No 'name' setting in config file!");

        putchar('\n');

	/*
	 * read daemon specific content
	 */
	struct conf_obj daemon_conf;
	read_daemon_conf(&daemon_conf);

#if defined DEBUG      
	print_config_content(&daemon_conf);
#endif
	
	/*
	 * finished config handling
	 */
	if (fchdir(cur_dir) == -1)
		error_msg("cant set old working dir");
	close(cur_dir);


/*
 *  main parts
 */

	
        config_destroy(&cfg);
        
        exit(EXIT_SUCCESS);
}
