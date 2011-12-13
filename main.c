/* OpenSn0w 
 * Open source equivalent of redsn0w
 * Brought to you by rms, acfrazier & Maximus
 * Special thanks to iH8sn0w & MuscleNerd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "sn0w.h"

bool verboseflag = false;
irecv_device_t device = NULL;
irecv_client_t client = NULL;

#define usage(x) \
	printf("Usage: %s [OPTION]\n" \
			"Jailbreak an iOS device (iPhones/iPod touches/iPads)\n" \
			"Supported devices are: %s\n" \
			"\n" \
			"Options:\n" \
			"\t-v				Verbose mode. Useful for debugging.\n" \
			"\t-h				Help.\n" \
			"\t-w url		Get necessary files from a remote IPSW.\n" \
			"\t-k kernelcache	Boot using specified kernel.\n" \
			"\t-i ipsw		   Use specified ipsw to retrieve files from\n" \
			"\t-b bootlogo.img3  Use specified bootlogo img3 file during startup.\n" \
			"\n", \
			argv[0], \
			"None." ); \
			exit(-1);

bool file_exists(const char* fileName) {
	struct stat buf;
	return !stat(fileName, &buf);
}

int poll_device_for_dfu() {
	irecv_error_t err;
	static int try;
	err = irecv_open(&client);
	if (err != IRECV_E_SUCCESS) {
		printf("\rConnect the device in DFU mode. [%d]", try);
		fflush(stdout);
		goto err;
	}

	if (client->mode != kDfuMode) {
		printf("\rConnect the device in DFU mode. [%d]", try);
		fflush(stdout);
		irecv_close(client);
		goto err;
	}

	return 0;
	err:
	try++;
	return 1;
}

int main(int argc, char **argv) {
	int c;
	char *ipsw = NULL, *kernelcache = NULL, *bootlogo = NULL, *url = NULL;;
	irecv_error_t err = IRECV_E_SUCCESS;

	printf("opensn0w, an open source jailbreaking program.\n"
		   "Compiled on: " __DATE__ " " __TIME__ "\n\n");

	opterr = 0;

	while ((c = getopt (argc, argv, "vhb:w:k:i:")) != -1) {
		switch (c) {
		case 'v':
			verboseflag = true;
			break;
		case 'h':
			usage();
			break;
		case 'i':
			if (!file_exists(optarg)) {
				printf("Cannot open IPSW file '%s'\n", ipsw);
				return -1;
			}
			ipsw = optarg;
			break;
		case 'w':
			url = optarg;
			break;
		case 'k':
			if (!file_exists(optarg)) {
				printf("Cannot open kernelcache file '%s'\n", optarg);
				return -1;
			}
			kernelcache = optarg;
			break;
		case 'b':
			if (!file_exists(optarg)) {
				printf("Cannot open bootlogo file '%s'\n", optarg);
				return -1;
			}
			bootlogo = optarg;
			break;
		default:
			usage();
		}
	}

	/* to be done */
	printf("Initializing libirecovery\n");
	irecv_init();

#ifdef DEBUG
	irecv_set_debug_level(3);
#endif

	/* Poll for DFU mode */
	while(poll_device_for_dfu()) {
		sleep(1);
	}
	puts("");

	/* Got the handle */

	/* Check the device */
	err = irecv_get_device(client, &device);
	if (device == NULL || device->index == DEVICE_UNKNOWN) {
		printf("Bad device. errno %d\n", err);
		return -1;
	}

	printf("Device found: name: %s, processor s5l%dxsi\n", device->product, device->chip_id);
	printf("iBoot information: %s\n", client->serial);

	/* What jailbreak exploit is this thing capable of? */
	if(device->chip_id == 8930 || device->chip_id == 8922 || device->chip_id == 8920) {
		printf("This device is compatible with the limera1n exploit. Sending.\n");
		err = limera1n();
		if(err) {
			printf("Error during limera1ning.\n");
			exit(-1);
		}
	} else {
		printf("Support for the S5L%dX isn't done yet.\n", device->chip_id);
	}

	/* We are owned now! */

	printf("Bootrom is pwned now! :D\n");

	printf("to be completed\n");

	return 0;
}
