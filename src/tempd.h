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

#ifndef _TEMPD_H
#define _TEMPD_H

#include <libarietta.h>
#include <libconfig.h>

/*
 * config related
 */
#define CONF_FILE "tempd.conf"
config_t cfg;

struct conf_obj {
	char *name;
        /*
	 * common parts
	 */
	const char *message_file;
	const char *kdo_msg_queue;
	const char *common_output_dir;
	/*
	 * tempd specific parts
	 */
	const char *i2c_adapter;
};


#endif

