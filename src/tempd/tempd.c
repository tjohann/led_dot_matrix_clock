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

#include "tempd.h"


static void
__attribute__((noreturn)) usage(void)
{
	fprintf(stdout, "\nusage: ./tempd -d /etc/led_dot_matrix_clock/tempd.conf\n");
	fprintf(stdout, "               -d -> config directory                 \n");
	exit(EINVAL);
}


static void
cleanup(void)
{
	config_destroy(&cfg);
	
	fprintf(stdout,"in cleanup -> Cheers %s\n", getenv("USER"));
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
		fprintf(stderr, "no valid signal handler for %d\n", signo);
	}
	
}


static
void read_daemon_conf(struct conf_obj *conf)
{
	const char *str;
	
	if (config_lookup_string(&cfg, "common.message_file", &str)) {
                fprintf(stdout, "common.message_file for %s\n", str);
		conf->message_file = str;
		
        } else
                fprintf(stderr, "No 'common.message_file' setting in config file!\n");

        if (config_lookup_string(&cfg, "tempd.i2c_adapter", &str)) {
                fprintf(stdout, "tempd.i2c_adapter for %s\n", str);
		conf->i2c_adapter = str;
        } else
                fprintf(stderr, "No 'tempd.i2c_adapter' setting in config file!\n");


	printf("message_file %p\n", conf->message_file);
	printf("i2c_adapter %p\n", conf->i2c_adapter);
}


int main(int argc, char *argv[])
{
        const char *str;
	const char *conf_dir = NULL;
	int c;
	
	if (argc == 1) 
		usage();

	while ((c = getopt(argc, argv, "hd:")) != -1) {
		switch (c) {
		case 'd':
			conf_dir = optarg;
			break;
		case 'h':		
			usage();
			break;
		default:
			fprintf(stderr,"ERROR: no valid argument");
			usage();
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
       

	
	/*
	 * finished config handling
	 */
	if (fchdir(cur_dir) == -1)
		error_msg("cant set old working dir");
	close(cur_dir);
	
        config_destroy(&cfg);
        
        exit(EXIT_SUCCESS);
}
