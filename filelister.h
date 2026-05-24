#ifndef FILELISTER_H
#define FILELISTER_H

#include <cstdint>
#include <string>

using namespace std;

string prgname="dlg-filelister";
string version="1.0a";
string copyright="(c) 2026 by Felice Murolo, Salerno - Italia";
string email="linuxboy@fel.hopto.org";

// Directly from include/dlg/file.h source, from package DLG_Source.zip

/* File header - First part of FILE:<number>/<nunber>.fd
   The header is followed by a null-terminated body of text */
struct  File_Header
{
    char    From[36];           /* The user who uploaded the file                  */
    char    Filename[36];       /* Filename of the file this is describing         */
    char    Date[20];           /* Text string of the date the file was uploaded   */
    int16_t Times_Downloaded;   /* Number of downloads the file has had            */
    int32_t Size;               /* Size of the file in bytes                       */
    int16_t Attribute;          /* See attributes below                            */
}__attribute__((packed));

/* Flags for the attribute field of the file header */
#define NORATIO   1 /* No file ratio will be imposed on this file */
#define UNVALIDATED 2 /* This is an unvalidated file */

/* Quick file index

 The following structure must be written alphabetically on the first field
 into an index file called 'file.dat' in each public file area when a file is
 added.  Also must be deleted when the file is removed.  Applicable fields
 must also be modified in the index file when the filename, size, date, or
 description changes. Use AddStruct() if possible.

 All utilities that place a file into a public file area must be modified to
 update this file. (Private files need not worry about this index file).

*/

struct QuickFile
{
    char    filename[36];
    uint32_t    date;         /* number of seconds since Jan 1, 1978 */
    uint16_t   number;        /* File number (.fd file number)       */
    uint32_t    size ;        /* size of file in bytes               */
    char    desc[60];         /* 60 character of the description     */
} __attribute__((packed));


void Usage(void);
bool startsWith(const string& str, const string& prefix);
void replaceAll(string& str, const string& from, const string& to);
string trovaFileCaseInsensitive(const string& directory, const string& nomeCercato);

#endif // FILELISTER_H
