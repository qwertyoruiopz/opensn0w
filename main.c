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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <stdbool.h>

bool verboseflag = false;

#define usage(x) \
    printf("Usage: %s [OPTION]\n" \
           "Jailbreak an iOS device (iPhones/iPod touches/iPads)\n" \
           "Supported devices are: %s\n" \
           "\n" \
           "Options:\n" \
           "\t-v                Verbose mode. Useful for debugging.\n" \
           "\t-h                Help.\n" \
           "\t-k kernelcache    Boot using specified kernel.\n" \
           "\t-i ipsw           Use specified ipsw to retrieve files from\n" \
           "\t-b bootlogo.img3  Use specified bootlogo img3 file during startup.\n" \
           "\n", \
           argv[0], \
           "None." ); \
    exit(-1);

bool file_exists(const char* fileName)
{
   struct stat buf;
   return !stat(fileName, &buf);
}

int main(int argc, char **argv) {
    int c;
    char *ipsw = NULL, *kernelcache = NULL, *bootlogo = NULL;

    printf("opensn0w, an open source jailbreaking program.\n"
           "Compiled on: " __DATE__ " " __TIME__ "\n\n");

    opterr = 0;

    while ((c = getopt (argc, argv, "vhk:i:b:")) != -1)
        switch (c)
    {
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

    /* to be done */

    printf("to be completed\n");

    return 0;
}
