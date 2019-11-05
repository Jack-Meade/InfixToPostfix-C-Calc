// CS3500 Project - filedata
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#define BFSIZE 101                                                  // Memory allocation for full buffer size

// Defines filedata struct
// Used to forward formatted string and number of tokens needed
typedef struct __filedata {
    int num_of_tokens;                                              // Used to calculate how much memory needed
    char *pstring;                                                  // Formatted string
} filedata;

//
filedata *create_filedata() {
    filedata *fd = (filedata *)malloc(sizeof(filedata));
    fd->num_of_tokens = 0;                                          // Initialise at 0
    fd->pstring = malloc(BFSIZE);                                   // File will be formatted in this buffer
    return fd;
}
